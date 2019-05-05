/**
 * This file contains the ClusterManager that creates new Clusters from Prototypes.
 * @author barn
 * @version 20121027
 */
#ifndef __ClusterManager_HPP__
#define __ClusterManager_HPP__

/*===========================================================================*
 * INCLUDES base definition file for DLL import/export
 *===========================================================================*/

/*==================d=========================================================*
 * INCLUDES project headers
 *===========================================================================*/
#include "stdafx.h"
#include <clusters/Cluster.hpp>

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
	 * This class is able to create Clusters from prototypes that can be registered at runtime.
	 * Use this class is you want to create Clusters.
	 */
	class ClusterManager
	{

	private: // class vars

		/// The singleton instance.
		static ClusterManager* __instance;

	private: // instance vars

		/// This map stores the names and their corresponding prototype Clusters.
		std::map< String, Cluster* > _prototypes;

		/// This is the root Cluster, from where the Engine begins to iterate through all Clusters.
		Cluster* _root_cluster;

	protected: // constructor

		/**
		 * Protected main constructor.
		 * @param sceneManager The Ogre::SceneManager to which to connect the whole stuff.
		 */
		ClusterManager( Ogre::SceneManager* sceneManager)
			: _root_cluster( new Cluster( sceneManager, "root"))
		{}

	public: // destructor

		/**
		 * Destructor.
		 */
		~ClusterManager()
		{
			removeAllPrototypes();

			__instance = 0;
		}

	public: // class methods

		/**
		 * Sets up the singleton instance of the ClusterManager.
		 * Only sets it up, if the singleton instance is NULL.
		 * @param sceneManager The Ogre::SceneManager to which to connect the whole stuff.
		 * @return The singleton ClusterManager.
		 * @see instance()
		 */
		static ClusterManager* setup( Ogre::SceneManager* sceneManager)
		{
			if (__instance == 0)
				__instance = new ClusterManager(sceneManager);
			return __instance;
		}

		/**
		 * Retrieves the singleton instance of the ClusterManager.
		 * Before you call this method, setup() should be called once.
		 * @param sceneManager The Ogre::SceneManager to which to connect the whole stuff.
		 * @return The singleton ClusterManager or NULL, if setup() is not called.
		 * @see setup()
		 */
		static ClusterManager* instance();


	public: // methods

		/**
		 * Adds a prototype Cluster to the manager. The same instance as the given
		 * will be taken as a prototype, so don't delete this pointer by yourself.
		 * At destruction time, the manager will take care of it.
		 * @param name The name of the prototype. Should be unique for the manager.
		 * in order to be stored.
		 * @param cluster The Cluster which shall be handled as a prototype.
		 * @return
		 * TRUE - if the element was stored successfully
		 * FALSE - if a prototype with the same name already exists. Nothing happens then.
		 */
		bool addPrototype( const String& name, Cluster* cluster);

		/**
		 * Adds a prototype Cluster to the manager. The same instance as the given
		 * will be taken as a prototype, so don't delete this pointer by yourself.
		 * At destruction time, the manager will take care of it. The name of the prototype will
		 * be the name property of the given cluster.
		 * @param cluster The Cluster which shall be handled as a prototype.
		 * @return
		 * TRUE - if the element was stored successfully
		 * FALSE - if a prototype with the same name already exists. Nothing happens then.
		 */
		bool addPrototype( Cluster* cluster)
		{
			return addPrototype( cluster->getName(), cluster);
		}


		/**
		 * Removes all prototypes from the manager and deletes them from memory.
		 */
		void removeAllPrototypes();

		/**
		 * Removes the specified prototype from the manager.
		 * If some prototype is specified that doesn't exist in the list,
		 * nothing happens.
		 * @param name The name of the prototype which is to be deleted.
		 */
		void removePrototype( const String& name)
		{
			// TODO verify in error case
			delete _prototypes.find( name)->second;
			_prototypes.erase(
				_prototypes.find( name));
		}

		/**
		 * Creates a Cluster from a prototype.
		 * Beware that this method does no error checking if a prototype does really exist.
		 * @param name The name of the prototype which is to be used for creation.
		 * @param addToRootCluster Specifies, if the created Cluster shall be added to the
		 * root Cluster, so that the created Cluster and all its child Clusters will be
		 * processed by the Engine. When added to the Root Cluster the ClusterManager is able
		 * to keep track of this Cluster and its children through its root Cluster.
		 * @return A new Cluster that should be a clone of the given prototype.
		 * Returns NULL when the specified name does not match any prototype.
		 * @see getRootCluster()
		 * @see addPrototype()
		 */
		Cluster* createCluster( const String& name, bool addToRootCluster = false);

		/**
		 * Creates a random Cluster from a prototype.
		 * @return A new Cluster that is a clone of some prototype.
		 * Returns null, if there are no prototypes.
		 */
		Cluster* createRandomCluster();

		/**
		 * Retrieves the list of all available Cluster's names.
		 * @return A list of the names of the available Clusters.
		 * @see addPrototype()
		 */
		std::list<String> getClusterNameList();

		/**
		 * Retrieves the root Cluster on which the Engine begins iterating through all connected Clusters.
		 * @return The root Cluster.
		 */
		Cluster* getRootCluster()
		{
			return _root_cluster;
		}


	}; // END class ClusterManager

} // END namespace Trip

#endif /* __ClusterManager_HPP__ */
