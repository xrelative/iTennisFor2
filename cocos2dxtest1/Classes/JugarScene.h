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
#include "MultitouchJugador.h"
#include "Bola.h"

class Jugar : public cocos2d::CCLayer
{
public:
	virtual bool init();
	static cocos2d::CCScene* scene();
	
	void back(CCObject* pSender);
	
	// variables de juego
	MultitouchJugador *j1;
	MultitouchJugador *j2;
	
	void update(float dt);
	void beganCharge(CCPoint p, int id);
	void endedCharge(CCPoint p, int id);
	void resetGame();
	
	float initX1;
	float initX2;
	
	float initY1;
	float initY2;
	
	float endX1;
	float endX2;
	
	float endY1;
	float endY2;
	
	GLboolean isChargingPLayer1;
	GLboolean isChargingPLayer2;
	
	float charge1;
	float charge2;
	
	float floor;
	
	float pos1;
	float pos2;
	
	float x;
	float y;
	
	float xEnd;
	float yEnd;
	
	cocos2d::CCSprite* player1;
	cocos2d::CCSprite* player2;
	cocos2d::CCSprite* ball;
	cocos2d::CCSprite* background;
	
	Bola* bola;
	float posBallx,posBally;
	float speedBallX,speedBallY;
	float accBallX,accBallY;
	float g;
	float R;
	
	bool planeHit1;
	bool planeHit2;
	
	// preprocessor macro for "static create()" constructor ( node() deprecated )
	CREATE_FUNC(Jugar);
};

#endif /* defined(__cocos2dxtest1__JugarScene__) */
