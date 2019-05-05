/**
 * This File contains a class that can grab console input in a paralleled thread.
 * @author barn
 * @version 20121030
 */
#ifndef __ConsoleInputGrabber_HPP__
#define __ConsoleInputGrabber_HPP__

/*===========================================================================*
 * INCLUDES base definition file for DLL import/export
 *===========================================================================*/
 
/*===========================================================================*
 * INCLUDES project headers
 *===========================================================================*/
 
/*===========================================================================*
 * INCLUDES C/C++ standard library (and other external libraries)
 *===========================================================================*/
#include "stdafx.h"

/*===========================================================================*
 * DEFINES and MACROS
 *===========================================================================*/
 
/*===========================================================================*
 * NAMESPACE, CONSTANTS and TYPE DECLARATIONS/IMPLEMENTATIONS
 *===========================================================================*/

namespace Trip
{

	/**
	 * This class provides a console input grabber that works in a parallel thread
	 * in order not to disturb the render loop.
	 */
	class ConsoleInputGrabber
	{
	private: // vars

		/// The line that was entered.
		String _line;

		/// Indicates if the input grabber can provide a new line.
		bool _ready;
		
		/// A string that will be printed right before the console input will be asked.
		String _pre_string;


	public: // constructor & destructior

		/**
		 * Main constructor.
		 */
		ConsoleInputGrabber()
			: _ready(false),
			_line("")
		{}

		/**
		 * Destructor.
		 */
		~ConsoleInputGrabber()
		{}

	public: // methods

		/**
		 * Method that will be performed in parallel.
		 * Will be used by boost::thread and boost::ref.
		 * You usually do not need to touch this method by yourself.
		 */
		void operator()();

		/**
		 * Retrieves the current line.
		 * @return The line that was entered on the console.
		 */
		std::string getLine()
		{
			// ERRORPRONE through parallel writing to _line and reading from it.
			_ready = false;
			return _line;
		}

		/**
		 * Indicates, whether a new line was entered and is ready to process.
		 * @return
		 * TRUE - a new line was entered and is ready to be used. You may call getLine().
		 * FALSE - there is no new line entered and it is not necessecary to call getLine() again.
		 * @see getLine()
		 */
		bool isReady()
		{
			return _ready;
		}

		/**
		 * Makes the ConsoleInputGrabber work in parallel for one line.
		 * In order to be able to read a line,
		 * you should call this method after creation of an ConsoleInputGrabber object
		 * and you should call runThread() again after reading one line.
		 * @param pre_string If you want a string to be printed right before the console input,
		 * you can enter this string here.
		 */
		void runThread( String pre_string = "")
		{
			_pre_string = pre_string;
			boost::thread( boost::ref( *this));
		}


	}; // END class ConsoleInputGrabber

} // END namespace Trip


#endif /* __ConsoleInputGrabber_HPP__ */
