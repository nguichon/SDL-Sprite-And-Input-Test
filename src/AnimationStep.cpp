/*
 * AnimationStep.cpp
 *
 *  Created on: Mar 31, 2012
 *      Author: nguichon
 */

#include "../include/SpriteManager.h"

AnimationStep* AnimationStep::LoadAnimation( const char* animationString ) {
	int i = 0; int parsed = 0;
	int currentValue = 0;
	AnimationStep* first = new AnimationStep();
	bool isFirst = true;
	AnimationStep* current = first;
	while( animationString[i] != '\0') {
		if( animationString[i] >= '0' && animationString[i] <= '9' ) {
			currentValue *= 10;
			currentValue += animationString[i] - '0';
		}
		if( animationString[i] == ',') {
			//std::string s;// = currentValue;
			//s << currentValue;
			switch( parsed ) {
			case 0:
				if( isFirst ) {
					isFirst = false;
				} else {
					current->m_Next = new AnimationStep();
					current = current->m_Next;
				}
				current->m_Duration = currentValue;
				parsed++;
				break;
			case 1:
				current->x = currentValue;
				parsed++;
				break;
			case 2:
				current->y = currentValue;
				parsed++;
				break;
			case 3:
				current->w = currentValue;
				parsed++;
				break;
			case 4:
				current->h = currentValue;
				parsed = 0;
				break;
			default:
				SDL_WM_SetCaption(" YOU SUCK ", "" );
				break;
			}
			currentValue = 0;
		}
		i++;
	}
	current->m_Next=first;
	return first;
}

AnimationStep::AnimationStep() {
	m_Next = 0;
}

long AnimationStep::Duration() {
	return m_Duration;
}

AnimationStep* AnimationStep::NextAnimationStep() {
	return m_Next;
}
