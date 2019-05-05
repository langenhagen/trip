/**
 * Implementation file for the Function.hpp.
 * @author barn
 * @version 20121027
 */

/*===========================================================================*
 * INCLUDES (associated header files)
 *===========================================================================*/
#include "Function.hpp"

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
	/**
	 * TODO doc
	 */
	void Function::setup( float x_stretch, float y_stretch, float x_offset, float y_offset)
	{
		_x_stretch = x_stretch;
		_y_stretch = y_stretch;
		_x_offset = x_offset;
		_y_offset = y_offset;
	}

} // END namespace Trip
