/**
 * This file contains of a class that saves global resources
 * that don't come with the ogre framework.
 * @author barn
 * @version 20121023
 */
#ifndef __TripVarManager_HPP__
#define __TripVarManager_HPP__

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

	/**
	 * This class is a resource manager for global resources in the TRiP framework.
	 */
	class TripVarManager
	{
	private: // class vars

		/// The singleton instance.
		static TripVarManager* __instance;

	private: // instance vars

		/// Saves the measures of the window when switching to full screen mode and back.
		std::pair<unsigned int,unsigned int> _win_dimensions;

		/// Stores the SceneManager
		Ogre::SceneManager* _scene_manager;

	public: // instance vars // TODO put them into private

		/// The spherical coordinates of the camera. radius - azimuth - inclination.
		Ogre::Camera* _cam;
		Ogre::Vector3 _cam_pos_spherical;
		std::map< Ogre::Camera*, Ogre::Vector3> _cam_positions_spherical;

		float _cam_speed;

	protected: // constructor

		/**
		 * Protected main constructor.
		 */
		TripVarManager();

	public: // destructor

		/**
		 * Destructor.
		 */
		~TripVarManager();

	public: // class methods

		/**
		 * Retrieves the singleton instance of the TripVarManager.
		 * Also does the lazy initialization.
		 */
		static TripVarManager* instance()
		{
			if (__instance == 0)
				__instance = new TripVarManager();
			return __instance;
		}

	public: // getters & setters

		/**
		 * Sets the window dimensions.
		 */
		void setWinDimensions( unsigned int winWidth, unsigned int winHeight)
		{
			_win_dimensions = std::pair<unsigned int,unsigned int>( winWidth, winHeight);
		}

		/**
		 * Sets the window dimensions.
		 */
		void setWinDimensions( const std::pair<unsigned int,unsigned int>& winDimensions)
		{
			_win_dimensions = winDimensions;
		}

		/**
		 * Retrieves the window dimensions.
		 * @return A pair consisting the window dimensions.
		 * The first value will be the width in pixels, the second the height, also in pixels.
		 */
		const std::pair<unsigned int,unsigned int>& getWinDimensions()
		{
			return _win_dimensions;
		}

		/**
		 * Sets the scene manager of the Trip system.
		 * @param the Ogre scene manager to be used.
		 */
		void setSceneManager( Ogre::SceneManager* scene_manager)
		{
			_scene_manager = scene_manager;
		}

		/**
		 * Retrieves the scene manager.
		 * @Return The scene manager.
		 */
		Ogre::SceneManager* getSceneManager()
		{
			return _scene_manager;
		}

		/**
		 * Sets the camera position in a spherical manner around the coordinate center.
		 * Does not really affect the camera itself, but the spherical coordinates, which you can
		 * use manually, or which will be used by some functions like the se Trip::moveCameraSpherical().
		 * @param cam The camera to use.
		 */
		void setCameraPositionSpherical( Ogre::Camera* cam,  float radius, float azimuth, float inclination);

		/**
		 * Retrieves the camera position in sphere coordinates.
		 * @param cam The camera to use.
		 * @return The spherical coordinates in a vector:
		 * x = radius, y = azimuth, z = inclination.
		 */
		Ogre::Vector3& getCameraPositionSpherical( Ogre::Camera* cam);

		/**
		 * Sets the currently active cam.
		 * @param cam The cam.
		 */
		void setCam( Ogre::Camera* cam)
		{
			_cam = cam;
		}

		/**
		 * Returns the currently active cam.
		 */
		Ogre::Camera* getCam()
		{
			return _cam;
		}

	}; // END class TripVarManager

} // END namespace Trip

#endif /* __TripVarManager_HPP__ */
