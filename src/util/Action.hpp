/**
 * The Action enum counts up all the actions that shall be possible by entering some input.
 * @author barn
 * @version 20121015
 */
#ifndef __Action_HPP__
#define __Action_HPP__

/*===========================================================================*
 * INCLUDES base definition file for DLL import/export
 *===========================================================================*/

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
	 * This enum counts all the actions that shall be possible when entering some input.
	 */
	enum Action
	{
		RESET_ALL,
		EXIT,
		RESTART,
		REINIT_RESOURCES,
		TOGGLE_FULLSCREEN,
		SCREENSHOT,

		MODEL_NEXT,
		MODEL_PREV,
		MODEL_STD,

		MAT_NEXT,
		MAT_PREV,
		MAT_STD,

		COMPOSITOR_NEXT,
		COMPOSITOR_PREV,
		COMPOSITOR_STD,

		CAM_MOVE_UP,
		CAM_MOVE_DOWN,
		CAM_MOVE_LEFT,
		CAM_MOVE_RIGHT,

		CAM_SPEED_UP,
		CAM_SPEED_DOWN,
		CAM_SPEED_STD,

		CAM_ZOOM_IN,
		CAM_ZOOM_OUT,
		CAM_ZOOM_STD

	}; // END enum Action

} // END namespace Trip

#endif /* __Action_HPP__ */
