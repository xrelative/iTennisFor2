//
//  Jugador.cpp
//  cocos2dxtest1
//
//  Created by Cristián Arenas Ulloa on 10/23/12.
//
//

#include "Jugador.h"

Jugador::Jugador (CCRect area, CCObject* pSelectorTarget, SEL_CallFuncO selector, string staySpriteName, string jumpSpriteName)
: multitouch(100.0, 0.01, 0.005, 4.5, 8.0, area, pSelectorTarget, selector, this, NULL),
staySpriteName(staySpriteName),
jumpSpriteName(jumpSpriteName)
{
	//	this->schedule(schedule_selector(Jugador::update));
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("sprites.plist");
	CCSpriteBatchNode *batchNode = CCSpriteBatchNode::create("sprites.pvr.ccz");
	this->addChild(batchNode);
	
	sprite = CCSprite::createWithSpriteFrameName(staySpriteName.c_str());
	
	sprite->setPosition(CCPointZero);
	batchNode->addChild(sprite, 0);
	
	setContentSize(sprite->getContentSize()); // Estupido cocos2d...
						  //	sprite->setFlipX(isSecondPlayer);
}


CCRect const Jugador::getHitArea ()
{
	return multitouch.area;
}

void Jugador::Jump(CargaEvent *event)
{
	CCSpriteFrame *spriteFrameJump = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(jumpSpriteName.c_str());
	sprite->setDisplayFrame(spriteFrameJump);
	
}

void Jugador::Fall()
{
	CCSpriteFrame *spriteFrameJump = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(staySpriteName.c_str());
	sprite->setDisplayFrame(spriteFrameJump);
}
