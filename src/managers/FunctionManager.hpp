/**
 * This file contains the FunctionManager that creates new Functions from Prototypes.
 * @author barn
 * @version 20121027
 */
#ifndef __FunctionManager_HPP__
#define __FunctionManager_HPP__

/*===========================================================================*
 * INCLUDES base definition file for DLL import/export
 *===========================================================================*/

/*===========================================================================*
 * INCLUDES project headers
 *===========================================================================*/
#include "stdafx.h"
#include <functions/Function.hpp>

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
	 * This class is able to create Functions from prototypes that can be registered at runtime.
	 * Use this class is you want to create Functions at runtime.
	 */
	class FunctionManager
	{

	private: // class vars

		/// The singleton instance.
		static FunctionManager* __instance;

	private: // instance vars

		/// This map stores the names and their corresponding prototype Functions.
		std::map< String, Function* > _prototype_functions;

	protected: // constructor

		/**
		 * Protected main constructor.
		 */
		FunctionManager()
		{}

	public: // destructor

		/**
		 * Destructor.
		 */
		~FunctionManager()
		{
			removeAllPrototypes();

			__instance = 0;
		}

	public: // class methods

		/**
		 * Retrieves the singleton instance of the FunctionManager.
		 * Also does the lazy initialization.
		 * @return The singleton FunctionManager.
		 */
		static FunctionManager* instance()
		{
			if (__instance == 0)
				__instance = new FunctionManager();

			return __instance;
		}

	public: // methods

		/**
		 * Adds a prototype Function to the manager. The same instance as the given
		 * will be taken as a prototype, so don't delete this pointer by yourself.
		 * At destruction time, the manager will take care of it.
		 * @param name The name of the prototype. Should be unique for the manager.
		 * in order to be stored.
		 * @param function The Function which shall be handled as a prototype.
		 * @return
		 * TRUE - if the element was stored successfully
		 * FALSE - if a prototype with the same name already exists. Nothing happens then.
		 */
		bool addPrototype( const String& name, Function* function);

		/**
		 * Removes all prototypes from the manager and deletes them from memory.
		 */
		void removeAllPrototypes();

		/**
		 * Removes the specified prototype from the manager.
		 * If some prototype is specified that doesn't exist in the list,
		 * nothing happens.
		 * @param name The name of the prototype which is to be deleted.
		 */
		void removePrototype( const String& name)
		{
			// TODO verify in error case
			delete _prototype_functions.find( name)->second;
			_prototype_functions.erase(
				_prototype_functions.find( name));
		}

		/**
		 * Creates a Function from a prototype.
		 * Beware that this method does no error checking if a prototype does really exist.
		 * @param name The name of the prototype which is to be used for creation.
		 * @return A new Function that should be a clone of the given prototype.
		 * Returns null, if the specified prototype does not exist.
		 * @see addPrototype()
		 */
		Function* createFunction( const String& name);

		/**
		 * Creates a random Function from a prototype.
		 * @return A new Function that is a clone of some prototype.
		 */
		Function* createRandomFunction();

		/**
		 * Retrieves the list of all available Functions's names.
		 * @return A list of the names of the available Functions.
		 * @see addPrototype()
		 */
		std::list<String> getFunctionNameList();

	}; // END class FunctionManager

} // END namespace Trip

#endif /* __FunctionManager_HPP__ */
