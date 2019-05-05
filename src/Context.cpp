/**
 * Implementation file for the Context.hpp.
 * @author barn
 * @version 20121113
 */

/*===========================================================================*
 * INCLUDES (associated header files)
 *===========================================================================*/
#include "Context.hpp"

/*===========================================================================*
 * INCLUDES project headers
 *===========================================================================*/
#include <clusters/Cluster.hpp>
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

	/**
	 * Updates the current context.
	 */
	void Context::updateContextType()
	{
		if( _context_transformer)
		{
			_context_type = TRANSFORMER;
		}
		else
		{
			_context_type = _context_cluster_list.size() > 1 ? CLUSTER : ROOT;
		}
	}

	/**
	 * Builds and retrieves a string that defines the current context.
	 * @return A string that shows the current context.
	 */
	String Context::getContextString()
	{
		String ret = "";

		for( auto it = _context_cluster_list.begin(); it != _context_cluster_list.end(); ++it)
		{
			ret.append("c ");
			ret.append( (*it)->getName());
			ret.append( "::");
		}

		if( this->isContext( TRANSFORMER))
		{
			ret.append("t ");
			ret.append( _context_transformer->getName());
			ret.append(":");
		}

		ret.append(" ");

		return ret;
	}

	/**
	 * Sets the context in its hierarchy one step higher.
	 * E.g. sets the parent Cluster of the former current
	 * Cluster to the current one.
	 */
	void Context::contextLevelUp()
	{
		if( isContext(ROOT))
		{
			/* DO NOTHING */
		}
		else if( isContext(CLUSTER))
		{
			_context_cluster_list.pop_back();
		}
		else if( isContext( TRANSFORMER))
		{
			_context_transformer = 0;
		}

		_context_type = _context_cluster_list.size() > 1 ? CLUSTER : ROOT;
	}

} // END namespace Trip
