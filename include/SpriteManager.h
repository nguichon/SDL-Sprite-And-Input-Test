/*
 * SpriteManager.h
 *
 *  Created on: Mar 31, 2012
 *      Author: nguichon
 */

#ifndef SPRITEMANAGER_H_
#define SPRITEMANAGER_H_
#include <string>
#include <iostream>
#include <fstream>
#include <SDL/SDL.h>
#include "main.h"
#include "ImageManager.h"
#include <map>

//#include<boost/property_map/property_map.hpp>

class AnimationStep;
class Sprite;
class SpriteInstance;

class Sprite {
private:
	Sprite();
	//boost::intrusive::property_map<int, AnimationStep*> m_Animations;
	std::map<int, AnimationStep*> m_Animations;
	int m_BaseAnimation;
	SDL_Surface* m_Image;
public:
	static Sprite* LoadSprite( const char* );
	AnimationStep* GetAnimation( const char* );
	AnimationStep* GetAnimation( int );
	SpriteInstance* CreateInstance();
	SDL_Surface* GetImage();
};

class SpriteInstance {
private:
	AnimationStep* m_Animation;
	Sprite* m_BaseSprite;
	long m_Time;

	int m_XLocation, m_YLocation;
	bool m_Enabled; bool m_Animate;
public:
	SpriteInstance( Sprite* base );
	void ReceiveMessage();
	void SetAnimation( const char* );
	void SetAnimation( int );
	AnimationStep* Update( long timePassed );
	SDL_Surface* GetImage();
};

class AnimationStep {
private:
	AnimationStep();

	int x, y, w, h;
	AnimationStep* m_Next;
	long m_Duration;
public:
	static AnimationStep* LoadAnimation( const char* );

	int getX(); int getY(); int getW(); int getH();
	long Duration();
	AnimationStep* NextAnimationStep();
};


#endif /* SPRITEMANAGER_H_ */
