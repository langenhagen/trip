/**
 * Implementation File for Logger.hpp
 * @author barn
 * @version 20121027
 */

/*===========================================================================*
 * INCLUDES (associated header files)
 *===========================================================================*/
#include "Logger.hpp"

/*===========================================================================*
 * INCLUDES project headers
 *===========================================================================*/

/*===========================================================================*
 * INCLUDES C/C++ standard library (and other external libraries)
 *===========================================================================*/
#include <iostream>

/*===========================================================================*
 * DEFINES and MACROS
 *===========================================================================*/

/*===========================================================================*
 * NAMESPACE, CONSTANTS and TYPE DECLARATIONS/IMPLEMENTATIONS
 *===========================================================================*/

namespace Trip
{

	/**
	 * Logs a message according to the type of the message.
	 * @param message The message string to be logged.
	 * @param type The message type to be logged, according to the
	 * MessageType enumeration.
	 */
	void log( std::string message, MessageType type)
	{
		if( type == MSG_NORMAL)
		{
			Trip::Console::setColor( Console::STD);
			std::cout << message << std::endl;
		}
		else if( type == MSG_ERROR)
		{
			Trip::Console::setColor( Console::YELLOW);
			std::cerr << "ERROR: ";
			Trip::Console::setColor( Console::STD);
			std::cerr << message << std::endl;
		}
		else if( type == MSG_EXCEPTION)
		{
			Trip::Console::setColor( Console::RED);
			std::cerr << "EXCEPTION: ";
			Trip::Console::setColor( Console::STD);
			std::cerr << message << std::endl;
		}
	}


	/**
	 * Logs a message according to the type of the message.
	 * @param message The message string to be logged.
	 * @param type The message type to be logged, according to the
	 * MessageType enumeration.
	 */
	void Logger::log( std::string message, MessageType type)
	{
		if( type == MSG_NORMAL)
		{
			std::cout << message << std::endl;
		}
		else if( type == MSG_ERROR)
		{
			std::cerr << "ERROR: " << message << std::endl;
		}
		else if( type == MSG_EXCEPTION)
		{
			std::cerr << "EXCEPTION: " << message << std::endl;
		}
	}

} // END namespace Trip
