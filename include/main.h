/*
 * main.h
 *
 *  Created on: Mar 27, 2012
 *      Author: nguichon
 *
 *
 *      This is the main header, it will be included in all other .h header files.
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "Logger.h"

#include <SDL/SDL.h>
#include <stdio.h>
#include <boost/program_options.hpp>
#include <boost/functional/hash.hpp>
#include <iostream>
#include <fstream>

#include "WindowManager.h"
#include "ImageManager.h"
#include "SpriteManager.h"
#include "GameManager.h"

class Entity;

const int DIRECTION_UP   	= 	0;
const int DIRECTION_DOWN 	= 	1;
const int DIRECTION_LEFT 	= 	2;
const int DIRECTION_RIGHT 	= 	3;

/**
 * The variable box is a storage unit for global variables.
 */
class VariableBox {
private:
	static VariableBox* m_Instance;	//Singleton
	VariableBox();	//private constructor
public:
	int xResolution; int yResolution;	//This is the size of the game window.
	double xScale; double yScale;		//This is unused currently.
	Entity* m_Player;					//This is the entity that represents the player. Directly controlled by the player.
	SDLKey movement_Up; SDLKey movement_Down; SDLKey movement_Left; SDLKey movement_Right;	//These are the keys setup by the config.ini file
	bool keyUp, keyDown, keyLeft, keyRight; int playerFacing; bool moving;
	boost::hash<std::string> m_StringHash;	//Use to hash all strings that need to be hashed

	int WorldPositionX; int WorldPositionY;

	static VariableBox* get();	//Singleton getter
};

#endif /* MAIN_H_ */
