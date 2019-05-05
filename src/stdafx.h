/**
 * This file lists all header files that shall be precompiled by Visual Studio.
 * @author barn
 * @version 20121026
 */
#ifndef __stdafx_H__
#define __stdafx_H__

/*===========================================================================*
 * INCLUDES base definition file for DLL import/export
 *===========================================================================*/

/*===========================================================================*
 * INCLUDES project headers
 *===========================================================================*/

/*===========================================================================*
 * INCLUDES C/C++ standard library (and other external libraries)
 *===========================================================================*/
#include <OGRE/Ogre.h>
#include <Ogre/OgreException.h>
#include <Ogre/OgreRoot.h>
#include <Ogre/OgreConfigFile.h>
#include <Ogre/OgreCamera.h>
#include <Ogre/OgreViewport.h>
#include <Ogre/OgreSceneManager.h>
#include <Ogre/OgreRenderWindow.h>
#include <Ogre/OgreEntity.h>
#include <Ogre/OgreWindowEventUtilities.h>
#include <OGRE/OgreHardwarePixelBuffer.h>


#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>


#include <Defines.h>
#include <util/Logger.hpp>
#include <util/ConsoleController.hpp>

// any other header can be included, as usual
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif


/*===========================================================================*
 * DEFINES and MACROS
 *===========================================================================*/

/*===========================================================================*
 * NAMESPACE, CONSTANTS and TYPE DECLARATIONS/IMPLEMENTATIONS
 *===========================================================================*/


#endif /* __stdafx_H__ */
