/**
 * This file contains an interpreter that can be used 
 * for console or script input in the Trip application.
 * @author barn
 * @version 20121030
 */
#ifndef __ConsoleInterpreter_HPP__
#define __ConsoleInterpreter_HPP__

/*===========================================================================*
 * INCLUDES base definition file for DLL import/export
 *===========================================================================*/
 
/*===========================================================================*
 * INCLUDES project headers
 *===========================================================================*/
#include "stdafx.h"
#include <Enableable.hpp>
#include <Context.hpp>
#include <util/Util.hpp>
#include <managers/ClusterManager.hpp>
#include <clusters/Cluster.hpp>
#include <transformers/Transformer.hpp>

/*===========================================================================*
 * INCLUDES C/C++ standard library (and other external libraries)
 *===========================================================================*/
#include <boost/function.hpp>

/*===========================================================================*
 * DEFINES and MACROS
 *===========================================================================*/

// argument of the callbacks for convenience
#define ARGS std::vector<String>& args


/*===========================================================================*
 * NAMESPACE, CONSTANTS and TYPE DECLARATIONS/IMPLEMENTATIONS
 *===========================================================================*/

namespace Trip
{
	class ConsoleInterpreter;

	// pointer to a bool foo(vector<String>) member function of ConsoleInterpreter
	typedef bool (ConsoleInterpreter::*ConsoleCallback)( std::vector<String>& args);

	/**
	 * This class implements a console that you can use in the Trip context.
	 */
	class ConsoleInterpreter : public Trip::Enableable, public Trip::Context
	{
	protected: //vars
		
		/// Stores the initial console input strings and their corresponding callbacks.
		std::map<String, ConsoleCallback> _callback_map;

	public: // constructor & destructor

		/**
		 * Main constructor.
		 * Make sure the ClusterManager is already set up.
		 * @param pathToSyntaxFile The path of the syntax config file where
		 * the syntaxes are specified.
		 * @param syntax The specific syntax to be used. Must be defined 
		 * in the syntax file.
		 */
		ConsoleInterpreter( const String& pathToSyntaxFile, const String& syntax)
		{
			_context_cluster_list.push_back( ClusterManager::instance()->getRootCluster());

			setup( pathToSyntaxFile, syntax);
		}
		
		/**
		 * Destructor.
		 */
		~ConsoleInterpreter()
		{}
	

	public: // methods

		/**
		 * Interpretes a given input string and manipulates Trip according to that input.
		 * @param str An input string that is to be interpreted.
		 * @return Indicates, whether the input string could be processed correctly or not.
		 * TRUE - input could be processed
		 * FALSE - input could not be processed due to syntax errors or due to wrong context.
		 */
		virtual bool interprete( std::string& str);

		/**
		 * Assigns a callback to a string element.
		 * Override this method in your subclass.
		 * @param pathToSyntaxFile The path of the syntax config file where
		 * the syntaxes are specified.
		 * @param syntax The specific syntax to be used. Must be defined 
		 * in the syntax file.
		 */
		virtual bool setup( const String& pathToSyntaxFile, const String& syntax);


	protected: // methods

		/**
		 * Creates a cluster with the given name, appends it to the current context,
		 * changes the context and sets the cluster up.
		 * @param name The name of the cluster to create
		 * @param createRandomCluster Specifies, whether the specified or a random cluster shall be created.
		 * TRUE - create a random Cluster, the specified name won't be taken into account
		 * FALSE - creates a Cluster which prototype has the specified name.
		 * @return
		 * TRUE - operation successful
		 * FALSE - operation failed
		 */
		bool addCluster( String& name, bool createRandomCluster = false);
		
	protected: // callbacks


		bool onPrintPrototypeClusters( ARGS);
		bool onPrintPrototypeTransformers( ARGS);
		bool onPrintPrototypeFunctions( ARGS);
		bool onPrintPrototypeFadeFunctions( ARGS);
		bool onPrintFrameInfo( ARGS);
		bool onFadeIn( ARGS);
		bool onFadeOut( ARGS);
		bool onEnable( ARGS);
		bool onDisable( ARGS);
		bool onContextRoot( ARGS);
		bool onGetClusters( ARGS);
		bool onGetTransformers( ARGS);
		bool onAddCluster( ARGS);
		bool onAddTransformer( ARGS);
		bool onAddRandomCluster( ARGS);
		bool onAddRandomTransformer( ARGS);
		bool onRemoveCluster( ARGS);
		bool onRemoveTransformer( ARGS);
		bool onRemove( ARGS);
		bool onContextLevelUp( ARGS);
		bool onInfo( ARGS);
		bool onExit( ARGS);
		bool onHelp( ARGS);
		bool onSelectCluster( ARGS);
		bool onSelectTransformer( ARGS);

	}; // END class ConsoleInterpreter

} // END namespace Trip
	

#endif /* __ConsoleInterpreter_HPP__ */
