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
	string hitSprite1, hitSprite2, hitSprite3;
	CCSprite* sprite;	Jugador (CCRect area, CCRect clickArea, CCObject* pSelectorTarget, SEL_CallFuncO selector, string staySpriteName, string jumpSpriteName, string hitSprite1, string hitSprite2, string hitSprite3);
	const CCRect getHitArea ();
    void Jump(CargaEvent *event);
    void Fall();
	
	//aquí empieza el chanterío… que triste u.u
	void hitFrame1 ();
	void hitFrame2 ();
	void hitFrame3 ();
//	void hitFrame4 ();
	bool isHitting;
	CCRect area;
private:
//	void update (float dt);
};

#endif /* defined(__cocos2dxtest1__Jugador__) */
