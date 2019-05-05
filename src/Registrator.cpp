/**
 * Implementation file of the Registrator.hpp.
 * @author barn
 * @version 20121029
 */

/*===========================================================================*
 * INCLUDES (associated header files)
 *===========================================================================*/
#include "Registrator.hpp"

/*===========================================================================*
 * INCLUDES project headers
 *===========================================================================*/
#include "managers/FunctionManager.hpp"
#include "managers/TransformerManager.hpp"
#include "managers/ClusterManager.hpp"

#include "functions/Function.hpp"
#include "clusters/Cluster.hpp"
#include "managers/TransformerManager.hpp"

#include "functions/Functions1.hpp"

#include "clusters/Clusters1.hpp"

#include "transformers/Transformers1.hpp"


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

	/// a prototypical registrator namespace just fits before you later may be able to load and register things with dlls
	namespace Registrator
	{
		/// registers all Functions
		void registerFunctions()
		{
			auto man = FunctionManager::instance();

			// fade linear
			Function* flin = new Lin();
			flin->setStretchX( 0.01f);

			man->addPrototype( "Lin", new Lin());
			man->addPrototype( "FLin", flin);
			man->addPrototype( "Sine", new Sine());
			man->addPrototype( "CosFade", new CosFade());

		}

		/// registers all Transformers
		void registerTransformers()
		{
			auto man = TransformerManager::instance();

			man->addPrototype( "Simple Rotator", new SimpleRotator());
		}

		/// registers all Clusters
		void registerClusters()
		{
			auto man = ClusterManager::instance();

			man->addPrototype( "Schnecki", new SchneckiCluster());
		}


	} // END namespace Registrator

} // END namespace Trip
