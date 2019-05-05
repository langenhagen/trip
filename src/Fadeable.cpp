/**
 * The implementation file for Fadeable.hpp.
 * @author barn
 * @version 20121027
 */

/*===========================================================================*
 * INCLUDES (associated header files)
 *===========================================================================*/
#include "Fadeable.hpp"

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
	 * Indicates, that the object wants to be faded in.
	 * Also stores the necessary values. Note that fading in and fading
	 * out is not possible at the same time. The newest called action overrides an older one.
	 * Enables the object. Also, deletes the old fade in function, if there was one.s
	 * @param fadeTime
	 * The time that the fade in takes in seconds.
	 * After that time, the fade-in effect will be stopped.
	 * @fadeFun The Function to be used.
	 */
	void Fadeable::fadeIn( float fadeTime, Trip::Function* fadeFun)
	{
		if( _fade_in_fun)
			delete _fade_in_fun;

		_enabled = true;
		_fade_out = false;
		_fade_in = true;
		_fade_time = 0;
		_fade_in_time = fadeTime;
		_fade_in_fun = fadeFun;
	}

	/**
	 * Indicates, that the object wants to be faded out.
	 * Also stores the necessary values. Note that fading in and fading
	 * out is not possible at the same time. The newest called action overrides an older one.
	 * Disables the object when finished fading. Also, deletes the old fade out function,
	 * if there was one.
	 * @param fadeTime
	 * The time that the fade in takes in seconds.
	 * After that time, the fade-in effect will be stopped.
	 * @fadeFun The Function to be used.
	 */
	void Fadeable::fadeOut( float fadeTime, Trip::Function* fadeFun)
	{
		if( _fade_out_fun)
			delete _fade_out_fun;

		_fade_in = false;
		_fade_out = true;
		_fade_time = fadeTime;
		_fade_out_fun = fadeFun;
	}


	/**
	 * Sets whether this object is enabled or not.
	 * This also stops all fadings, not just pausing it.
	 * @param enabled
	 * TRUE - enabled
	 * FALSE - disabled
	 */
	void Fadeable::setEnabled( bool enabled)
	{
		Enableable::setEnabled( enabled);

		if( !enabled)
		{
			if(_fade_in)
				_fade_in = false;
			else if(_fade_out)
				_fade_out = false;
		}
	}


} // END namespace Trip
