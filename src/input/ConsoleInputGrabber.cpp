/**
 * Implementation file for the ConsoleInputGrabber.hpp.
 * @author barn
 * @version 20121030
 */

/*===========================================================================*
 * INCLUDES (associated header files)
 *===========================================================================*/
#include "ConsoleInputGrabber.hpp"

/*===========================================================================*
 * INCLUDES project headers
 *===========================================================================*/

/*===========================================================================*
 * INCLUDES C/C++ standard library (and other external libraries)
 *===========================================================================*/

/*===========================================================================*
 * DEFINES and MACROS
 *===========================================================================*/

/// maximum line size for entering. When you enter longer lines, undefined behaviour occurs.
#define MAX_LINE_SIZE 80

/*===========================================================================*
 * NAMESPACE, CONSTANTS and TYPE DECLARATIONS/IMPLEMENTATIONS
 *===========================================================================*/

namespace Trip
{
	
	/**
	 * Method that will be performed in parallel.
	 * Will be used by boost::thread and boost::ref.
	 */
	void ConsoleInputGrabber::operator()()
	{
		Trip::Console::setColor( Console::GRAY);
		std::cout << _pre_string;

		Trip::Console::setColor( Console::STD);
		std::cin.sync();
		std::cin.clear();
	
		char str[MAX_LINE_SIZE];

		std::cin.getline( str, MAX_LINE_SIZE);
		_line = str;
		_ready = true;
	}

} // END namespace Trip