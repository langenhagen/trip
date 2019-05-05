/**
 * This file contains of the Enableable interface that provides methods
 * for objects of classes that can be enabled/disabled.
 * @author barn
 * @version 20121030
 */
#ifndef __Enableable_HPP__
#define __Enableable_HPP__

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
	 * The interface Enableable provides an interface to make things enabled
	 * or disabled. It can be used for any general purpose.
	 */
	class Enableable
	{
	protected: // vars

		/// Indicates, whether the object is enabled or not.
		bool _enabled;

	public: // constructor & destructor

		/**
		 * Main constructor.
		 * Sets the Enableable initially enabled.
		 */
		Enableable()
			: _enabled(true)
		{}

		/**
		 * Destructor
		 */
		~Enableable()
		{}

	public: // methods

		/**
		 * Sets whether this object is enabled or not.
		 * @param enabled
		 * TRUE - enabled
		 * FALSE - disabled
		 */
		virtual void setEnabled( bool enabled)
		{
			_enabled = enabled;
		}

		/**
		 * Indicates whether this object is enabled or not.
		 * @return
		 * TRUE - enabled
		 * FALSE - disabled
		 */
		virtual bool isEnabled()
		{
			return _enabled;
		}

	}; // END class Enableable

} // END namespace Trip

#endif /* __Enableable_HPP__ */
