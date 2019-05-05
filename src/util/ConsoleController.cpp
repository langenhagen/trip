/**
 * Implementation file for the ConsoleController.hpp.
 * @author barn
 * @version 20121101
 */

/*===========================================================================*
 * INCLUDES (associated header files)
 *===========================================================================*/
#include "util/ConsoleController.hpp"

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
	namespace Console
	{
		/// out handle
		static HANDLE hStdOut;
		
		/// screen buffer info
		static CONSOLE_SCREEN_BUFFER_INFO csbInfo;


		/**
		 * Clears the screen.
		 * @return
		 * FALSE - on error
		 * TRUE - if it worked
		 */
		bool cls()
		{
			COORD home = { 0, 0 };          // home position
			DWORD dwCellsWritten;           // num of bewritten char cells
			DWORD dwConSize;                // num of chars in buffer

			// get size of buffer and current attribute
			hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); 
			GetConsoleScreenBufferInfo(hStdOut, &csbInfo);

			dwConSize = csbInfo.dwSize.X * csbInfo.dwSize.Y;
 
			// blanks into the buffer
			if( ! FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', dwConSize,
			home, &dwCellsWritten) )
			return false;

			// set attributes
			if( ! FillConsoleOutputAttribute(hStdOut, csbInfo.wAttributes, dwConSize,
			home, &dwCellsWritten) )
			return false;

			// place cursor in the home position
			if( ! SetConsoleCursorPosition(hStdOut, home) )
			return false;
	
			return true;
		}
		

		/**
		 * Sets the cursor to the specified position.
		 * @param line The line to put the cursor in.
		 * @param row The row tu put the cursor in.
		 * @return
		 * FALSE - on error
		 * TRUE - if it worked
		 */
		bool setCursor( int line, int row)
		{
			COORD cursorPos = {row, line};

			hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); 
			return SetConsoleCursorPosition(hStdOut, cursorPos) != 0;
		}


		/**
		 * Sets the color of the text.
		 * @param color The color value according to SetConsoleTextAttribute.
		 * @return
		 * FALSE - on error
		 * TRUE - if it worked
		 */
		bool setColor( ConsoleColor color)
		{
			hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); 
			return SetConsoleTextAttribute(hStdOut, (WORD)color) != 0;
		}


		/**
		 * Retrieves the cursor Position.
		 * @return A pair where the first value specifies the line,
		 * and the second the row.
		 */
		std::pair<int, int> getCursorPos()
		{
			int line, row;

			hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); 
			CONSOLE_SCREEN_BUFFER_INFO CSBI;
	
			GetConsoleScreenBufferInfo( hStdOut, &CSBI);

			row		= CSBI.dwCursorPosition.X;
			line	= CSBI.dwCursorPosition.Y;

			return std::pair<int,int>(line,row);
		}


		/**
		 * Switches the cursor invisible.
		 */
		void cursorOff()
		{
			CONSOLE_CURSOR_INFO cursorInfo;   
			HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); 

			GetConsoleCursorInfo( hStdOut, &cursorInfo);
			cursorInfo.bVisible = FALSE;
			SetConsoleCursorInfo( hStdOut, &cursorInfo);
		}
		

		/**
		 * Switches the cursor visible.
		 */
		void cursorOn()
		{
			CONSOLE_CURSOR_INFO cursorInfo;   
			HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); 

			GetConsoleCursorInfo( hStdOut, &cursorInfo);
			cursorInfo.bVisible = TRUE;
			SetConsoleCursorInfo( hStdOut, &cursorInfo);
		}


		/**
		 * Toggles the cursor between visible & invisible.
		 */
		void cursorOnOffSwitch()
		{
			CONSOLE_CURSOR_INFO cursorInfo;
			HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
			GetConsoleCursorInfo( hStdOut, &cursorInfo);
	
			cursorInfo.bVisible = !cursorInfo.bVisible;
		}


	} // END namespace Console

} // END namespace Trip
