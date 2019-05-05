/**
 * This filecontains a bunch of Clusters.
 * @author barn
 * @version 20121107
 */
#ifndef __Clusters1_HPP__
#define __Clusters1_HPP__

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
#include <clusters/Cluster.hpp>


/*===========================================================================*
 * DEFINES and MACROS
 *===========================================================================*/
 
/*===========================================================================*
 * NAMESPACE, CONSTANTS and TYPE DECLARATIONS/IMPLEMENTATIONS
 *===========================================================================*/

/*****************************************************************************
 
	/// comment
	class XXXCluster : public Trip::Cluster
	{
		Cluster* clone()
		{
			return new XXXCluster( *this);
		}

		void doSetup()
		{
	
		}
	};
 
******************************************************************************/
 
namespace Trip
{
	/// A single big Schnecki
	class SchneckiCluster : public Trip::Cluster
	{
		Cluster* clone()
		{
			return new SchneckiCluster( *this);
		}

		void doSetup()
		{
			Ogre::SceneNode* schnecknode = createSceneNode();
			Ogre::Entity* schnecke = _scene_manager->createEntity( "3dschnecki.mesh");
			schnecknode->attachObject(schnecke);
		}
	};

	
} // END namespace Trip

#endif /* __Clusters1_HPP__ */
