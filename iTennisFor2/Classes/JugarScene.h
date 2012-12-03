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
#include "WinScene.h"
#include "PointScene.h"

class JugadorGolpeaEvent : public CCObject {
public:
	GolpeEvent * golpe;
	Jugador    & jugador;
	int          id;
	Bola       & bola;
	JugadorGolpeaEvent (GolpeEvent * golpe,
	                    Jugador    & jugador,
	                    int          id,
	                    Bola       & bola)
	: golpe(golpe),
	  jugador(jugador),
	  id(id),
	  bola(bola)
	{}
};

class Jugar : public cocos2d::CCLayer
{
public:
	virtual bool init();
	int players;
	static cocos2d::CCScene* scene(int players);
    
	Jugador *j1;
	Jugador *j2;
	Bola *bola;
    Win *win;
    Point *point;
	float piso;
	void update (float dt);
	// preprocessor macro for "static create()" constructor ( node() deprecated )
//	CREATE_FUNC(Jugar);
	static Jugar* create(int players);
	
	void golpearJ1 (GolpeEvent* golpe);
	void golpearJ2 (GolpeEvent* golpe);
	void golpear (int id, GolpeEvent* golpe);
	void empujarPelota (JugadorGolpeaEvent* jg);
    
    void ResultadoJugada(ScoreMensage *mensage);
    
    
    int scorePlayer1;
    int scorePlayer2;
	int set;
    CCLabelTTF *scoreLabelPlayer1;
    CCLabelTTF *scoreLabelPlayer2;
    
    void resetGame();
};

#endif /* defined(__cocos2dxtest1__JugarScene__) */
