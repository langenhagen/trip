/**
 * The implementation file for the FunctionManager.hpp.
 * @author barn
 * @version 20121027
 */

/*===========================================================================*
 * INCLUDES (associated header files)
 *===========================================================================*/
#include "managers/FunctionManager.hpp"

/*===========================================================================*
 * INCLUDES project headers
 *===========================================================================*/

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

	/// The singleton instance.
	FunctionManager* FunctionManager::__instance = 0;


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
	bool FunctionManager::addPrototype( const String& name, Function* function)
	{
		return _prototype_functions.insert( std::pair< String, Function* >( name, function)).second;
	}

	/**
	 * Removes all prototypes from the manager and deletes them from memory.
	 */
	void FunctionManager::removeAllPrototypes()
	{
		for( auto it = _prototype_functions.begin(); it != _prototype_functions.end(); it++)
		{
			delete it->second;
		}
		_prototype_functions.clear();
	}


	/**
	 * Creates a Function from a prototype.
	 * Beware that this method does no error checking if a prototype does really exist.
	 * @param name The name of the prototype which is to be used for creation.
	 * @return A new Function that should be a clone of the given prototype.
	 * Returns null, if the specified prototype does not exist.
	 * @see addPrototype()
	 */
	Function* FunctionManager::createFunction( const String& name)
	{
		auto it = _prototype_functions.find( name);

		return (it == _prototype_functions.end() ? 0 : it->second->clone() );
	}


	/**
	 * Retrieves the list of all available Functions's names.
	 * @return A list of the names of the available Functions.
	 * @see addPrototype()
	 */
	std::list<String> FunctionManager::getFunctionNameList()
	{
		std::list<String> ret;

		for( auto it= _prototype_functions.begin(); it != _prototype_functions.end(); it++)
		{
			ret.push_back( it->first);
		}

		return ret;
	}

	/**
	 * Creates a random Function from a prototype.
	 * @return A new Function that is a clone of some prototype.
	 */
	Function* FunctionManager::createRandomFunction()
	{
		auto it = _prototype_functions.begin();

		int num = std::rand() % _prototype_functions.size();
		for( int i = 0; i < num; i++)
		{
			it++;
		}

		return it->second->clone();
	}


} // END namespace Trip
