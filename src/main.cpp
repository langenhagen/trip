///////////////////////////////////////////////////////////////////////////////
// INCLUDES project headers
#include "stdafx.h"

#include <Defines.h>
#include <managers/FunctionManager.hpp>
#include <managers/TripVarManager.hpp>
#include <managers/ClusterManager.hpp>
#include <managers/TransformerManager.hpp>

#include <input/ConsoleInputGrabber.hpp>
#include <input/ConsoleInterpreter.hpp>

#include <Registrator.hpp> // SEMI HACK

#include <Engine.hpp>


///////////////////////////////////////////////////////////////////////////////
//INCLUDES C/C++ standard library (and other external libraries)
#include "Ogre/Ogre.h"

///////////////////////////////////////////////////////////////////////////////
// DEFINES and MACROS

///////////////////////////////////////////////////////////////////////////////
// NAMESPACE, CONSTANTS and TYPE DECLARATIONS/IMPLEMENTATIONS



using namespace Trip;

Ogre::Root* initOgre( int argc, char** argv);

void parseResourceFile( const char* fname, bool recursive = false);




int main( int argc, char** argv)
{
	// set up ogre
	Ogre::Root* ogre = initOgre( argc, argv);
	if(!ogre)
	{
		return -1;
	}


	Ogre::RenderWindow* win = ogre->getAutoCreatedWindow();
	ogre->setFrameSmoothingPeriod( 2.5f);
	Ogre::SceneManager* scene_manager = ogre->createSceneManager(Ogre::ST_GENERIC, "scene_manager0");

	// enforce an eager manager initialization
	FunctionManager::instance();
	TripVarManager* varman = TripVarManager::instance();
	varman->setWinDimensions( win->getWidth(), win->getHeight());
	varman->setSceneManager( scene_manager);
	ClusterManager::setup( scene_manager);
	TransformerManager::instance();

	// init all resource groups TODO maybe not necessary all the time...
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	// init Functions, Transformers, Clusters
	Trip::Registrator::registerFunctions();
	Trip::Registrator::registerTransformers();
	Trip::Registrator::registerClusters();

	// this is a HACK
	{
		Ogre::Camera* camera0 = scene_manager->createCamera( "camera_name");
		Ogre::Viewport*	viewport0 = win->addViewport( camera0);

		camera0->setPosition( Ogre::Vector3(0, 0, 500));
		camera0->lookAt( Ogre::Vector3( 0, 0, 0));
		camera0->setNearClipDistance(5);
		camera0->setAspectRatio( Ogre::Real( viewport0->getActualWidth())/
									Ogre::Real( viewport0->getActualHeight()));

	} // END HACK

	// Set up console input
	ConsoleInputGrabber input_grabber;
	ConsoleInterpreter console_interpreter( TRIP_CONSOLE_SYNTAX_MAP_FILE, TRIP_CONSOLE_SYNTAX);
	input_grabber.runThread( console_interpreter.getContextString());

	// Connect the engine
	Engine* engine = new Engine();
	ogre->addFrameListener( engine);

	// render loop
	while(true)
	{
		if (win->isActive())
		{
		   ogre->renderOneFrame();
		}
		else if (win->isVisible())
		{
		   win->setActive(true);
		}

		Ogre::WindowEventUtilities::messagePump();


		if( input_grabber.isReady())
		{
			console_interpreter.interprete( input_grabber.getLine());
			input_grabber.runThread( console_interpreter.getContextString());
		}
	}

	// TODO... be tidy
	delete engine;
	delete ogre;
	return 0;
}


/**
 * Initializes OGRE.
 * @param argc The argument counter, maybe the according parameter of the main function.
 * @param argv The argument vector, maybe the according parameter of the main function.
 * @return The root element of the Ogre framework.
 */
Ogre::Root* initOgre( int argc, char** argv)
{
	// TODO dynamize
	const char* window_title = "Barns Ogre App";
	const char* plugin_file = "plugins_barn.cfg";
	const char* config_file = "ogre.cfg";
	const char* log_file = "Ogre.log";

	Ogre::Root* root = new Ogre::Root( plugin_file, config_file, log_file);

	if (!root->restoreConfig())
	{
		if (!root->showConfigDialog())
		{
			delete root;
			return 0;
		}
	}

	root->initialise( true, window_title);

	parseResourceFile( "resources_barn.cfg", false);

	return root;
}

/**
 * Parses a resource cfg file.
 * @param fname The filename, including the path.
 * @param recursive Indicates, whether to check the paths in the config file recursively or not.
 */
void parseResourceFile( const char* fname, bool recursive)
{
	Ogre::ConfigFile cf;
	cf.load( fname);

	Ogre::ResourceGroupManager& resource_manager = Ogre::ResourceGroupManager::getSingleton();

	// for every section
	Ogre::ConfigFile::SectionIterator section_iter = cf.getSectionIterator();
	while( section_iter.hasMoreElements())
	{
		Ogre::String section_name = section_iter.peekNextKey();

		// get type / path of every resource
		auto section = section_iter.getNext();
		for( auto it = section->begin(); it != section->end(); it++)
		{
			resource_manager.addResourceLocation( it->second /*name*/, it->first /* location type */, section_name, recursive);
		}
	}
}
