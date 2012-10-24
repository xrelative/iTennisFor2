//
//  Jugador.h
//  cocos2dxtest1
//
//  Created by Cristián Arenas Ulloa on 10/23/12.
//
//

#ifndef __cocos2dxtest1__Jugador__
#define __cocos2dxtest1__Jugador__

#include "cocos2d.h"
#include "MultitouchJugador.h"
USING_NS_CC;

class Jugador : public CCNode {
	MultitouchJugador multitouch;
	bool isSecondPlayer;
public:
	CCSprite* sprite;
	Jugador (bool isSecondPlayer, CCRect area, CCObject* pSelectorTarget, SEL_CallFuncO selector);
private:
//	void update (float dt);
};

#endif /* defined(__cocos2dxtest1__Jugador__) */
