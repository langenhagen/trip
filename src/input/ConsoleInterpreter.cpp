/**
 * Implementation file for the TripConsole.hpp.
 * @author barn
 * @version 20121029
 */

/*===========================================================================*
 * INCLUDES (associated header files)
 *===========================================================================*/
#include "ConsoleInterpreter.hpp"

/*===========================================================================*
 * INCLUDES project headers
 *===========================================================================*/
#include <Defines.h>
#include <managers/TransformerManager.hpp>
#include <managers/FunctionManager.hpp>
#include <managers/TripVarManager.hpp>

/*===========================================================================*
 * INCLUDES C/C++ standard library (and other external libraries)
 *===========================================================================*/

/*===========================================================================*
 * DEFINES and MACROS
 *===========================================================================*/

/// maps a keyword to a callback
#define CALLBACK_MAP(keyword, associated_callback)	\
	if( callback_name.compare( keyword) == 0) \
	{ \
		callback = &ConsoleInterpreter::##associated_callback; \
	} \
	else

/*===========================================================================*
 * NAMESPACE, CONSTANTS and TYPE DECLARATIONS/IMPLEMENTATIONS
 *===========================================================================*/
 
namespace Trip
{
	/// Pairs of commands and callbacks
	typedef std::pair<String, ConsoleCallback> CommandCallbackPair;

	/**
	 * Assigns a callback to a string element.
	 * Override this method in your subclass.
	 * @return
	 * TRUE - setup was successful
	 * FALSE - setup failed
	 */
	bool ConsoleInterpreter::setup( const String& pathToSyntaxFile, const String& syntax)
	{
		Ogre::ConfigFile cf;
		cf.load( pathToSyntaxFile);

		Ogre::ConfigFile::SectionIterator section_iter = cf.getSectionIterator();

		while( section_iter.hasMoreElements())
		{
			String syntax_name = section_iter.peekNextKey();
			Ogre::ConfigFile::SettingsMultiMap* section = section_iter.getNext();

			// look for right syntax
			if( syntax_name.compare( syntax) != 0)
			{
				continue;
			}
			// *** found right syntax ***

			// process every line
			
			for( Ogre::ConfigFile::SettingsMultiMap::iterator it = section->begin(); it != section->end(); ++it)
			{
				String callback_name = it->first;
				String command = it->second;
				ConsoleCallback callback;

				Ogre::StringUtil::trim( callback_name);
				Ogre::StringUtil::trim( command);
			
				// map callback_name to corresponding keywords / callbacks

				CALLBACK_MAP("onPrintPrototypeClusters", onPrintPrototypeClusters)
				CALLBACK_MAP("onPrintPrototypeTransformers", onPrintPrototypeTransformers)
				CALLBACK_MAP("onPrintPrototypeFunctions", onPrintPrototypeFunctions)
				CALLBACK_MAP("onPrintFrameInfo", onPrintFrameInfo)
				CALLBACK_MAP("onFadeIn", onFadeIn)
				CALLBACK_MAP("onFadeOut", onFadeOut)
				CALLBACK_MAP("onEnable", onEnable)
				CALLBACK_MAP("onDisable", onDisable)
				CALLBACK_MAP("onContextRoot", onContextRoot)
				CALLBACK_MAP("onContextLevelUp", onContextLevelUp)
				CALLBACK_MAP("onGetClusters", onGetClusters)
				CALLBACK_MAP("onGetTransformers", onGetTransformers)
				CALLBACK_MAP("onAddCluster", onAddCluster)
				CALLBACK_MAP("onAddTransformer", onAddTransformer)
				CALLBACK_MAP("onAddRandomCluster", onAddRandomCluster)
				CALLBACK_MAP("onAddRandomTransformer", onAddRandomTransformer)
				CALLBACK_MAP("onRemoveCluster", onRemoveCluster)
				CALLBACK_MAP("onRemoveTransformer", onRemoveTransformer)
				CALLBACK_MAP("onRemove", onRemove)
				CALLBACK_MAP("onInfo", onInfo)
				CALLBACK_MAP("onExit", onExit)
				CALLBACK_MAP("onHelp", onHelp)
				CALLBACK_MAP("onSelectCluster", onSelectCluster)
				CALLBACK_MAP("onSelectTransformer", onSelectTransformer) 
				{
                    // error case
					Trip::log( String("ConsoleInterpreter::setup(): Callback ").append( callback_name).append(" not known."), MSG_ERROR);
					return false;
				}

				// insert command-callback pair into map
				_callback_map.insert( CommandCallbackPair( command, callback));
			}

			// finished. return
			return true;
		}
		// *** no syntax with the specified name found ***

		Trip::log( String("ConsoleInterpreter::setup(): No syntax called ").append( syntax).append(" found."), MSG_ERROR);

		return false;
	}


