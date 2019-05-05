/**
 * This file contains functions for setting up the clusters, transformers and functions,
 * meaning to create initial prototypes etc. Later, this shall be done in another way,
 * when everything like prototype-classes are compiled into dlls which will be read automatically
 * and which bring their own register-functions. Now, for purpose of fast and simple development
 * this file should be sufficient.
 * @author barn
 * @version 20121029
 */
#ifndef __Registrator_HPP__
#define __Registrator_HPP__

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
	namespace Registrator
	{
		/// registers all Functions
		void registerFunctions();

		/// registers all Transformers
		void registerTransformers();

		/// registers all Clusters
		void registerClusters();

	} // END namespace Registrator

} // END namespace Trip

#endif /* __Registrator_HPP__ */
