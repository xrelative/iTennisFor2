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
    
	Jugador *j1;
	Jugador *j2;
	Bola *bola;
	float piso;
    int scorePlayer1;
    int scorePlayer2;
	int set;
    CCLabelTTF *scoreLabelPlayer1;
    CCLabelTTF *scoreLabelPlayer2;
    
	void back(CCObject* pSender);
    void golpearJ1(GolpeEvent* golpe);
	void golpearJ2(GolpeEvent* golpe);
	void golpear(int id, GolpeEvent* golpe);
    void ResultadoJugada(ScoreMensage* mensage);
    void resetGame();
    
    CREATE_FUNC(Jugar);
};

#endif /* defined(__cocos2dxtest1__JugarScene__) */