	/**
	 * Interpretes a given input string and manipulates Trip according to that input.
	 * @param str An input string that is to be interpreted.
	 * @return Indicates, whether the input string could be processed correctly or not.
	 * TRUE - input could be processed
	 * FALSE - input could not be processed due to syntax errors or due to wrong context.
	 */
	bool ConsoleInterpreter::interprete( std::string& str)
	{
		std::vector<String>& args = Trip::Util::split( str, ' ');

		if( args.size() < 1)
		{
			return false;
		}

		auto it = _callback_map.find(args[0]);
		if( it == _callback_map.end())
		{
			Trip::log( 
				String("Command ").append(args[0]).append(" not kown."),
				MSG_ERROR); 

			return false;
		}
		
		// call the callback
		return (this->*it->second)( args);
	}


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
	bool ConsoleInterpreter::addCluster( String& name, bool createRandomCluster)
	{
		// check context
		if( !isContext( CLUSTER))
		{
			Trip::log( "Only Clusters can carry child Clusters.", MSG_ERROR);
			return false;
		}

		Cluster* cluster;

		// create cluster
		if(createRandomCluster)
		{
			cluster = ClusterManager::instance()->createRandomCluster();
		}
		else
		{
			cluster = ClusterManager::instance()->createCluster( name);
		}
			
		// error handling
		if( cluster == 0)
		{
			Trip::log( String("Cluster with the name ").append( name).append( " is not known."), MSG_ERROR);
			return false;
		}

		// setup cluster & context
		_context_cluster_list.back()->addCluster( cluster);
		_context_cluster_list.push_back(cluster);
		cluster->setup();
		_context_type = CLUSTER;
		return true;
	}

	// CALLBACKS //////////////////////////////////////////////////////////////////////////////////

	/*
	 * onPrintPrototypeClusters
	 */
	bool ConsoleInterpreter::onPrintPrototypeClusters( std::vector<String>& args)
	{
		std::cout << "Cluster Prototypes: " << std::endl;	
		Trip::Util::printList( ClusterManager::instance()->getClusterNameList());

		return true;
	}
	

	/**
	 * onPrintPrototypeTransformers
	 */ 
	bool ConsoleInterpreter::onPrintPrototypeTransformers( std::vector<String>& args)
	{
		std::cout << "Transformer Prototypes: " << std::endl;	
		Trip::Util::printList( TransformerManager::instance()->getTransformerNameList());

		return true;
	}

	/**
	 * onPrintPrototypeFunctions
	 */
	bool ConsoleInterpreter::onPrintPrototypeFunctions( std::vector<String>& args)
	{
		std::cout << "Function Prototypes: " << std::endl;	
		Trip::Util::printList( FunctionManager::instance()->getFunctionNameList());

		return true;
	}


	/**
	 * onPrintFrameInfo
	 */
	bool ConsoleInterpreter::onPrintFrameInfo( std::vector<String>& args)
	{
		std::cout << "onPrintFrameInfo" << std::endl;
		// TODO
		return false;
	}

