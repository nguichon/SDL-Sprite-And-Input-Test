/*
 * Sprite.cpp
 *
 *  Created on: Mar 31, 2012
 *      Author: nguichon
 */
#include "../include/SpriteManager.h"

Sprite::Sprite() {	}

Sprite* Sprite::LoadSprite( const char* filename ) {
	Sprite* toReturn = new Sprite();
	std::ifstream reader;
	reader.open( filename );
	char* s = new char[512];
	int hash;
	reader.getline( s, 512 );
	toReturn->m_Image = ImageManager::get()->GetImage( s );
	while( !reader.eof() ) {
		reader.getline( s, 512 );
		hash = VariableBox::get()->m_StringHash(s);
		reader.getline( s, 512 );
		toReturn->m_Animations[hash] = AnimationStep::LoadAnimation( s );
	}
	return toReturn;
}

SpriteInstance* Sprite::CreateInstance() {
	SpriteInstance* toReturn = new SpriteInstance( this );
	return toReturn;
}

SpriteInstance::SpriteInstance( Sprite* baseSprite ) {
	m_BaseSprite = baseSprite;
	m_Animation = baseSprite->GetAnimation("moveup");
	m_Animate = true;
	m_Enabled = true;
}

AnimationStep* Sprite::GetAnimation( const char* name ) {
	return GetAnimation( VariableBox::get()->m_StringHash(name) );
}
AnimationStep* Sprite::GetAnimation( int name ) {
	return m_Animations[name];
}
SDL_Surface* SpriteInstance::GetImage() {
	return m_BaseSprite->GetImage();
}
SDL_Surface* Sprite::GetImage() {
	return m_Image;
}
AnimationStep* SpriteInstance::Update( long timePassed ) {
	if( m_Animate ) {
		m_Time+=timePassed;
		if(m_Time > m_Animation->Duration()) {
			m_Time = m_Time%m_Animation->Duration();
			m_Animation = m_Animation->NextAnimationStep();
		}
	}
	return m_Animation;
}
int AnimationStep::getX() {
	return x;
}

int AnimationStep::getY() {
	return y;
}
int AnimationStep::getW() {
	return w;
}
int AnimationStep::getH() {
	return h;
}

void SpriteInstance::SetAnimation( int animation) {
	m_Time = 0;
	m_Animation = m_BaseSprite->GetAnimation(animation);
}
void SpriteInstance::SetAnimation( const char* animation) {
	m_Time = 0;
	m_Animation = m_BaseSprite->GetAnimation(animation);
}
