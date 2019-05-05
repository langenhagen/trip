/**
 *
 * @author barn
 * @version 20121107
 */
#ifndef __Transformers1_HPP__
#define __Transformers1_HPP__

/*===========================================================================*
 * INCLUDES base definition file for DLL import/export
 *===========================================================================*/

/*===========================================================================*
 * INCLUDES project headers
 *===========================================================================*/
#include "stdafx.h"
#include <util/Math.hpp>

/*===========================================================================*
 * INCLUDES C/C++ standard library (and other external libraries)
 *===========================================================================*/

/*===========================================================================*
 * DEFINES and MACROS
 *===========================================================================*/

/*===========================================================================*
 * NAMESPACE, CONSTANTS and TYPE DECLARATIONS/IMPLEMENTATIONS
 *===========================================================================*/

/*****************************************************************************

	/// comment
	class XXXTransformer : public Trip::Transformer
	{
	public:

		Transformer* clone()
		{
			return new XXXTransformer( *this);
		}

		XXXTransformer()
		{
			setName( "XXX");
			// ...
		}

		void doSetup()
		{
			this->setName("XXX");

		}
	};

******************************************************************************/

namespace Trip
{

	/// SimpleRotator
	class SimpleRotator : public Trip::Transformer
	{
	public:

		Transformer* clone()
		{
			return new SimpleRotator( *this);
		}

		SimpleRotator()
		{
			setName("Simple_Rotator");

			// _params[0] - speed
			_params.push_back( 3);
			_param_descriptions.push_back("Rotation Speed");
			// _params[1] - x axis
			_params.push_back( 0);
			_param_descriptions.push_back("X axis");
			// _params[2] - y axis
			_params.push_back( 1);
			_param_descriptions.push_back("Y axis");
			// _params[3] - z axis
			_params.push_back( 0);
			_param_descriptions.push_back("Z axis");
		}

		void apply( Ogre::Node* nd, float tlc, uint i = 0, float inf = 1)
		{
			nd->rotate( Ogre::Vector3( _params[1], _params[2], _params[3]), Ogre::Radian( _params[0] * tlc * inf) );
		}
	};

} // END namespace Trip

#endif /* __Transformers1_HPP__ */
