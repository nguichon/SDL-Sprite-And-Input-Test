/*
 * GameManager.h
 *
 *  Created on: Mar 29, 2012
 *      Author: nguichon
 */

#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

const int MENUMODE = 0;
const int GAMEPLAYMODE = 1;

#include <SDL/SDL.h>
#include <boost/container/vector.hpp>
#include "main.h"

class SpriteInstance;
class Sprite;

class Button {
public:
	std::string text;
	double x; double y;
	double w; double h;
	Button();
	void Activate();
};

class GameMenu {
private:
	boost::container::vector<Button*> m_Buttons;
	GameMenu();
public:
	static GameMenu* LoadMenu( std::string );
	void MenuPressed( double x, double y );
};

class Entity {
private:
	SpriteInstance* m_Sprite;
	double m_CenterX; double m_CenterY; //World-based, affect by camera and shit
	int m_Width; int m_Height; //if width is -1, the collision is circle based, using height as radius

	double m_MovementX; double m_MovementY;
public:
	Entity( Sprite*, int, int, int, int );
	SpriteInstance* GetSprite();
	void Update( long );
	void Offset( int, int, bool );
	void SetMovement( double, double );
	void Move( int, int, bool );
	bool CheckCollision( Entity* );
	int GetXPos();
	int GetYPos();
	//Process messages here
};

class GameManager {
private:
	static GameManager* m_Instance;
	GameManager();

	int m_GameState; bool m_Running;
	GameMenu* m_CurrentMenu;
	void GameLoop();
	void HandlePlayer( bool, long );
public:
	static GameManager* get();
	void Start();
};


#endif /* GAMEMANAGER_H_ */
