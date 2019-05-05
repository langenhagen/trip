/**
 * The implementation file of the TransformerManager.hpp.
 * @author barn
 * @version 20121027
 */

/*===========================================================================*
 * INCLUDES (associated header files)
 *===========================================================================*/
#include "TransformerManager.hpp"

/*===========================================================================*
 * INCLUDES project headers
 *===========================================================================*/
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

	/// The singleton instance.
	TransformerManager* TransformerManager::__instance = 0;

	/**
	 * Creates a random Transformerfrom a prototype.
	 * @return A new Transformer that is a clone of some prototype.
	 * Returns NULL if there are no prototypes.
	 */
	Transformer* TransformerManager::createRandomTransformer()
	{
		if( _prototypes.size() == 0)
		{
			return 0;
		}

		auto it = _prototypes.begin();

		int num = std::rand() % _prototypes.size();
		for( int i = 0; i < num; i++)
		{
			it++;
		}

		return it->second->clone();
	}

	/**
	 * Retrieves the list of all available Transformer's names.
	 * @return A list of the names of the available Transformers.
	 * @see addPrototype()
	 */
	std::list<String> TransformerManager::getTransformerNameList()
	{
		std::list<String> ret;

		for( auto it= _prototypes.begin(); it != _prototypes.end(); it++)
		{
			ret.push_back( it->first);
		}

		return ret;
	}




} // END namespace Trip
