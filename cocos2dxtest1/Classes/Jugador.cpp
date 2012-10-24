//
//  Jugador.cpp
//  cocos2dxtest1
//
//  Created by Cristián Arenas Ulloa on 10/23/12.
//
//

#include "Jugador.h"

Jugador::Jugador (bool isSecondPlayer, CCRect area)
: multitouch(isSecondPlayer+1, 10.0, 0.001, 0.001, 1, 5, area),
  isSecondPlayer(isSecondPlayer)
{
//	this->schedule(schedule_selector(Jugador::update));
	
	sprite = CCSprite::create("stay.png");
	// Dejemos que se caiga si esto no funca
	
//	CCSize size = CCDirector::sharedDirector()->getWinSize();
//	sprite->setPosition(ccp(200, size.height*3/4));
	addChild(sprite, 0);
	
	setContentSize(sprite->getContentSize()); // Estupido cocos2d...
//	sprite->setFlipX(isSecondPlayer);
	if (isSecondPlayer) {
		setScaleX(-1);
	}
}
