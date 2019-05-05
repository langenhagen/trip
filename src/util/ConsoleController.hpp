/**
 * Provides windows-system dependent, easy functions for manipulating the console.
 * @author barn
 * @version 20121101
 */
#ifndef __ConsoleController_HPP__
#define __ConsoleController_HPP__

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

	namespace Console
	{

		/**
		 * This enum provides some easy readable
		 * values for the set color methods.
		 */
		enum ConsoleColor
		{
			STD = 7,
			BLACK = 0,
			DARK_BLUE = 1,
			DARK_GREEN = 2,
			DARK_CYAN = 3,
			DARK_RED = 4,
			DARK_PINK = 5,
			DARK_YELLOW = 6,
			DARK_WHITE = 7,
			GRAY = 8,
			BLUE = 9,
			GREEN = 10,
			CYAN = 11,
			RED = 12,
			PINK = 13,
			YELLOW = 14,
			WHITE = 15
		}; // END enum ConsoleColor


		/**
		 * Clears the screen.
		 * @return
		 * FALSE - on error
		 * TRUE - if it worked
		 */
		bool cls();

		/**
		 * Sets the cursor to the specified position.
		 * @param line The line to put the cursor in.
		 * @param row The row tu put the cursor in.
		 * @return
		 * FALSE - on error
		 * TRUE - if it worked
		 */
		bool setCursor( int line, int row);

		/**
		 * Sets the color of the text.
		 * @param color The color value according to SetConsoleTextAttribute.
		 * @return
		 * FALSE - on error
		 * TRUE - if it worked
		 */
		bool setColor( ConsoleColor color);

		/**
		 * Retrieves the cursor Position.
		 * @return A pair where the first value specifies the line,
		 * and the second the row.
		 */
		std::pair<int, int> getCursorPos();

		/**
		 * Switches the cursor invisible.
		 */
		void cursorOff();

		/**
		 * Switches the cursor visible.
		 */
		void cursorOn();

		/**
		 * Toggles the cursor between visible & invisible.
		 */
		void cursorOnOffSwitch();


	} // END namespace Console

} // END namespace Trip

#endif /* __ConsoleController_HPP__ */
