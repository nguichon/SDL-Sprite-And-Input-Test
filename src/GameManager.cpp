/*
 * GameManager.cpp
 *
 *  Created on: Mar 29, 2012
 *      Author: nguichon
 */

#include "../include/GameManager.h"
#include <stdio.h>

char DString[100];

GameManager* GameManager::m_Instance = 0;

//Private constructor for use with singleton.
GameManager::GameManager() {
	m_GameState = GAMEPLAYMODE;
	m_Running = false;
	m_CurrentMenu = GameMenu::LoadMenu( "test.menu" );
}

//Singleton "get" method, returns a pointer to the single instance of WindowManager
GameManager* GameManager::get() {
	//If instance does not exist, create it.
	if( m_Instance == 0 ) {	m_Instance = new GameManager();	}
	return m_Instance;
}

//Starts the game loop IF it has not been already.
void GameManager::Start() {
	if( !m_Running ) {
		GameManager::GameLoop();
	}
}

//This is the game loop
void GameManager::GameLoop() {
	bool endGame = false;
	SDL_Event e;
	long time = SDL_GetTicks(); long passed = 0;
	long frameRate = 33;
	bool keyChanged = false;
	while(!endGame){
		while(SDL_PollEvent(&e)){
				switch(e.type){
				case SDL_MOUSEBUTTONDOWN:
					switch(m_GameState){
					case MENUMODE:
						m_CurrentMenu->MenuPressed( (double)e.button.x/VariableBox::get()->xResolution, (double)e.button.y/VariableBox::get()->yResolution );
						break;
					}
					break;
				case SDL_KEYDOWN:
					if( e.key.keysym.sym == VariableBox::get()->movement_Up ) {
						VariableBox::get()->keyUp = true;
						keyChanged = true;
					}
					if( e.key.keysym.sym == VariableBox::get()->movement_Down ) {
						VariableBox::get()->keyDown = true;
						keyChanged = true;

					}
					if( e.key.keysym.sym == VariableBox::get()->movement_Left ) {
						VariableBox::get()->keyLeft = true;
						keyChanged = true;
					}
					if( e.key.keysym.sym == VariableBox::get()->movement_Right ) {
						VariableBox::get()->keyRight = true;
						keyChanged = true;
					}
					break;
				case SDL_KEYUP:
					if( e.key.keysym.sym == VariableBox::get()->movement_Up ) {
						VariableBox::get()->keyUp = false;
						keyChanged = true;
					}
					if( e.key.keysym.sym == VariableBox::get()->movement_Down ) {
						VariableBox::get()->keyDown = false;
						keyChanged = true;
					}
					if( e.key.keysym.sym == VariableBox::get()->movement_Left ) {
						VariableBox::get()->keyLeft = false;
						keyChanged = true;
					}
					if( e.key.keysym.sym == VariableBox::get()->movement_Right ) {
						VariableBox::get()->keyRight = false;
						keyChanged = true;
					}
					break;
				case SDL_QUIT:
					endGame = true;
					break;
				}
		}
		passed = SDL_GetTicks() - time;
		if( passed > frameRate ) {
			time = SDL_GetTicks();
			HandlePlayer( keyChanged, passed );
			passed = 0; keyChanged = false;
		}
	}
}

Button::Button() {

}
void GameMenu::MenuPressed( double x, double y ) {
	Button* current = 0;
	for( unsigned int i = 0; i < m_Buttons.size(); i++ ) {
		if ( m_Buttons[i]->x < x && m_Buttons[i]->x + m_Buttons[i]->w > x && m_Buttons[i]->y < y && m_Buttons[i]->y + m_Buttons[i]->h > y ) {
			current = m_Buttons[i];
		}
	}
	if( current != 0 ) {
		current->Activate();
	}
}
GameMenu::GameMenu() {
	m_Buttons.push_back( new Button() );
	m_Buttons.push_back( new Button() );
	m_Buttons.push_back( new Button() );
	m_Buttons[0]->text = "TOP";
	m_Buttons[1]->text = "MIDDLE";
	m_Buttons[2]->text = "BOTTOM";

	m_Buttons[0]->w = 1.0;
	m_Buttons[1]->w = 1.0;
	m_Buttons[2]->w = 1.0;

	m_Buttons[0]->h = 0.33;
	m_Buttons[1]->h = 0.33;
	m_Buttons[2]->h = 0.33;

	m_Buttons[0]->x = 0.0;
	m_Buttons[1]->x = 0.0;
	m_Buttons[2]->x = 0.0;

	m_Buttons[0]->y = 0.0;
	m_Buttons[1]->y = 0.33;
	m_Buttons[2]->y = 0.66;
}
GameMenu* GameMenu::LoadMenu( std::string path ) {
	GameMenu* toReturn = new GameMenu();
	return toReturn;
}

void Button::Activate() {
	SDL_WM_SetCaption( text.c_str(), "" );
}


