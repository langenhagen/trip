/**
 * The implementation file of the Cluster.hpp header.
 * @author barn
 * @version 20121027
 */

/*===========================================================================*
 * INCLUDES (associated header files)
 *===========================================================================*/
#include "Cluster.hpp"

/*===========================================================================*
 * INCLUDES project headers
 *===========================================================================*/
#include <managers/ClusterManager.hpp>

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
	 * Creates all the stuff the cluster contains.
	 * Also performs setup() on all the internal stored Clusters.
	 */
	void Cluster::setup()
	{
		doSetup();

		// create all internal clusters.
		for( auto it = _clusters.begin(); it != _clusters.end(); ++it)
		{
			(*it)->setup();
		}
	}

	/**
	 * Convenience function that creates an Ogre::SceneNode and adds it to the Node List of the Cluster.
	 * @param name The name of the SceneNode.
	 * @param translate Initial translation offset of child relative to parent.
	 * @param rotate Initial rotation relative to parent.
	 */
	Ogre::SceneNode* Cluster::createSceneNode( const String& name, const Ogre::Vector3& translate, const Ogre::Quaternion& rotate)
	{
		Ogre::SceneNode* ret = _scene_manager->getRootSceneNode()->createChildSceneNode( name, translate, rotate);
		_nodes.push_back( ret);
		return ret;
	}

	/**
	 * Creates a Ogre::SceneNode and adds it to the Node List of the corresponding Cluster.
	 * @param translate Initial translation offset of child relative to parent.
     * @param rotate Initial rotation relative to parent.
	 */
	Ogre::SceneNode* Cluster::createSceneNode( const Ogre::Vector3& translate, const Ogre::Quaternion& rotate)
	{
		Ogre::SceneNode* ret = _scene_manager->getRootSceneNode()->createChildSceneNode( translate, rotate);
		_nodes.push_back( ret);
		return ret;
	}


	/**
	 * Clears all nodes from this Cluster and deletes them.
	 */
	void Cluster::clearAllNodes()
	{
		for( auto it = _nodes.begin(); it != _nodes.end(); ++it)
		{
			delete *it;
		}
		_nodes.clear();
	}

	/**
	 * Retrieves a child Cluster from the given position. Linear complexity.
	 * @return A Cluster or NULL if there is no cluster at a given position.
	 */
	Cluster* Cluster::getCluster( uint pos)
	{
		if( pos >= _clusters.size())
			return NULL;

		ClusterList::iterator it;
		for( it = _clusters.begin(); it != _clusters.end(); ++it)
		{
			if( pos == 0)
			{
				break;
			}
			--pos;
		}
		return *it;
	}


	/**
	 * Removes the given cluster from the child list and retrieves it. Linear complexity.
	 * @param pos The position of the Cluster in the child Cluster list.
	 * Must be between 0 and the value returned by getClusterListSize().
	 * If the value is larger than the child cluster list, nothing happens.
	 * @return the Cluster that is removed from the list of child Clusters or NULL if 
	 * the specified position exceeds the number of clusters.
	 * @see getClusterListSize()
	 */
	Cluster* Cluster::removeCluster( uint pos)
	{
		if( pos >= _clusters.size())
			return 0 ;

		auto it = _clusters.begin();
		for( uint i=1; i<pos; ++i)
		{
			++it;
		}

		Cluster* cluster = *it;
		_clusters.remove( *it);
		return cluster;
	}


	/**
	 * Adds a Transformer to the specified position. Relatively high complexity.
	 * @param transformer The Transformer to be added.
	 * @param pos The position of the transformer to be added.
	 * If the given position is bigger than the size of the list of transformers,
	 * the transformer will be added to the back of the list.
	 */
	void Cluster::addTransformer( Transformer* transformer, uint pos)
	{
		if( pos >= _transformers.size())
		{
			_transformers.push_back( transformer);
		}else
		{
			_transformers.insert( _transformers.begin() + pos, transformer);
		}
	}


	/**
	 * Removes the Transformer at the given position and retrieves it.
	 * If the specified position is not in the scope of the Transformers vector,
	 * NULL will be returned.
	 * @param pos the Position of the Transformer to remove.
	 * Retruns the removed Transformer or NULL, if the given pos exceeds the length of the Transformer vector.
	 * @see getAllTransformers()
	 */
	Transformer* Cluster::removeTransformer( uint pos)
	{
		if( pos >= _transformers.size())
			return 0;

		auto ptr = _transformers.begin() + pos;
		Transformer* transformer = *ptr;
		_transformers.erase( ptr);
		return transformer;
	}


	/**
	 * Removes the given Transformer, but does not destroy it.
	 * Does nothing if the given Transformer is not attached to the Cluster.
	 * @param t The Transformer to remove.
	 */
	void Cluster::removeTransformer( Transformer* t)
	{
		for( auto it = _transformers.begin(); it != _transformers.end(); ++it)
		{
			if ( *it == t)
			{
				Transformer* transformer = *it;
				_transformers.erase( it);
				break;
			}
		}
	}

	/**
	 * Clears the whole Transformer vector & deletes the transformers.
	 * therefore clears all first-class transformers from this Cluster.
	 */
	void Cluster::clearAllTransformers()
	{
		for( auto it = _transformers.begin(); it != _transformers.end(); ++it)
		{
			delete *it;
		}
		_transformers.clear();
	}


	/** 
	 * Creates a Cluster with the specified name and attaches it to the list of Clusters.
	 * @param name The name of the Cluster to create.
	 */
	void Cluster::createCluster( const String& name)
	{
		_clusters.push_back( Trip::ClusterManager::instance()->createCluster( name));
	}


} // END namespace Trip
