/*
 * WindowManager.h
 *
 *  Created on: Mar 27, 2012
 *      Author: nguichon
 */

#ifndef WINDOWMANAGER_H_
#define WINDOWMANAGER_H_

#include "main.h"

#include <SDL/SDL.h>

class WindowManager {
private:
	static WindowManager* m_Instance;
	WindowManager();

	SDL_Surface* m_WindowScreen;
public:
	static WindowManager* get();
	int Startup();
	void BlitImage( SDL_Surface*, double, double, int, int, int, int );
	void BlitImage( SDL_Surface*, int, int, int, int, int, int );
};


#endif /* WINDOWMANAGER_H_ */
