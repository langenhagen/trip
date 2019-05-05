/**
 * This file makes some typedefs and defines that can be pretty useful concerning writing less code.
 * General purpose.
 * Use at own risk
 * @author barn
 * @version 20121018
 */
#ifndef __Defines_H__
#define __Defines_H__

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
#include <string>

/*===========================================================================*
 * DEFINES and MACROS
 *===========================================================================*/

/// console syntax map file
#define TRIP_CONSOLE_SYNTAX_MAP_FILE "ConsoleSyntaxMap.cfg"

/// console syntax to be used
#define TRIP_CONSOLE_SYNTAX "UltraShortSyntax"


#define LASTFRAME evt.timeSinceLastFrame

#define SPHERICAL_STEPSIZE 1.3f


/*===========================================================================*
 * NAMESPACE, CONSTANTS and TYPE DECLARATIONS/IMPLEMENTATIONS
 *===========================================================================*/

namespace Trip
{
	typedef unsigned int uint;

	typedef unsigned char uchar;

	typedef std::string String;

} // END namespace Trip

#endif /* __Defines_H__ */
