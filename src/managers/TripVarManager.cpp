/**
 * The TripVarManager class found in this file provides global access to the data
 * that is used within the Trip-framework.
 * @author barn
 * @version 20121023
 */

/*===========================================================================*
 * INCLUDES (associated header files)
 *===========================================================================*/
#include "TripVarManager.hpp"
#include <util/Math.hpp>

/*===========================================================================*
 * INCLUDES project headers
 *===========================================================================*/

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

	/**
	 * The singleton instance.
	 */
	TripVarManager* TripVarManager::__instance = 0;


	/**
	 * Main constructor.
	 */
	TripVarManager::TripVarManager()
	{
		Ogre::RenderWindow* win = Ogre::Root::getSingletonPtr()->getAutoCreatedWindow();
		_win_dimensions = std::pair<unsigned int,unsigned int>( win->getWidth(), win->getHeight());

		_cam_pos_spherical[0] = 0;
		_cam_pos_spherical[1] = 0;
		_cam_pos_spherical[2] = 0;

		_cam_speed = 0;
	}

	/**
	 * Destructor.
	 */
	TripVarManager::~TripVarManager()
	{
		// TODO
	}

	/**
	 * setCameraPositionSpherical
	 */
	void TripVarManager::setCameraPositionSpherical( Ogre::Camera* cam, float radius, float azimuth, float inclination)
	{
		Ogre::Vector3 pos;
		pos.x = radius;
		pos.y = azimuth;
		pos.z = inclination;

		//_cam_positions_spherical.insert( cam, pos);

		_cam_pos_spherical.x = radius;
		_cam_pos_spherical.y = azimuth;
		_cam_pos_spherical.z = inclination;
/*
		for( std::map< Ogre::Camera*, float[3]>::iterator it = _cam_positions_spherical.begin();
			it!=_cam_positions_spherical.end();
			it++)
		{
			if( it->first == cam)
			{
				it->second[0] = radius;
				it->second[1] = azimuth;
				it->second[2] = inclination;
				break;
			}
		}*/
	}

	/**
	 * getCameraPositionSpherical
	 */
	Ogre::Vector3& TripVarManager::getCameraPositionSpherical( Ogre::Camera* cam)
	{
		for( std::map< Ogre::Camera*, Ogre::Vector3>::iterator it = _cam_positions_spherical.begin();
			it!=_cam_positions_spherical.end();
			it++)
		{
			if( it->first == cam)
			{
				return it->second;
			}
		}

		return _cam_pos_spherical;

		// ERRORPRONE
	}


} // END namespace Trip
