/**
 * Implementation file for the TripUtil.hpp.
 * @author barn
 * @version 20121019
 */

/*===========================================================================*
 * INCLUDES (associated header files)
 *===========================================================================*/
#include "Util.hpp"

/*===========================================================================*
 * INCLUDES project headers
 *===========================================================================*/
#include <Defines.h>
#include <util/Math.hpp>
#include <managers/TripVarManager.hpp>

/*===========================================================================*
 * INCLUDES C/C++ standard library (and other external libraries)
 *===========================================================================*/

/*===========================================================================*
 * DEFINES and MACROS
 *===========================================================================*/

/**
 * Maximum line size for entering. It should be
 * maximally as long as one line in your console window,
 * or else the formatting of printList() will not work properly.
 */
#define MAX_LINE_SIZE 80

/*===========================================================================*
 * NAMESPACE, CONSTANTS and TYPE DECLARATIONS/IMPLEMENTATIONS
 *===========================================================================*/

namespace Trip
{
	namespace Util
	{

		/**
		 * Converts an integer value into a string.
		 * @param an arbitrary integer value.
		 * @return the specified integer value as a string.
		 */
		std::string itos( int i)
		{
			std::stringstream stream;
			stream << i;
			return stream.str();
		}


		/*
		 * Checks, if a file with the specified path exists.
		 * @return
		 * TRUE - if the file exists
		 * FALSE - if the file doesn't exist
		 */
		bool fileExists( const char* file)
		{
			std::fstream f;

			f.open( file, std::ios::in);
			f.close();

			if( f.fail())
					return false;
			return true;
		}


		/**
		 * Prints a list of strings onto the console.
		 * @param strings The list of strings to print onto the console.
		 * @param min_space The minimum number of space characters between two elements of the list.
		 * @param expand_min_space Specifies, if the minimum number of spaces between
		 * two printed list elements shall be expanded as much as possible without beginning a new line.
		 * @param max_line_size The maximum length of a line in the console. In standard cases it is 80
		 * but you can redefine it. A printed line of this method will not exceed the given value.
		 * TRUE - expand as much as possible
		 * FALSE - use min_space as absolute minimum spaces
		 */
		void printList( const std::list<std::string> strings, unsigned char min_space, bool expand_min_space, unsigned char max_line_size)
		{
			// find the minimum size of a block
			unsigned char block_size(1);
			for( auto it = strings.begin(); it != strings.end(); it++)
			{
				if( it->size() + min_space > block_size)
				{
					block_size = it->size() + min_space;
				}
			}

			// expand block_size if necessary
			if( expand_min_space)
			{
				block_size +=(max_line_size % block_size) / (max_line_size/block_size);
			}

			// print strings
			unsigned char line_size(0);
			for( auto it = strings.begin(); it != strings.end(); it++)
			{
				line_size += block_size;

				if( line_size > max_line_size)
				{
					std::cout << std::endl;
					line_size = block_size;
				}
				else if( line_size == max_line_size)
				{
					line_size = block_size;
				}

				std::cout << std::left << std::setw( block_size) << *it;
			}

			std::cout << std::endl;
		}


		/**
		 * Splits a string at the specified delimeters and writes the results into the specified vector.
		 * @param s The string to split.
		 * @param delim The delimeter to use.
		 * @param elems The vector containing all substrings.
		*/
		std::vector<std::string>& split(const std::string& s, char delim, std::vector<std::string>& elems)
		{
			std::stringstream ss(s);
			std::string item;
			while( std::getline(ss, item, delim))
			{
			elems.push_back(item);
			}
			return elems;
		}


		/**
		 * Splits a string at the specified delimeters.
		 * @param s The string to split.
		 * @param delim The delimeter to use.
		 * @return A vector containing all substrings.
		 */
		std::vector<std::string> split(const std::string &s, char delim)
		{
			std::vector<std::string> elems;
			return split(s, delim, elems);
		}


		/**
		 * Checks, whether the given string is a number.
		 * @param s The string to be tested.
		 * @return
		 * TRUE - string is a number
		 * FALSE - string is not a number
		 */
		bool isNumber(const std::string& s)
		{
			return
				!s.empty() &&
				std::find_if(s.begin(), s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
		}


		/**
		 * Moves the specified camera in a sphere coordinate system about the given vector around the coordinate center.
		 * In order to preserve rounding errors when calculating from sphere coords to carthesian coords and back,
		 * the camera should be registered in the TripVarManager.
		 * @param cam the cam to be moved.
		 * @param vec The vector about which the object has to be moved.
		 * vec.x - radius
		 * vec.y - azimuth
		 * vec.z - inclination
		 * @param move_speed a multiplier that multiplies to the vector.
		 */
		void moveCameraSpherical( Ogre::Camera* cam,  Ogre::Vector3& vec, float move_speed)
		{
			TripVarManager* trip_vars = TripVarManager::instance();

			Ogre::Vector3& cam_pos_spherical = trip_vars->getCameraPositionSpherical( cam);

			cam_pos_spherical.x += vec.x * move_speed;
			cam_pos_spherical.y += vec.y * move_speed;
			cam_pos_spherical.z += vec.z * move_speed;

			if( cam_pos_spherical.x < 10)
				cam_pos_spherical.x = 10;
			if( cam_pos_spherical.z < 2)
				cam_pos_spherical.z = 2;
			else if( cam_pos_spherical.z > 178)
				cam_pos_spherical.z = 178;

			cam->setPosition(
				Ogre::Vector3( cam_pos_spherical.x * cosf( cam_pos_spherical.y TORAD)* sinf( cam_pos_spherical.z TORAD),
				cam_pos_spherical.x * cosf( cam_pos_spherical.z TORAD),
				cam_pos_spherical.x * sinf( cam_pos_spherical.y TORAD)* sinf( cam_pos_spherical.z TORAD)));
			cam->lookAt( Ogre::Vector3(0,0,0));
		}

		/**
		 * Moves the specified camera in a sphere coordinate system about the given vector around the coordinate center.
		 * In order to preserve rounding errors when calculating from sphere coords to carthesian coords and back,
		 * the camera should be registered in the TripVarManager.
		 * @param cam the cam to be moved.
		 * @param cam_pos_dim The dimension to use. Should be _cam_radius, _cam_azimuth or _cam_inclination.
		 * vec.x - radius
		 * vec.y - azimuth
		 * vec.z - inclination
		 * @param move_speed a multiplier that multiplies to the vector.
		 */
		void moveCameraSpherical( Ogre::Camera* cam, float& cam_pos_dim, float move_speed)
		{
			cam_pos_dim += move_speed*std::abs( move_speed)/100;

			Ogre::Vector3& cam_pos_spherical = TripVarManager::instance()->getCameraPositionSpherical( cam);

			if( cam_pos_spherical.x < 10)
				cam_pos_spherical.x = 10;
			if( cam_pos_spherical.z < 2)
				cam_pos_spherical.z = 2;
			else if( cam_pos_spherical.z > 178)
				cam_pos_spherical.z = 178;

			float x = cam_pos_spherical.x * cosf( cam_pos_spherical.y TORAD)* sinf( cam_pos_spherical.z TORAD);
			float y = cam_pos_spherical.x * sinf( cam_pos_spherical.y TORAD)* sinf( cam_pos_spherical.z TORAD);
			float z = cam_pos_spherical.x * cosf( cam_pos_spherical.z TORAD);

			cam->setPosition( Ogre::Vector3( x, z, y));
			cam->lookAt( Ogre::Vector3(0,0,0));
		}



	} // END namespace Util

} // END namespace Trip
