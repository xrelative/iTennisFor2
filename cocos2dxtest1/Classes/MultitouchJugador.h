//
//  Multitouch jugador.h
//  Test Multitouch
//
//  Created by Cristián Arenas Ulloa on 10/17/12.
//
//

#ifndef __Test_Multitouch__MultitouchJugador__
#define __Test_Multitouch__MultitouchJugador__

#include "touch_dispatcher/CCTouchDelegateProtocol.h"
#include "CCTouch.h"
USING_NS_CC;

class MultitouchJugador : public CCObject, public CCTouchDelegate
{
	int ID;
	CCRect area;
	
	// Para el cálculo del efecto
	float tapTime;
	float lastTime;
	int   yPosition;
	float yVelocity;
	float sensibilidadCarga;
	float sensibilidadDescarga;
	
	// Para el cálculo de la fuerza
	float fuerza;
	float potenciaMinima;
	float potenciaMaxima;
	
	// Para evitar más de un toque en la misma area
	bool isTouching;
	
public:
	MultitouchJugador(int id, float kcarga, float kdescarga, float fuerza, float potenciaMinima, float potenciaMaxima, CCRect area);
private:
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
	void calcularVelocidad(float newPos);
};

float getTimeTick();
#endif /* defined(__Test_Multitouch__MultitouchJugador__) */
