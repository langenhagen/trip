/**
 * This file contains of functions and definitions that are useful for calculating mathematical stuffn.
 * @author barn
 * @version 20121015
 */
#ifndef __Barn_Math_H__
#define __Barn_Math_H__

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
	// PI. you sucker.
	static const float PI = 3.14159265f;

	// converts a degree number into a radian number. example: 90 TORAD := PI/2
	#define TORAD *0.0174532925f

	// converts a radian number into a degree number. example: 3.14159265 TODEG := 180
	#define TODEG *57.296986035f

	// beware of rounding-errors
	Ogre::Vector3 cartesian2spherical( const Ogre::Vector3& v);

	// beware of rounding-errors
	Ogre::Vector3 spherical2cartesian( const Ogre::Vector3& v);

	/**
	 * Switches the y and z coordinates of the given vector.
	 * @return Reutrns a reference of this vector.
	 */
	Ogre::Vector3& switchYZ( Ogre::Vector3& v);

	/**
	 * Rounds a number up to specified number of digits behind the comma.
	 * @param f The number to round.
	 * @param digits The number of digits to which shall be rounded. 0 Rounds to integer.
	 */
	float round( float f, unsigned char digits);

} // END namespace Trip


#endif /* __Barn_Math_H__ */
