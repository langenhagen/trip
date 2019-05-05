/**
 * Implementation file for ClusterManager.hpp.
 * @author barn
 * @version 20121027
 */

/*===========================================================================*
 * INCLUDES (associated header files)
 *===========================================================================*/
#include "ClusterManager.hpp"

/*===========================================================================*
 * INCLUDES project headers
 *===========================================================================*/
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
	/// The singleton instance.
	ClusterManager* ClusterManager::__instance = 0;


	/**
	 * Retrieves the singleton instance of the ClusterManager.
	 * Before you call this method, setup() should be called once.
	 * @param sceneManager The Ogre::SceneManager to which to connect the whole stuff.
	 * @return The singleton ClusterManager or NULL, if setup() is not called.
	 * @see setup()
	 */
	ClusterManager* ClusterManager::instance()
	{
		if ( __instance != 0)
		{
			return __instance;
		}
		else
		{
			Trip::log( "ClusterManager::instance(): ClusterManager not set up", MSG_ERROR);
			return 0;
		}
	}

	/**
	 * Adds a prototype Cluster to the manager. The same instance as the given
	 * will be taken as a prototype, so don't delete this pointer by yourself.
	 * At destruction time, the manager will take care of it.
	 * @param name The name of the prototype. Should be unique for the manager.
	 * in order to be stored. Also overrides the old name of the cluster with this new one.
	 * @param cluster The Cluster which shall be handled as a prototype.
	 * @return
	 * TRUE - if the element was stored successfully
	 * FALSE - if a prototype with the same name already exists. Nothing happens then.
	 */
	bool ClusterManager::addPrototype( const String& name, Cluster* cluster)
	{
		cluster->setName( name);
		return _prototypes.insert( std::pair< String, Cluster* >( name, cluster )).second;
	}

	/**
	 * Removes all prototypes from the manager and deletes them from memory.
	 */
	void ClusterManager::removeAllPrototypes()
	{
		for( auto it = _prototypes.begin(); it != _prototypes.end(); it++)
		{
			delete it->second;
		}
		_prototypes.clear();
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
	Cluster* ClusterManager::createCluster( const String& name, bool addToRootCluster)
	{
		auto it = _prototypes.find( name);

		if( it == _prototypes.end())
		{
			return 0;
		}

		Cluster* ret = it->second->clone();

		if(addToRootCluster)
		{
			_root_cluster->addCluster( ret);
		}

		return ret;
	}

	/**
	 * Creates a random Cluster from a prototype.
	 * @return A new Cluster that is a clone of some prototype.
	 * Returns NULL if there are no prototypes.
	 */
	Cluster* ClusterManager::createRandomCluster()
	{
		if( _prototypes.size() == 0)
		{
			return 0;
		}

		auto it = _prototypes.begin();

		int num = std::rand() % _prototypes.size();
		for( int i = 0; i < num; i++)
		{
			it++;
		}

		return it->second->clone();
	}

	/**
	 * Retrieves the list of all available Cluster's names.
	 * @return A list of the names of the available Clusters.
	 * @see addPrototype()
	 */
	std::list<String> ClusterManager::getClusterNameList()
	{
		std::list<String> ret;

		for( auto it= _prototypes.begin(); it != _prototypes.end(); it++)
		{
			ret.push_back( it->first);
		}

		return ret;
	}


} // END namespace Trip
