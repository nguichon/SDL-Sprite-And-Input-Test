/*
 * main.cpp
 *
 *  Created on: Mar 27, 2012
 *      Author: nguichon
 */

#include "../include/main.h"

int ReadConfiguration( ) {
	namespace po = boost::program_options;
	const char* testFileName = "config.ini";
	std::ifstream s;
	s.open(  testFileName );

	/*po::options_description desc("Allowed options");
	desc.add_options()
		 ("x", po::value<int>(), "Width of the game window")
		 ("left", po::value<int>(), "Key to move the main character left")
		 ("right", po::value<int>(), "Key to move the main character right")
		 ("down", po::value<int>(), "Key to move the main character down")
		 ("up", po::value<int>(), "Key to move the main character up")
		 ("y", po::value<int>(), "Height of the game window");

	po::variables_map vm;
	po::store(po::parse_config_file( s, desc, false ), vm);
	po::notify(vm);*/

	VariableBox::get()->xResolution = 1000;//vm["x"].as<int>();
	VariableBox::get()->yResolution = 600;//vm["y"].as<int>();
	VariableBox::get()->movement_Down = (SDLKey)274;//(SDLKey)vm["down"].as<int>();
	VariableBox::get()->movement_Up = (SDLKey)273;//(SDLKey)vm["up"].as<int>();
	VariableBox::get()->movement_Left = (SDLKey)276;//(SDLKey)vm["left"].as<int>();
	VariableBox::get()->movement_Right = (SDLKey)275;//(SDLKey)vm["right"].as<int>();
	//int z = vm["left"].as<int>();

	return 0;
}

int main(int argc, char *argv[]) {
#ifdef LOGGER_ENABLED
	Logger::get()->Output( "Startup" );
#endif
	if( ReadConfiguration() != 0 ) {
		return -1; //Invalid Configuration
	}

	if( WindowManager::get()->Startup() != 0 ) {
		return -2; //WindowManager failed to startup
	}
#ifdef LOGGER_ENABLED
	Logger::get()->Output( "Startup Successful" );
#endif

	//TODO: REMOVE THIS CODE
	Sprite* s = Sprite::LoadSprite( "resources\\data\\sprites\\link.sprite" );
	Entity* e = new Entity( s, 0, 0, 0, 0 );
	VariableBox::get()->m_Player = e;

#ifdef LOGGER_ENABLED
	Logger::get()->Output( "Starting game manager" );
#endif
	GameManager::get()->Start();

	SDL_Quit();
	Logger::Close();
	return 0;
}



VariableBox* VariableBox::m_Instance = 0;
VariableBox* VariableBox::get() {
	if( m_Instance == 0 ) {
		m_Instance = new VariableBox();
	}
	return m_Instance;
}
VariableBox::VariableBox() {
	moving = false;
	keyDown = false;
	keyUp = false;
	keyLeft = false;
	keyRight = false;
	WorldPositionX = 0;
	WorldPositionY = 0;
}



