/*
 * Entity.cpp
 *
 *  Created on: Apr 3, 2012
 *      Author: nguichon
 */
#include "../include/GameManager.h"

Entity::Entity( Sprite* sprite, int x, int y, int w, int h ) {
	m_Sprite = sprite->CreateInstance();
	//m_CenterX = 120;
	m_CenterY = y;
	m_Width = w;
	m_Height = h;
	m_MovementX = 0;
	m_MovementY = 0;
	m_CenterX = x;
}

void Entity::Update( long timePassed ) {
	m_CenterY += m_MovementY * (double)(timePassed / 1000.0);
	m_CenterX += m_MovementX * (double)(timePassed / 1000.0);
	AnimationStep* as;
	as = m_Sprite->Update( timePassed );
	WindowManager::get()->BlitImage( m_Sprite->GetImage(), (int)m_CenterX - VariableBox::get()->WorldPositionX + VariableBox::get()->xResolution/2,
			(int)m_CenterY - VariableBox::get()->WorldPositionY + VariableBox::get()->yResolution/2, as->getX(), as->getY(), as->getW(), as->getH());
}

void Entity::SetMovement( double x, double y ) {
	m_MovementX = x;
	m_MovementY = y;
}

SpriteInstance* Entity::GetSprite() {
	return m_Sprite;
}

int Entity::GetXPos() {
	return m_CenterX;
}
int Entity::GetYPos() {
	return m_CenterY;
}
