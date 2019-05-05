/**
 * The implementation file of the Math.hpp
 * @author barn
 * @version 20121017
 */

/*===========================================================================*
 * INCLUDES (associated header files)
 *===========================================================================*/
#include "Math.hpp"

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

	// beware of rounding-errors
	Ogre::Vector3 cartesian2spherical( const Ogre::Vector3& v)
	{
		float r = sqrtf( v.x*v.x + v.y*v.y + v.z*v.z);

		return Ogre::Vector3(
			r,						// radius
			atan2( v.y, v.x) TODEG, // azimuth
			acosf( v.z/r) TODEG		// inclination
		);
	}

	// beware of rounding-errors
	Ogre::Vector3 spherical2cartesian( const Ogre::Vector3& v)
	{
		// v.x aka r
		// v.y aka azimuth aka phi
		// v.z aka inclination aka psi

		return Ogre::Vector3(
			v.x * cosf( v.y TORAD)* sinf( v.z TORAD),
			v.x * sinf( v.y TORAD)* sinf( v.z TORAD),
			v.x * cosf( v.z TORAD)
		);
	}

	/**
	 * Switches the y and z coordinates of the given vector.
	 * @return Reutrns a reference of this vector.
	 */
	Ogre::Vector3& switchYZ( Ogre::Vector3& v)
	{
		float t_y = v.y;
		v.y = v.z;
		v.z = t_y;

		return v;
	}

	/**
	 * Rounds a number up to specified number of digits behind the comma.
	 * @param f The number to round.
	 * @param digits The number of digits to which shall be rounded. 0 Rounds to integer.
	 */
	float round( float f, unsigned char digits)
	{
		float pow = powf( 10, digits);
		float t = f * pow;

		float fc( std::ceilf( t));
		float ff( std::floorf( t));

		if( std::abs( t - fc) < std::abs( t - ff))
			return fc/pow;
		else
			return ff/pow;
	}

} // END namespace Trip
