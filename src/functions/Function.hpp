/**
 * This file contains Function classes that encapsulate mathematical functions
 * @author barn
 * @version 20121027
 */
#ifndef __Function_HPP__
#define __Function_HPP__

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
	/**
	 * This class represents real mathematical functions.
	 */
	class Function
	{
	protected: // vars

		float _x_stretch; //< Stretch factor in x/input direction
		float _y_stretch; //< Stretch factor in y/output direction
		float _x_offset; //< additive offset in x direction
		float _y_offset; //< additive offset in y direction

	public: // constructors & destructor

		Function()
			: _x_stretch(1.0f), _y_stretch(1.0f), _x_offset(0.0f), _y_offset(0.0f)
		{}

	public: // methods

		/**
		 * Applies the function with the set stretch factors and offset.
		 * @param x The input variable.
		 * @return The corresponding function value to x.
		 */
		float operator()( float x)
		{
			return fun( x);
		}

		/**
		 * The clone operation. Subclasses have to override this method in order to
		 * to enable creation via the FunctionManager, where Functions can be set as prototypes.
		 * Say, when you create a subclass named YourFunction just add a
		 * "return new YourFunction()" to the clone() method.
		 */
		virtual Function* clone()
		{
			return new Function();
		}

		/**
		 * TODO doc
		 */
		float fun( float x)
		{
			return doFun( x * _x_stretch + _x_offset) * _y_stretch + _y_offset;
		}

	protected: // overridable methods

		/**
		 * TODO doc
		 */
		virtual float doFun( float x)
		{
			return 0.0f;
		}

	public: // setters & getters

		/**
		 * TODO doc
		 */
		void setup( float x_stretch = 1.0f, float y_stretch  = 1.0f, float x_offset  = 0.0f, float y_offset = 0.0f);

		/**
		 * TODO doc
		 */
		void setStretchX( float stretch = 1.0f) { _x_stretch = stretch; }

		/**
		 * TODO doc
		 */
		void setStretchY( float stretch = 1.0f) { _y_stretch = stretch; }

		/**
		 * TODO doc
		 */
		void setOffsetX( float offset = 0.0f) { _x_offset = offset; }

		/**
		 * TODO doc
		 */
		void setOffsetY( float offset = 0.0f) { _y_offset = offset; }

		/**
		 * TODO doc
		 */
		float getStretchX() { return _x_stretch; }

		/**
		 * TODO doc
		 */
		float getStretchY() { return _y_stretch; }

		/**
		 * TODO doc
		 */
		float getOffsetX() { return _x_offset; }

		/**
		 * TODO doc
		 */
		float getOffsetY() { return _y_offset; }

	}; // END class Function

} // END namespace Trip

#endif /* __Function_HPP__ */