	/**
	 * onFadeIn
	 */
	bool ConsoleInterpreter::onFadeIn( std::vector<String>& args)
	{
		// error handling
		if( args.size() < 2)
		{
			Trip::log( String("Usage: ").append(args[0]).append( " <milliseconds> <Function> or\n       ")
				.append(args[0]).append( " <milliseconds>" ));
			return false;
		}

		// retrieve fade function
		Function* fade_function;
		if( args.size() < 3)
		{
			fade_function = FunctionManager::instance()->createRandomFunction();
		}
		else
		{
			fade_function = FunctionManager::instance()->createFunction( args[2]);

			if( fade_function == 0)
			{
				Trip::log( String("Function ").append(args[2]).append( " not known."));
				return false;
			}
		}

		if( !Trip::Util::isNumber( args[1]))
		{
			Trip::log( "First command parameter: " + args[1] + " must be a number", MSG_ERROR);
			return false;
		}

		// set it up
		float time = ((float)atoi( args[1].c_str()))/1000.0f;
		fade_function->setStretchX( fade_function->getStretchX()/time);
		if( isContext( CLUSTER))
		{
			_context_cluster_list.back()->fadeIn( time, fade_function);
		}
		else if( isContext( TRANSFORMER))
		{
			_context_transformer->fadeIn( time, fade_function);
		}
		
		return true;
	}

	/**
	 * onFadeOut
	 */
	bool ConsoleInterpreter::onFadeOut( std::vector<String>& args)
	{
		// error handling
		if( args.size() < 2)
		{
			Trip::log( String("Usage: ").append(args[0]).append( " <milliseconds> <Function> or\n       ")
				.append(args[0]).append( " <milliseconds>" ));
			return false;
		}

		// retrieve fade function
		Function* fade_function;
		if( args.size() < 3)
		{
			fade_function = FunctionManager::instance()->createRandomFunction();
		}
		else
		{
			fade_function = FunctionManager::instance()->createFunction( args[2]);

			if( fade_function == 0)
			{
				Trip::log( String("Function ").append(args[2]).append( " not known."));
				return false;
			}
		}

		if( !Trip::Util::isNumber( args[1]))
		{
			Trip::log( "First command parameter: " + args[1] + " must be a number", MSG_ERROR);
			return false;
		}

		// set it up
		float time = ((float)atoi( args[1].c_str()))/1000.0f;
		fade_function->setStretchX( fade_function->getStretchX()/time);
		if( isContext( CLUSTER))
		{
			_context_cluster_list.back()->fadeOut( time, fade_function);
		}
		else if( isContext( TRANSFORMER))
		{
			_context_transformer->fadeOut( time, fade_function);
		}
		
		return true;
	}

	/**
	 * onEnable
	 */
	bool ConsoleInterpreter::onEnable( std::vector<String>& args)
	{
		if( isContext( CLUSTER))
		{
			this->_context_cluster_list.back()->setEnabled(true);
		}
		else if( isContext( TRANSFORMER))
		{
			this->_context_transformer->setEnabled(true);
		}
		else
		{
			Trip::log( "ConsoleInterpreter::onEnable: Wrong context.", MSG_ERROR);
			return false;	// Should not happen
		}

		return true;
	}

	/**
	 * onDisable
	 */
	bool ConsoleInterpreter::onDisable( std::vector<String>& args)
	{
		if( this->isContext( CLUSTER))
		{
			this->_context_cluster_list.back()->setEnabled(false);
		}
		else if( this->isContext( TRANSFORMER))
		{
			this->_context_transformer->setEnabled(false);
		}
		else
		{
			Trip::log( "ConsoleInterpreter::onDisable: Wrong context.", MSG_ERROR);
			return false;	// Should not happen
		}
		
		return true;
	}

	/**
	 * onContextRoot
	 */
	bool ConsoleInterpreter::onContextRoot( std::vector<String>& args)
	{
		_context_cluster_list.clear();
		_context_cluster_list.push_back( ClusterManager::instance()->getRootCluster());
		return true;
	}

	/**
	 * Couts the names of the child Clusters of the current context Cluster.
	 */
	bool ConsoleInterpreter::onGetClusters( std::vector<String>& args)
	{
		if( !isContext( CLUSTER))
		{
			Trip::log( "Only Clusters can carry child Clusters.", MSG_ERROR);
			return false;
		}

		std::list<String> cluster_names;
		auto clusters = _context_cluster_list.back()->getAllClusters();
		for( auto it = clusters.begin(); it != clusters.end(); ++it)
		{
			cluster_names.push_back( (*it)->getName());
		}

		std::cout << "Child Clusters" << std::endl;
		Trip::Util::printList( cluster_names);

		return true;
	}

