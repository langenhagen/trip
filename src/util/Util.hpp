/**
 * This file contains utility functions for the Trip framework.
 * @author barn
 * @version 20121027
 */
#ifndef __Util_HPP__
#define __Util_HPP__

/*===========================================================================*
 * INCLUDES base definition file for DLL import/export
 *===========================================================================*/

/*===========================================================================*
 * INCLUDES project headers
 *===========================================================================*/
 #include "stdafx.h"

/*===========================================================================*
 * INCLUDES C/C++ standard library (and other external libraries)
 *===========================================================================*/

/*===========================================================================*
 * DEFINES and MACROS
 *===========================================================================*/

/*===========================================================================*
 * NAMESPACE, CONSTANTS and TYPE DECLARATIONS/IMPLEMENTATIONS
 *===========================================================================*/

namespace Trip
{
	namespace Util
	{
		/*
		 * Checks, if a file with the specified path exists.
		 * @return
		 * TRUE - if the file exists
		 * FALSE - if the file doesn't exist
		 */
		bool fileExists( const char* file);

		/**
		 * Converts an integer value into a string.
		 * @param an arbitrary integer value.
		 * @return the specified integer value as a string.
		 */
		std::string itos( int i);

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
		void printList( const std::list<std::string> strings, unsigned char min_space = 3, bool expand_min_space = true, unsigned char max_line_size = 80);

		/**
		 * Splits a string at the specified delimeters and writes the results into the specified vector.
		 * @param s The string to split.
		 * @param delim The delimeter to use.
		 * @param elems The vector containing all substrings.
		*/
		std::vector<std::string>& split(const std::string& s, char delim, std::vector<std::string>& elems);

		/**
		 * Splits a string at the specified delimeters.
		 * @param s The string to split.
		 * @param delim The delimeter to use.
		 * @return A vector containing all substrings.
		 */
		std::vector<std::string> split(const std::string &s, char delim);


		/**
		 * Checks, whether the given string is a number.
		 * @param s The string to be tested.
		 * @return
		 * TRUE - string is a number
		 * FALSE - string is not a number
		 */
		bool isNumber(const std::string& s);

		/**
		* Moves a camera along the given vector in sphere coordinates.
		* @param cam the camera to be used. Must be registered in the TripVarManager.
		* @param vec the vector that shoud be used for movement. Beware of sphere coordinates (radius, azimuth, inclination)!
		* @param move_speed The speed with which to move the camera.
		*/
		void moveCameraSpherical( Ogre::Camera* cam,  Ogre::Vector3& vec, float move_speed = 1);

		/**
		* Moves a camera along the given dimension in spherical coordinates.
		* @param cam the camera to be used. Must be registered in the TripVarManager.
		* @param cam_pos_dim The dimension to use. Should be _cam_radius, _cam_azimuth or _cam_inclination.
		* @param move_speed The speed with which to move the camera.
		*/
		void moveCameraSpherical( Ogre::Camera* cam, float& cam_pos_dim, float move_speed = 1);

	} // END namespace Util

} // END namespace Trip

#endif /* __Util_HPP__ */
