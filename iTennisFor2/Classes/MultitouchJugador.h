//
//  Multitouch jugador.h
//  Test Multitouch
//
//  Created by Cristián Arenas Ulloa on 10/17/12.
//
//

#ifndef __Test_Multitouch__MultitouchJugador__
#define __Test_Multitouch__MultitouchJugador__

#include "cocos2d.h"
//#include "touch_dispatcher/CCTouchDelegateProtocol.h"
//#include "CCTouch.h"
USING_NS_CC;

class GolpeEvent : public CCObject {
public:
	float spin;
	float power;
};

class CargaEvent : public CCObject {
public:
	float y;
};

class MultitouchJugador : public CCNode/*CCObject*/, public CCTouchDelegate
{
//	int ID;
	
	// Para el cálculo del efecto
	float dt;
	float totaldt;
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
	
	// Para el sistema de eventos
	GolpeEvent resultadoGolpe;
	CCCallFuncO *callbackGolpe;
	CargaEvent resultadoCarga;
	CCCallFuncO *callbackCarga;
	
public:
	MultitouchJugador(float kcarga, float kdescarga, float fuerza, float potenciaMinima, float potenciaMaxima, CCRect area, CCObject* pselectorGolpeTarget, SEL_CallFuncO selectorGolpe, CCObject* pselectorCargaTarget, SEL_CallFuncO selectorCarga);
	CCRect area;
private:
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
	void calcularVelocidad(float newPos);
	void timing (float dt);
	float getDeltaT ();
};

float getTimeTick();
#endif /* defined(__Test_Multitouch__MultitouchJugador__) */
