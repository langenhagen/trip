/**
 * This file contains Trip's TransformerManager which is responsible for the creation
 * of Transformers through the usage of prototypes.
 * @author barn
 * @version 20121025
 */
#ifndef __TransformerManager_HPP__
#define __TransformerManager_HPP__

/*===========================================================================*
 * INCLUDES base definition file for DLL import/export
 *===========================================================================*/
 
/*===========================================================================*
 * INCLUDES project headers
 *===========================================================================*/
#include "stdafx.h"
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
	 * The singleton TransformerManager class is responsible for the creation of
	 * the different Transformers during runtime. It makes use of the 
	 * Prototype pattern and creates copy-constructed clones of prototype Transformers.
	 */
	class TransformerManager
	{
	private: // class vars
		
		/// The singleton instance.
		static TransformerManager* __instance;
	
	private: // instance vars


		/// This map stores the names and their corresponding prototype transformers.
		std::map<String, Transformer*> _prototypes;

	protected: // constructor		
		
		/**
		 * Protected main constructor.
		 */
		TransformerManager()
		{}

	public: // destructor

		/**
		 * Destructor.
		 */
		~TransformerManager()
		{
			__instance = 0;
		}

	public: // class methods
	
		/**
		 * Retrieves the singleton instance of the TransformerManager.
		 * Also does the lazy initialization.
		 * @return The singleton TransformerManager.
		 */
		static TransformerManager* instance()
		{
			if (__instance == 0)
				__instance = new TransformerManager();
	
			return __instance;
		}


	public: // methods

		/**
		 * Adds a prototype Transformer to the manager. The same instance as the given
		 * will be taken as a prototype, so don't delete this pointer by yourself.
		 * At destruction time, the manager will take care of it.
		 * @param transformer The Transformer which shall be handled as a prototype.
		 * @param name The name of the prototype. Should be unique for the manager.
		 * in order to be stored.
		 * @return
		 * TRUE - if the element was stored successfully
		 * FALSE - if a prototype with the same name already exists. Nothing happens then.
		 */
		bool addPrototype( const String& name, Transformer* transformer)
		{	
			transformer->setName( name);
			return _prototypes.insert( std::pair<String, Transformer*>( name, transformer )).second;
		}

		/**
		 * Removes all prototypes from the manager.
		 */
		void removeAllPrototypes()
		{
			_prototypes.clear();
		}

		/**
		 * Removes the specified prototype from the manager.
		 * If some prototype is specified that doesn't exist in the list,
		 * nothing happens.
		 * @param name The name of the prototype which is to be deleted.
		 */
		void removePrototype( String name)
		{
			_prototypes.erase( 
				_prototypes.find( name));
		}


		/**
		 * Creates a Transformer from a prototype.
		 * Beware that this function does no error checking if a prototype does really exist.
		 * @param name The name of the prototype which is to be used for creation.
		 * @return A new Transformer that should be a clone of the given prototype.
		 * Returns NULL when the specified name does not match any prototype.
		 * @see addPrototype()
		 */
		Transformer* createTransformer( String name)
		{
			auto it = _prototypes.find( name);
		
			if( it == _prototypes.end())
			{
				return 0;
			}

			return it->second->clone();
		}

		/**
		 * Creates a random Transformerfrom a prototype.
		 * @return A new Transformer that is a clone of some prototype.
		 * Returns NULL if there are no prototypes.
		 */
		Transformer* createRandomTransformer();

		/**
		 * Retrieves the list of all available Transformer's names.
		 * @return A list of the names of the available Transformers.
		 * @see addPrototype()
		 */
		std::list<String> getTransformerNameList();


	}; // END class TransformerManager
	
} // END namespace Trip

#endif /* __TransformerManager_HPP__ */
