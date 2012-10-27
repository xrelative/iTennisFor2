//
//  JugarScene.h
//  cocos2dxtest1
//
//  Created by Ignacio Gómez Espinoza on 13-10-12.
//
//

#ifndef __cocos2dxtest1__JugarScene__
#define __cocos2dxtest1__JugarScene__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Jugador.h"
#include "Bola.h"

class Jugar : public cocos2d::CCLayer
{
public:
	virtual bool init();
	static cocos2d::CCScene* scene();
	
	void back(CCObject* pSender);
	
	// variables de juego
	Jugador *j1;
	Jugador *j2;

	void resetGame();
	
	Bola* bola;
	float piso;
	
	// preprocessor macro for "static create()" constructor ( node() deprecated )
	CREATE_FUNC(Jugar);
	
	void golpearJ1 (GolpeEvent* golpe);
	void golpearJ2 (GolpeEvent* golpe);
	void golpear (int id, GolpeEvent* golpe);
};

#endif /* defined(__cocos2dxtest1__JugarScene__) */
