/*
 * WindowManager.cpp
 *
 *  Created on: Mar 27, 2012
 *      Author: nguichon
 */

#include "../include/WindowManager.h"


WindowManager* WindowManager::m_Instance = 0;

//Private constructor for use with singleton.
WindowManager::WindowManager() {	}

//Singleton "get" method, returns a pointer to the single instance of WindowManager
WindowManager* WindowManager::get() {
	//If instance does not exist, create it.
	if( m_Instance == 0 ) {	m_Instance = new WindowManager();	}
	return m_Instance;
}

//Creates the window and startups SDL.
int WindowManager::Startup() {
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){	/*TODO: Video failed to initialize*/ return -1;	}
	//If the window fails to initialize, shut down SDL.
	if (!( m_WindowScreen = SDL_SetVideoMode( VariableBox::get()->xResolution, VariableBox::get()->yResolution, 32, SDL_HWSURFACE))) {	SDL_Quit(); return -1;	}
	return 0;
}


void WindowManager::BlitImage( SDL_Surface* image, double targetX, double targetY, int sourceX, int sourceY, int w, int h ) {
	int x = (double)targetX*(double)VariableBox::get()->xResolution;
	int y = (double)targetY*(double)VariableBox::get()->yResolution;
	BlitImage( image, x, y, sourceX, sourceY, w, h );
}
void WindowManager::BlitImage( SDL_Surface* image, int targetX, int targetY, int sourceX, int sourceY, int w, int h ) {
	SDL_Rect* point = new SDL_Rect();
	point->w = VariableBox::get()->xResolution;
	point->h = VariableBox::get()->yResolution;
	SDL_FillRect( m_WindowScreen, point, 0);
	SDL_Rect* source = new SDL_Rect();
	source->x = sourceX;
	source->y = sourceY;
	source->w = w;
	source->h = h;
	SDL_Rect* target = new SDL_Rect();
	target->x = targetX;
	target->y = targetY;
	target->w = w;
	target->h = h;
	SDL_BlitSurface(  image, source,m_WindowScreen, target );
	delete source;
	delete target;
	SDL_Flip( m_WindowScreen );
}