	/**
	 * onGetTransformers
	 */
	bool ConsoleInterpreter::onGetTransformers( std::vector<String>& args)
	{
		if( !isContext( CLUSTER))
		{
			Trip::log( "Only Clusters can carry Transformers.", MSG_ERROR);
			return false;
		}

		std::list<String> transformer_names;
		auto transformers = _context_cluster_list.back()->getAllTransformers();
		for( auto it = transformers.begin(); it != transformers.end(); ++it)
		{
			transformer_names.push_back( (*it)->getName());
		}

		std::cout << "Child Transformers" << std::endl;
		Trip::Util::printList( transformer_names);

		return true;
	}

	/**
	 * onAddCluster
	 */
	bool ConsoleInterpreter::onAddCluster( std::vector<String>& args)
	{
		if( args.size() < 2)
		{
			Trip::log( String("Usage: ").append(args[0]).append( " <Cluster>"));
			return false;
		}

		return addCluster( args[1], false);
	}

	/**
	 * onAddTransformer
	 */
	bool ConsoleInterpreter::onAddTransformer( std::vector<String>& args)
	{
		if( args.size() < 2)
		{
			Trip::log( String("Usage: ").append(args[0]).append( " <Transformer>"));
			return false;
		}

		if( !isContext( CLUSTER))
		{
			Trip::log( "Only Clusters can carry child Transformers.", MSG_ERROR);
			return false;
		}

		Transformer* transformer = TransformerManager::instance()->createTransformer( args[1]);
		
		if( transformer == 0)
		{
			Trip::log( String("Transformer with the name ").append( args[1]).append( " is not known."), MSG_ERROR);
			return false;
		}

		_context_cluster_list.back()->addTransformer( transformer);
		return true;
	}

	/**
	 * onAddRandomCluster
	 */
	bool ConsoleInterpreter::onAddRandomCluster( std::vector<String>& args)
	{
		return addCluster( String(),true);
	}

	/**
	 * onAddRandomTransformer
	 */
	bool ConsoleInterpreter::onAddRandomTransformer( std::vector<String>& args)
	{
		if( !isContext( CLUSTER))
		{
			Trip::log( "Only Clusters can carry child Transformers.", MSG_ERROR);
			return false;
		}

		Transformer* transformer = TransformerManager::instance()->createRandomTransformer();

		if( transformer == 0)
			return false;

		_context_cluster_list.back()->addTransformer( transformer);
		return true;
	}

	/**
	 * onRemoveCluster
	 */
	bool ConsoleInterpreter::onRemoveCluster( std::vector<String>& args)
	{
		// Error checking
		if( args.size() < 2)
		{
			Trip::log( "Usage: " + args[0] + " <NUMBER>");
			return false;
		}
		if( !Trip::Util::isNumber( args[1]))
		{
			Trip::log( "First command parameter: " + args[1] + " must be a number", MSG_ERROR);
			return false;
		}
		if( !isContext( CLUSTER))
		{
			Trip::log( "Only Clusters can carry child Clusters.", MSG_ERROR);
			return false;
		}

		delete _context_cluster_list.back()->removeCluster(  std::atoi( args[1].c_str()));
		return true;
	}

	/**
	 * onRemoveTransformer
	 */
	bool ConsoleInterpreter::onRemoveTransformer( std::vector<String>& args)
	{
		// error checking
		if( args.size() < 2)
		{
			Trip::log( String("Usage: ").append(args[0]).append( " <NUMBER>"));
			return false;
		}
		if( !Trip::Util::isNumber( args[1]))
		{
			Trip::log( "First command parameter: " + args[1] + " must be a number", MSG_ERROR);
			return false;
		}
		if( !isContext( CLUSTER))
		{
			Trip::log( "Only Clusters can carry child Transformers.", MSG_ERROR);
			return false;
		}

		delete _context_cluster_list.back()->removeTransformer( std::atoi( args[1].c_str() ));
		return true;
	}

