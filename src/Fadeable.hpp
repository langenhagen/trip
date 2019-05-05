/**
 * This file contains the interface Fadeable which provides typical stuff for fadeable
 * classes.
 * @author barn
 * @version 20121027
 */
#ifndef __Fadeable_HPP__
#define __Fadeable_HPP__

/*===========================================================================*
 * INCLUDES base definition file for DLL import/export
 *===========================================================================*/

/*===========================================================================*
 * INCLUDES project headers
 *===========================================================================*/
#include "stdafx.h"
#include <Enableable.hpp>
#include <functions/Function.hpp>


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
	 * The interface Fadeable provides methods and instance vars that
	 * can be used by several other classes on purpose to fade something in/out.
	 */
	class Fadeable : public Enableable
	{
	protected: // vars

		/// Indicates if the object wants to be faded in/out.
		bool _fade_in, _fade_out;

		/// The Functions, that spefify the fading-process.
		Trip::Function* _fade_in_fun;
		Trip::Function* _fade_out_fun;

		/// The time left for fading in/out. Time in seconds.
		float _fade_time;

		/// The amount of time to fade in. Time in seconds.
		float _fade_in_time;

	public: // constructor & destructor

		/**
		 * Main constructor.
		 * Sets fade in/out deactivated.
		 */
		Fadeable()
			: Enableable(),
			_fade_in(false),
			_fade_out(false),
			_fade_in_fun(0),
			_fade_out_fun(0)
		{}

		/**
		 * Destructor.
		 * Deletes the FaderFunctions.
		 */
		~Fadeable()
		{
			delete _fade_in_fun;
			delete _fade_out_fun;
		}

	public: // methods


		/**
		 * Indicates, that the object wants to be faded in.
		 * Also stores the necessary values & sets the object enabled.
		 * @param fadeTime
		 * The time that the fade in takes in seconds.
		 * After that time, the fade-in effect will be stopped.
		 * @fadeFun The Function to be used.
		 */
		void fadeIn( float fadeTime, Trip::Function* fadeFun);

		/**
		 * Indicates, that the object wants to be faded out.
		 * Also stores the necessary values &  sets the object disabled.
		 * @param fadeTime
		 * The time that the fade in takes in seconds.
		 * After that time, the fade-in effect will be stopped.
		 * @fadeFun The Function to be used.
		 */
		void fadeOut( float fadeTime, Trip::Function* fadeFun);


	public: // getters & setters

		/**
		 * Sets whether this object is enabled or not.
		 * @param enabled
		 * TRUE - enabled
		 * FALSE - disabled
		 */
		void setEnabled( bool enabled);

		/**
		 * Retrieves the current set fade in function.
		 * @return The Function for fading in.
		 */
		Function* getFadeInFunction()
		{
			return _fade_in_fun;
		}

		/**
		 * Retrieves the current set fade out function.
		 * @return The Function for fading out.
		 */
		Function* getFadeOutFunction()
		{
			return _fade_out_fun;
		}

		/**
		 * Retrieves the function value of the fade in function
		 * for the specified input value.
		 * @param x The input value for the fade in function.
		 * @return The corresponding function value to input x.
		 */
		float getFadeInValue( float x)
		{
			return _fade_in_fun->fun(x);
		}

		/**
		 * Retrieves the function value of the fade out function
		 * for the specified input value.
		 * @param x The input value for the fade out function.
		 * @return The corresponding function value to input x.
		 */
		float getFadeOutValue( float x)
		{
			return _fade_out_fun->fun(x);
		}

		/**
		 * Indicates, whether the object is in fade-in mode.
		 * @return
		 * TRUE - fade in
		 * FALSE - not fade in
		 */
		bool isFadeIn()
		{
			return _fade_in;
		}

		/**
		 * Indicates, whether the object is in fade-out mode.
		 * @return
		 * TRUE - fade out
		 * FALSE - not fade out
		 */
		bool isFadeOut()
		{
			return _fade_out;
		}

	}; // END class Fadeable

} // END namespace Trip

#endif /* __Fadeable_HPP__ */
