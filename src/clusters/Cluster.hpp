/**
 * This file contains the class Cluster, which encapsulates the geometry of the rendered scene.
 * @author barn
 * @version 20121027
 */
#ifndef __Cluster_HPP__
#define __Cluster_HPP__

/*===========================================================================*
 * INCLUDES base definition file for DLL import/export
 *===========================================================================*/
 
/*===========================================================================*
 * INCLUDES project headers
 *===========================================================================*/
#include "stdafx.h"
#include <Fadeable.hpp>
#include <managers/TripVarManager.hpp>
#include <transformers/Transformer.hpp>


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
	class Cluster;

	/// A list of SceneNodes
	typedef std::list< Ogre::SceneNode*> NodeList;

	/// A list of Clusters
	typedef std::list< Cluster*> ClusterList;

	/// A vector of Transformers
	typedef std::vector< Transformer*> TransformerVector;


	/**
	 * This class encapsulates the geometry of a scene. 
	 * It contains of (almost) all the Nodes, Entities and so on that you want to have in your scene.
	 * You are able to combine several Cluster instances in order to create more complex scenes through its 
	 * compositor abilities. Cluster objects manage several Ogre::Nodes and other Clusters.
	 * 
	 * In general, you should not create the Clusters manually, but
	 * use the ClusterManager, that uses the Prototype pattern to create Clusters
	 * at runtime. Since you specify some prototypes of your Clusters for the Manager
	 * (that clones them when asked to create a new object), you have to take care 
	 * that the copy constructor works the correct way. As long as you are not using raw pointers,
	 * or a shallow copy is sufficient, everything is fine. But when you are doing more complex stuff,
	 * and you need some complex members to be copied correctly, please implement an explicit copy constructor
	 * in your child class.
	 *
	 * When you create your own subclasses, you should override those 2 methods: 
	 * doSetup() - sets the scene and everything up
	 * clone() - clones the current object in order to be used as a prototype for the ClusterManager
	 * 
	 * When you handle everything by the book, you only need to override doSetup() and clone().
	 * doSetup() shall set the scene up and fill the instance vars, lists and vectors.
	 * However, if you have some initial or special instance vars that shall be copied at construction time, 
	 * you have to override the copy constructor: Cluster( const Cluster&).
	 *
	 * @see doSetup()
	 * @see clone()
	 */
	class Cluster : public Fadeable
	{
	
	protected: // vars

		Ogre::SceneManager* _scene_manager;

		/// The name of this Cluster.
		String _name;
		
		/// All child Clusters of this Cluster.
		ClusterList _clusters;  // TODO BEWARE OF SHALLOW COPY!!!

		// All Nodes of this Cluster.
		NodeList _nodes;

		/// Intentionally the Material all nodes of _nodes have.
		Ogre::Material* _material;

		/// All Transformers that will be applied on the Nodes of the NodeGroups.
		TransformerVector _transformers;


	public: // constructor & destructor

		/**
		 * Main Constructor.
		 */
		Cluster()
			: _name("zero"),
			_scene_manager( TripVarManager::instance()->getSceneManager())
		{}

		/**
		 * 2nd Constructor.
		 */
		Cluster( Ogre::SceneManager* sceneManager)
			: _name("zero"),
			_scene_manager( sceneManager)
		{}

		/**
		 * 3rd Constructor.
		 */
		Cluster( Ogre::SceneManager* sceneManager, const String& name)
			: _name(name),
			_scene_manager( sceneManager)
		{}

		/**
		 * Destructor.
		 * Deletes the Clusters, Nodes, and the Transformers. 
		 */
		~Cluster()
		{
			// delete Clusters
			for( auto it = _clusters.begin(); it != _clusters.end(); ++it)
			{
				delete *it;
			}
			_clusters.clear();

			// delete Nodes
			for( auto it = _nodes.begin(); it != _nodes.end(); ++it)
			{
				_scene_manager->destroySceneNode( *it);
			}
			_nodes.clear();

			// delete Transformers
			for( auto it = _transformers.begin(); it != _transformers.end(); ++it)
			{
				delete *it;
			}
			_transformers.clear();
		}

	public: // methods

		/**
		 * Clones the Cluster. Override this method in order to use prototypes of your own subclass.
		 * Beware of usage of the copy constructor! After getting a clone of your special subclass,
		 * you can use the setup() method to fill the lists and set up the whole thing.
		 */
		virtual Cluster* clone()
		{
			return new Cluster( *this);
		}

		/**
		 * Creates all the stuff the cluster contains.
		 * Also performs setup() on all the internal stored Clusters.
		 */
		void setup();

		/**
		 * Creates a Ogre::SceneNode and adds it to the Node List of the corresponding Cluster.
		 * @param name The name of the SceneNode.
		 * @param translate Initial translation offset of child relative to parent.
         * @param rotate Initial rotation relative to parent.
		 */
		Ogre::SceneNode* createSceneNode( const String& name, const Ogre::Vector3& translate = Ogre::Vector3::ZERO, const Ogre::Quaternion& rotate = Ogre::Quaternion::IDENTITY);

		/**
		 * Creates a Ogre::SceneNode and adds it to the Node List of the corresponding Cluster.
		 * @param translate Initial translation offset of child relative to parent.
         * @param rotate Initial rotation relative to parent.
		 */
		Ogre::SceneNode* createSceneNode( const Ogre::Vector3& translate = Ogre::Vector3::ZERO, const Ogre::Quaternion& rotate = Ogre::Quaternion::IDENTITY);

		/** 
		 * Creates a child Cluster with the specified name and attaches it to the list of Clusters.
		 * @param name The name of the Cluster to create.
		 */
		void createCluster( const String& name);

	public: // getters & setters


		/**
		 * This function sets the name of this particular Cluster.
		 * @param name The new name of the Cluster.
		 */
		void setName( String name)
		{
			_name = name;
		}


		/**
		 * Retrieves the name of this Cluster.
		 * @return The current name of this Cluster.
		 */
		const String& getName()
		{
			return _name;
		}


		/**
		 * Retrieves the list of nodes that are direct within this Cluster.
		 * @return the List of Ogre::Nodes that belong to this Cluster.
		 */
		const NodeList& getNodes()
		{
			return _nodes;
		}


		/**
		 * Clears all nodes from this Cluster and deletes them.
		 */
		void clearAllNodes();


		/**
		 * Adds a Cluster to this Cluster.
		 * @param cluster The new cluster to add.
		 */
		void addCluster( Cluster* cluster)
		{
			_clusters.push_back( cluster);
		}
		
		
		/**
		 * Retrieves a Cluster from the given position. Linear complexity.
		 * @return A Cluster or NULL if there is no cluster at a given position.
		 */
		Cluster* getCluster( uint pos);

		/**
		 * Retrieves a child Cluster from the given position. Linear complexity.
		 * @return A Cluster or NULL if there is no cluster at a given position.
		 */
		Cluster* operator[](uint pos)
		{
			getCluster( pos);
		}


		/**
		 * Retrieves a list of all direct child Clusters within this particular Cluster.
		 * @return A list all first-class child Clusters.
		 */
		const ClusterList& getAllClusters()
		{
			return _clusters;
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
		Cluster* removeCluster( uint pos);
		
		/**
		 * Removes the given cluster from the child list, but doesnt call its destrutor.
		 * Linear complexity.
		 * @param cluster The Cluster to remove from the child Cluster list.
		 * If that particular value is not in the list, nothing happens.
		 */
		void removeCluster( Cluster* cluster)
		{
			_clusters.remove( cluster);
		}
		

		/**
		 * Adds a Transformer to the Cluster.
		 * @param transformer The Transformer to be added.
		 */
		void addTransformer( Transformer* transformer)
		{
			_transformers.push_back( transformer);
		}

		/**
		 * Adds a Transformer to the specified position. Relatively high complexity.
		 * @param transformer The Transformer to be added.
		 * @param pos The position of the transformer to be added.
		 * If the given position is bigger than the size of the list of transformers,
		 * the transformer will be added to the back of the list.
		 */
		void addTransformer( Transformer* transformer, uint pos);
		
		/**
		 * Retrieves a transformer with at the specified position.
		 * @param pos The position of the Transformer in the vector of transformers.
		 * Must be smaller than the number of elements in this vector.
		 * @return Returns the indexed Transformer.
		 * @see getAllTransformers()
		 */
		Transformer* getTransformer( uint pos)
		{
			return _transformers.at( pos);
		}
		
		/**
		 * Retrieves all first-class Transformers in their vector.
		 */
		const TransformerVector& getAllTransformers()
		{
			return _transformers;
		}

		/**
		 * Removes the Transformer at the given position and retrieves it.
		 * If the specified position is not in the scope of the Transformers vector,
		 * NULL will be returned.
		 * @param pos the Position of the Transformer to remove.
		 * Retruns the removed Transformer or NULL, if the given pos exceeds the length of the Transformer vector.
		 * @see getAllTransformers()
		 */
		Transformer* removeTransformer( uint pos);

		/**
		 * Removes the given Transformer, but does not destroy it.
		 * Does nothing if the given Transformer is not attached to the Cluster.
		 * Linear complexity.
		 * @param t The Transformer to remove.
		 */
		void removeTransformer( Transformer* t);

		/**
		 * Clears the whole Transformer vector & 
		 * therefore clears all first-class transformers from this Cluster.
		 */
		void clearAllTransformers();

		/**
		 * Sets the material for all nodes.
		 * Note that this method does not delete the last used material.
		 * @param material The new material to use.
		 *
		 * @see getMaterial()
		 */
		void setMaterial( Ogre::Material* material)
		{
			_material = material;

			for( auto it = _nodes.begin(); it != _nodes.end(); ++it)
			{
				// TODO
			}
		}

		/**
		 * Retrieves the Ogre::Material all first-class nodes of this Cluster should have.
		 * @return An Ogre::Material.
		 */
		Ogre::Material* getMaterial()
		{
			return _material;
		}

		
	protected: // helpers

		/**
		 * Creates all the stuff the particular Cluster contains.
		 * Build your scene nodes here, attach them to the NodeList,
		 * Generate internal Clusters here and add them to the ClusterList.
		 * Do not call create on the internal Clusters, 
		 * that will be done externally by the setup() method of this object.
		 * Feel free to use the helper methods createSceneNode() and createCluster().
		 *
		 * @see setup()
		 * @see createSceneNode()
		 * @see createCluster()
		 */
		virtual void doSetup()
		{
			/* EMPTY IMPLEMENTATION */
		}


	}; // END class Cluster
	
} // END namespace Trip

#endif /* __Cluster_HPP__ */
