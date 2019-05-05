/**
 * This file containst the Context class that stores the context of Trip.
 * Also stores the ContextType enum.
 * @author barn
 * @version 20121113
 */
#ifndef __Context_HPP__
#define __Context_HPP__

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
	class Transformer;

	/**
	 * This enum describes things that can be the context of the current
	 * Situation in the console interpreter. Depending on what context
	 * is active, different commands are possible.
	 */
	enum ContextType
	{
		ROOT = 0x03, //< also a CLUSTER
		CLUSTER = 0x02,
		TRANSFORMER = 0x04
	}; // END enum ContextType

	/**
	 * This class represents the concrete context of the current selected things in Trip.
	 */
	class Context
	{
	protected: // members

		/// The context in which the Console is at the moment.
		ContextType _context_type;

		/**
		 * The currently selected Cluster (cluster_list.back())
		 * and the Clusters that come before this one in the hierarchy.
		 * The root Cluster is cluster_list.front().
		 */
		std::list<Cluster*> _context_cluster_list;

		/// The currently selected transformer (should be null if no transformer is selected).
		Transformer* _context_transformer;

	public: // constructor & destructor

		/// Main constructor.
		Context()
			: _context_type(ROOT), _context_transformer(0)
		{}

		/// Destructor.
		~Context()
		{}

	public: // methods

		/**
		 * Updates the current context.
		 */
		void updateContextType();

		/**
		 * Indicates, if the current internal context type is equal to the given context.
		 * @param context A ContextType with wich to compare the current internal context type.
		 * @return
		 * TRUE - the internal context type matches the given one.
		 * FALSE - the internal context type does not match the given one.
		 */
		bool isContext( ContextType type)
		{
			return (_context_type & type) == type;
		}

		/**
		 * Builds and retrieves a string that defines the current context.
		 * @return A string that shows the current context.
		 */
		virtual String getContextString();

		/**
		 * Sets the context in its hierarchy one step higher.
		 * E.g. sets the parent Cluster of the former current
		 * Cluster to the current one.
		 */
		void contextLevelUp();

	public: // getters & setters

		/**
		 * Retrieves the current context type.
		 * Retrieves the ContextType enum value to the current context.
		 * @return The current context type.
		 */
		ContextType getContextType()
		{
			return _context_type;
		}

		/**
		 * Retrieves the list of Clusters in the context.
		 * This list should represent a hierarchy between Clusters,
		 * e.g. further Clusters in the list are children of the Clusters before.
		 * @return A cluster list representing the hierarchical context.
		 * The end of the list should be the current Cluster,
		 * the beginning the root Cluster
		 */
		std::list<Cluster*>& getClusterList()
		{
			return _context_cluster_list;
		}

		/**
		 * Retrieves the selected current Transformer, if there is any.
		 * @Return the selected Transformer, which shall be current context
		 * or NULL if, at the moment, there is no Transformer selected.
		 */
		Transformer* getSelectedTransformer()
		{
			return _context_transformer;
		}


	}; // END class Context

} // END namespace Trip

#endif /* __Context_HPP__ */
