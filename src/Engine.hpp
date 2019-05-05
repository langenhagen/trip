/**
 * This file contains the Engine class whose objects iterate over
 * a Cluster-tree and are able to process the Cluster's Transformers
 * on them. Actually, the Engine keeps it all rolling.
 * @author barn
 * @version 20121105
 */
#ifndef __Engine_HPP__
#define __Engine_HPP__

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
	class Cluster;

	/**
	 * The Engine class is able to iterate over a Tree of Clusters
	 * and process the Cluster's Transformers on them.
	 */
	class Engine : public Ogre::FrameListener
	{
	public: // constructor & destructor

		/**
		 * Main constructor.
		 */
		Engine()
		{}


		/**
		 * Destructor.
		 */
		~Engine()
		{}

	public: // methods

		/// Method derived by Ogre::FrameListener. Processes everything.
		bool frameRenderingQueued( const Ogre::FrameEvent& evt);

	private: // helpers

		/**
		 * Processes the transformers recursively on the whole tree.
		 * Iterates through the tree and applies higher level Transformers to every child Cluster,
		 * their children and so on.
		 * @param cluster The current cluster to process.
		 * @param context The list of clusters that are the parents of the current cluster.
		 * @param tlc The time since the last frame rendered.
		 */
		void process( Cluster* cluster, std::list<Cluster*> context, float tlc);


	}; // END class Engine

} // END namespace Trip

#endif /* __Engine_HPP__ */