	/**
	 * onRemove
	 */
	bool ConsoleInterpreter::onRemove( std::vector<String>& args)
	{
		if( isContext( CLUSTER))
		{
			if( _context_cluster_list.size() > 1)
			{
				Cluster* cluster = _context_cluster_list.back();
				_context_cluster_list.pop_back();
				_context_cluster_list.back()->removeCluster(cluster);
				delete cluster;
			}
		}
		else if ( isContext( TRANSFORMER))
		{
			Cluster* cluster = _context_cluster_list.back();
			cluster->removeTransformer( _context_transformer);
			delete _context_transformer;
			_context_transformer = 0; // TODO Necessary?
		}
		else
		{
			Trip::log( "ConsoleInterpreter::remove: Wrong context.", MSG_ERROR);
			return false;	// Should not happen
		}

		updateContextType();
		return true;	
	}

	/**
	 * onContextLevelUp
	 */
	bool ConsoleInterpreter::onContextLevelUp( std::vector<String>& args)
	{
		contextLevelUp();
		return true;
	}

	/**
	 * onInfo
	 */
	bool ConsoleInterpreter::onInfo( std::vector<String>& args)
	{
		std::cout << "Info about ";
		
		if( isContext(ROOT))
		{
			std::cout << "Root Cluster:" << std::endl;
		}
		if( isContext( CLUSTER))
		{
			std::cout << "Cluster '" << _context_cluster_list.back()->getName() << "': " << std::endl;
			
			// child clusters
			onGetClusters( std::vector<String>());

			// childTransformers
			onGetTransformers( std::vector<String>());
		}
		else if( isContext( TRANSFORMER))
		{
			std::cout << "Transformer '" << _context_transformer->getName() << "': " << std::endl;
			// TODO
		}

		return true;
	}

	/**
	 * onExit
	 */
	bool ConsoleInterpreter::onExit( std::vector<String>& args)
	{
		exit(0);
		return true;
	}

	/**
	 * onHelp
	 */
	bool ConsoleInterpreter::onHelp( std::vector<String>& args)
	{
		// TODO
		std::cout << "Please consult the File \"" << TRIP_CONSOLE_SYNTAX_MAP_FILE
			      << "\" for information about the syntax. You are using the syntax called \"" << TRIP_CONSOLE_SYNTAX "\"." << std::endl;
		return true;
	}


	/**
	 * onSelectCluster
	 */
	bool ConsoleInterpreter::onSelectCluster( std::vector<String>& args)
	{
		// Error checking
		if( args.size() < 2)
		{
			Trip::log( "Usage: " + args[0] + " <NUMBER>");
			return false;
		}
		if( !Trip::Util::isNumber( args[1]))
		{
			Trip::log( "First command parameter: " + args[1] + " must be a number", MSG_ERROR);
			return false;
		}

		uint pos( std::atoi( args[1].c_str()));

		if( pos >= _context_cluster_list.back()->getAllClusters().size())
		{
			Trip::log( "Entered index of child Cluster exceeds size of child Cluster list.", MSG_ERROR);
			return false;
		}

		_context_cluster_list.push_back( _context_cluster_list.back()->getCluster( pos));		
		return true;
	}
	
	/**
	 * onSelectTransformer
	 */
	bool ConsoleInterpreter::onSelectTransformer( std::vector<String>& args)
	{
		// Error checking
		if( args.size() < 2)
		{
			Trip::log( "Usage: " + args[0] + " <NUMBER>");
			return false;
		}
		if( !Trip::Util::isNumber( args[1]))
		{
			Trip::log( "First command parameter: " + args[1] + " must be a number", MSG_ERROR);
			return false;
		}

		uint pos( std::atoi( args[1].c_str()));

		if( pos >= _context_cluster_list.back()->getAllTransformers().size())
		{
			Trip::log( "Entered index of Transformer exceeds size of Transformer vector.", MSG_ERROR);
			return false;
		}

		_context_transformer = _context_cluster_list.back()->getTransformer( pos);
		updateContextType();
		return true;
	}


} // END namespace Trip


#undef CALLBACK_MAP