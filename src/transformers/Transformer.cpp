/**
 * Implementation File for Transformer.hpp.
 * @author barn
 * @version 20121025
 */

/*===========================================================================*
 * INCLUDES (associated header files)
 *===========================================================================*/
#include "Transformer.hpp"

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
	 * Applies the transform strategy once on the given Node.
	 * It takes the _influence variable, the fade-in and fade-out parameters into account and
	 * calls apply() with adjusted influence values internally.
	 * @param nd The Node on which to apply the strategy.
	 * @param tlc The time since the last frame rendered,
	 * multiply it in the implementations in order to keep the right timing.
	 * @param i
	 * A running variable that can be used to parameterize the strategy.
	 * E.g. it could be the number of the SceneNode in a List.
	 */
	void Transformer::transform( Ogre::Node* nd, float tlc, uint i)
	{
		// abort when disabled
		if( !_enabled)
			return;

		float inf = _influence;

		if( _fade_in)
		{
			// process fading in

			if( _fade_time <= _fade_in_time)
			{
				_fade_time += tlc;
				inf *= _fade_in_fun->fun( _fade_time);
			}
			else
			{
				_fade_in = false;
			}
		}
		else if( _fade_out)
		{
			// process fading out

			if( _fade_time >= tlc)
			{
				_fade_time -= tlc;
				inf *= _fade_out_fun->fun( _fade_time);
			}
			else
			{
				setEnabled( false);
				return;
			}
		}

		// apply transformation
		apply( nd, tlc, i, inf);
	}


	/**
	 * Speficies the influence that this Transformer shall have.
	 * Should be a value within [0,1]. Higher/Lower values will be cut.
	 * If the influence will be set to 0, the Transformer will be disabled.
	 * On the other hand, if the transformer is disabled and f > 0 holds,
	 * the Transformer will be enabled.
	 */
	void Transformer::setInfluence( float f)
	{
		if( f > 0.0f)
		{
			if( f > 1.0f)
				f = 1.0f;

			if (!_enabled)
				_enabled = true;
		}
		else if( f < 0.0f)
		{
			f = 0.0f;
			setEnabled(false);
		}

		_influence = f;
	}


} // END namespace Trip