void GameManager::HandlePlayer( bool keyChanged, long passed ) {
	if( keyChanged ) {
		bool doChangeDirection = false;
		bool didDirectionChange = false;
		if(( VariableBox::get()->playerFacing == DIRECTION_UP && !VariableBox::get()->keyUp )||
				( VariableBox::get()->playerFacing == DIRECTION_DOWN && !VariableBox::get()->keyDown )||
				( VariableBox::get()->playerFacing == DIRECTION_LEFT && !VariableBox::get()->keyLeft )||
				( VariableBox::get()->playerFacing == DIRECTION_RIGHT && !VariableBox::get()->keyRight )) {
			doChangeDirection = true;
		}
		if( VariableBox::get()->keyUp && !VariableBox::get()->keyDown && !VariableBox::get()->keyLeft && !VariableBox::get()->keyRight ) {
			//GO UP
			SDL_WM_SetCaption("UP","");
			if( VariableBox::get()->playerFacing != DIRECTION_UP ) {
				VariableBox::get()->playerFacing = DIRECTION_UP;
				didDirectionChange = true;
			}
			VariableBox::get()->m_Player->SetMovement( 0, -50 );
		}
		if( !VariableBox::get()->keyUp && VariableBox::get()->keyDown && !VariableBox::get()->keyLeft && !VariableBox::get()->keyRight ) {
			//GO DOWN
			SDL_WM_SetCaption("DOWN","");
			if( VariableBox::get()->playerFacing != DIRECTION_DOWN ) {
				VariableBox::get()->playerFacing = DIRECTION_DOWN;
				didDirectionChange = true;
			}
			VariableBox::get()->m_Player->SetMovement( 0, 50 );
		}
		if( !VariableBox::get()->keyUp && !VariableBox::get()->keyDown  && VariableBox::get()->keyLeft && !VariableBox::get()->keyRight ) {
			//GO LEFT
			SDL_WM_SetCaption("LEFT","");
			if( VariableBox::get()->playerFacing != DIRECTION_LEFT ) {
				VariableBox::get()->playerFacing = DIRECTION_LEFT;
				didDirectionChange = true;
			}
			VariableBox::get()->m_Player->SetMovement( -50, 0 );
		}
		if( !VariableBox::get()->keyUp && !VariableBox::get()->keyDown  && !VariableBox::get()->keyLeft && VariableBox::get()->keyRight  ) {
			//GO RIGHT
			SDL_WM_SetCaption("RIGHT","");
			if( VariableBox::get()->playerFacing != DIRECTION_RIGHT ) {
				VariableBox::get()->playerFacing = DIRECTION_RIGHT;
				didDirectionChange = true;
			}
			VariableBox::get()->m_Player->SetMovement( 50, 0 );
		}
		if( VariableBox::get()->keyUp && !VariableBox::get()->keyDown  && VariableBox::get()->keyLeft && !VariableBox::get()->keyRight  ) {
			//GO UPLEFT
			SDL_WM_SetCaption("UPLEFT","");
			if( doChangeDirection == true ) {
				VariableBox::get()->playerFacing = DIRECTION_UP;
				didDirectionChange = true;
			}
			VariableBox::get()->m_Player->SetMovement( -35.3, -35.3 );
		}
		if( VariableBox::get()->keyUp && !VariableBox::get()->keyDown  && !VariableBox::get()->keyLeft && VariableBox::get()->keyRight  ) {
			//GO UPLEFT
			SDL_WM_SetCaption("UPRIGHT","");
			if( doChangeDirection == true ) {
				VariableBox::get()->playerFacing = DIRECTION_UP;
				didDirectionChange = true;
			}
			VariableBox::get()->m_Player->SetMovement( 35.3, -35.3 );
		}
		if( !VariableBox::get()->keyUp && VariableBox::get()->keyDown  && VariableBox::get()->keyLeft && !VariableBox::get()->keyRight  ) {
			//GO UPLEFT
			SDL_WM_SetCaption("DOWNLEFT","");
			if( doChangeDirection == true ) {
				VariableBox::get()->playerFacing = DIRECTION_DOWN;
				didDirectionChange = true;
			}
			VariableBox::get()->m_Player->SetMovement( -35.3, 35.3 );
		}
		if( !VariableBox::get()->keyUp && VariableBox::get()->keyDown  && !VariableBox::get()->keyLeft && VariableBox::get()->keyRight  ) {
			//GO UPLEFT
			SDL_WM_SetCaption("DOWNRIGHT","");
			if( doChangeDirection == true ) {
				VariableBox::get()->playerFacing = DIRECTION_DOWN;
				didDirectionChange = true;
			}
			VariableBox::get()->m_Player->SetMovement( 35.3, 35.3 );
		}

		if( !VariableBox::get()->keyUp && !VariableBox::get()->keyDown && !VariableBox::get()->keyLeft && !VariableBox::get()->keyRight ) {
			//STOP
			SDL_WM_SetCaption("STOP","");
			VariableBox::get()->m_Player->SetMovement( 0, 0 );
			VariableBox::get()->moving = false;
			switch( VariableBox::get()->playerFacing ) {
				case DIRECTION_UP:
					VariableBox::get()->m_Player->GetSprite()->SetAnimation("standup");
					break;
				case DIRECTION_DOWN:
					VariableBox::get()->m_Player->GetSprite()->SetAnimation("standdown");
					break;
				case DIRECTION_LEFT:
					VariableBox::get()->m_Player->GetSprite()->SetAnimation("standleft");
					break;
				case DIRECTION_RIGHT:
					VariableBox::get()->m_Player->GetSprite()->SetAnimation("standright");
					break;
			}
		} else {
			if(didDirectionChange || VariableBox::get()->moving == false) {
				switch( VariableBox::get()->playerFacing ) {
				case DIRECTION_UP:
					VariableBox::get()->m_Player->GetSprite()->SetAnimation("moveup");
					break;
				case DIRECTION_DOWN:
					VariableBox::get()->m_Player->GetSprite()->SetAnimation("movedown");
					break;
				case DIRECTION_LEFT:
					VariableBox::get()->m_Player->GetSprite()->SetAnimation("moveleft");
					break;
				case DIRECTION_RIGHT:
					VariableBox::get()->m_Player->GetSprite()->SetAnimation("moveright");
					break;
				}
			}
			VariableBox::get()->moving = true;
		}
	}
	VariableBox::get()->m_Player->Update( passed );
}
