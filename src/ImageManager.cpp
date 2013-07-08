/*
 * ImageManager.cpp
 *
 *  Created on: Apr 1, 2012
 *      Author: nguichon
 */

#include "../include/ImageManager.h"

ImageManager* ImageManager::m_Instance = 0;

ImageManager::ImageManager() {

}
ImageManager* ImageManager::get() {
	//If instance does not exist, create it.
	if( m_Instance == 0 ) {	m_Instance = new ImageManager();	}
	return m_Instance;
}

SDL_Surface* ImageManager::LoadImage( const char* imagePath ) {
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;
	loadedImage = IMG_Load( imagePath );

	if( loadedImage != NULL ) {
		optimizedImage = SDL_DisplayFormatAlpha(loadedImage);

		SDL_FreeSurface( loadedImage );
	}

	return optimizedImage;
}

SDL_Surface* ImageManager::GetImage( const char* imagePath) {
	SDL_Surface* toReturn = m_LoadedImages[VariableBox::get()->m_StringHash( imagePath )];
	if ( toReturn==0 ) {
		toReturn = LoadImage( imagePath );
		m_LoadedImages[VariableBox::get()->m_StringHash( imagePath )] = toReturn;
	}
	return toReturn;
}
