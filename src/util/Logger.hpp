/**
 * This file contains the Logger class, that can be used to encapsulate logging from
 * the caller. It is very lightweight and can be a more dynamic substitute for the
 * std::cout function, although it can make use of std::cout.
 * @author barn
 * @version 20121027
 */
#ifndef __Logger_HPP__
#define __Logger_HPP__

/*===========================================================================*
 * INCLUDES base definition file for DLL import/export
 *===========================================================================*/

/*===========================================================================*
 * INCLUDES project headers
 *===========================================================================*/

/*===========================================================================*
 * INCLUDES C/C++ standard library (and other external libraries)
 *===========================================================================*/
#include <string>

/*===========================================================================*
 * DEFINES and MACROS
 *===========================================================================*/

/*===========================================================================*
 * NAMESPACE, CONSTANTS and TYPE DECLARATIONS/IMPLEMENTATIONS
 *===========================================================================*/


namespace Trip
{

	/**
	 * The enum MessageType defines different types of messages that can be logged.
	 * According to which MessageType will be specified when logging, the Logger will adjust
	 * the log style for a certain message.
	 */
	enum MessageType
	{
		MSG_NORMAL,
		MSG_ERROR,
		MSG_EXCEPTION
	}; // END enum MessageType

	/**
	 * Logs a message according to the type of the message.
	 * @param message The message string to be logged.
	 * @param type The message type to be logged, according to the
	 * MessageType enumeration.
	 */
	void log( std::string message, MessageType type = MSG_NORMAL);

	/**
	 * This class is a small logger that encapsulates the way an information is logged
	 * from the caller. Therefore subclasses can log information in a file, into a message box
	 * or somewhere else. However this implementation logs with help of std::cout and std::cerr.
	 */
	class Logger
	{
	public: // methods

		/**
		 * Logs a message according to the type of the message.
		 * @param message The message string to be logged.
		 * @param type The message type to be logged, according to the
		 * MessageType enumeration.
		 */
		virtual void log( std::string message, MessageType type = MSG_NORMAL);

	}; // END class Logger


} // END namespace Trip

#endif /* __Logger_HPP__ */
