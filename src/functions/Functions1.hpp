/**
 * This file contains a bunch of Functions.
 * @author barn
 * @version 20121029
 */
#ifndef __Functions1_HPP__
#define __Functions1_HPP__

/*===========================================================================*
 * INCLUDES base definition file for DLL import/export
 *===========================================================================*/
 
/*===========================================================================*
 * INCLUDES project headers
 *===========================================================================*/
#include "stdafx.h"
#include "Function.hpp"

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

	/// Simple linear function
	class Lin : public Function
	{
	public:
		float doFun( float x) { return x; }
		Function* clone() { return new Lin(); }
	};

	/// Cosine Wave getting smaller: lim->0 = 0.
	class CosFade : public Function
	{
	public:

		float doFun( float x) { return ( (1 - std::cosf( x*10)) * 0.5f) * x; }
		Function* clone() { return new CosFade(); }
	};


	/// Simple sine wave
	class Sine : public Function
	{
	public:
		float doFun( float x) { return std::sinf( x); }
		Function* clone() { return new Sine(); }
	};
	
} // END namespace Trip

#endif /* __Functions1_HPP__ */
