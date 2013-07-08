/*
 * ImageManager.h
 *
 *  Created on: Apr 1, 2012
 *      Author: nguichon
 */

#ifndef IMAGEMANAGER_H_
#define IMAGEMANAGER_H_

#include <SDL/SDL.h>
#include <SDL/SDL_Image.h>
#include <map>
#include "main.h"

class ImageManager {
private:
	static ImageManager* m_Instance;
	ImageManager();

	std::map<int, SDL_Surface*> m_LoadedImages;
	SDL_Surface* LoadImage( const char* );
public:
	static ImageManager* get();
	SDL_Surface* GetImage( const char* );

};


#endif /* IMAGEMANAGER_H_ */
