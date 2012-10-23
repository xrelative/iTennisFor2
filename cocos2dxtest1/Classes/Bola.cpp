//
//  Bola.cpp
//  cocos2dxtest1
//
//  Created by Cristián Arenas Ulloa on 10/23/12.
//
//

#include "Bola.h"

Bola::Bola (CCScene* escena)
{
	sprite = CCSprite::create("Projectile.png");
	//	CC_BREAK_IF(!ball); //Dejemos que se caiga si esto no funca
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	sprite->setPosition(ccp(200, size.height*3/4));
	escena->addChild(sprite, 0);
}
