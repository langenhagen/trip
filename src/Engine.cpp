/**
 * Implementation file for the Engine.hpp.
 * @author barn
 * @version 20121105
 */

/*===========================================================================*
 * INCLUDES (associated header files)
 *===========================================================================*/
#include "Engine.hpp"

/*===========================================================================*
 * INCLUDES project headers
 *===========================================================================*/
#include <managers/ClusterManager.hpp>
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
	/// Method derived by Ogre::FrameListener. Processes everything
	bool Engine::frameRenderingQueued( const Ogre::FrameEvent& evt)
	{
		Cluster* root = ClusterManager::instance()->getRootCluster();
		if( root->isEnabled())
		{
			process( root, std::list<Cluster*>(), evt.timeSinceLastFrame);
		}

		return true;
	}


	/**
	 * Processes the transformers recursively on the whole tree.
	 * Iterates through the tree and applies higher level Transformers to every child Cluster,
	 * their children and so on.
	 * @param cluster The current cluster to process.
	 * @param context The list of clusters that are the parents of the current cluster.
	 * @param tlc The time since the last frame rendered.
	 */
	void Engine::process( Cluster* cluster, std::list<Cluster*> context, float tlc)
	{
		context.push_back( cluster);

		// apply all transformers on cluster's nodes
		uint i = 0;
		auto node_list = cluster->getNodes();
		for( auto node_it = node_list.begin(); node_it != node_list.end(); ++node_it)
		{
			for( auto context_it = context.begin(); context_it != context.end(); ++context_it)
			{
				auto transformer_vec = (*context_it)->getAllTransformers();
				for( auto transformer_it = transformer_vec.begin(); transformer_it != transformer_vec.end(); ++transformer_it)
				{
					Transformer* transformer = *transformer_it;
					if( transformer->isEnabled())
					{
						transformer->transform( *node_it, tlc, i);
					}
				}
			}
			++i;
		}

		// process child clusters of current cluster
		auto child_cluster_list = cluster->getAllClusters();
		for( auto cluster_it = child_cluster_list.begin(); cluster_it != child_cluster_list.end(); ++cluster_it)
		{
			Cluster* child_cluster = *cluster_it;
			if( child_cluster->isEnabled())
			{
				process( *cluster_it, context, tlc);
			}
		}
	}


} // END namespace Trip
