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

#include <string>
using namespace std;

class Jugador : public CCNode {
	MultitouchJugador multitouch;
public:
	string staySpriteName;
	string jumpSpriteName;
	CCSprite* sprite;
	Jugador (CCRect area, CCObject* pSelectorTarget, SEL_CallFuncO selector, string staySpriteName, string jumpSpriteName);
	const CCRect getHitArea ();
    void Jump(CargaEvent *event);
    void Fall();
private:
//	void update (float dt);
};

#endif /* defined(__cocos2dxtest1__Jugador__) */
