//
//  Bola.cpp
//  cocos2dxtest1
//
//  Created by Cristián Arenas Ulloa on 10/23/12.
//
//

#include "Bola.h"

Bola::Bola (float piso,CCObject* pselectorCargaTarget, SEL_CallFuncO selectorCarga)
: piso(piso),
  gravedad(-1000.0f),
  spin(0),
  coeficienteRestitucion(0.70f) // Sacado de canchas de verdad
{
	schedule(schedule_selector(Bola::update));

    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("sprites.plist");
    CCSpriteBatchNode *batchNode = CCSpriteBatchNode::create("sprites.pvr.ccz");
    this->addChild(batchNode);
    
    sprite = CCSprite::createWithSpriteFrameName("ball1.png");
    sprite->setPosition(ccp(size.width * 0.1, size.height * 0.75));
    batchNode->addChild(sprite, 0);
	//	CC_BREAK_IF(!sprite); //Dejemos que se caiga si esto no funca
    
    
    callbackMensaje = CCCallFuncO::create(pselectorCargaTarget, selectorCarga, &resultadoMensage);
	callbackMensaje->retain(); // No estoy totalmente seguro por qué
}

void Bola::update (float dt)
{
	velocidad.y += gravedad * dt;
	CCPoint posicion = getPosicion();
	
	CCPoint cambio = ccpMult(velocidad, dt);
	posicion = ccpAdd(posicion, cambio);
	
	sprite->setPosition(posicion);
	checkStatus();
}

void Bola::checkStatus()
{
	CCPoint posicion = getPosicion();
	
	if(posicion.y < piso) {
		colisionPiso();
	}
	
	if (posicion.x<0){
//		resetGame(); enviarEvento fuera de la pantalla por la izq
        resultadoMensage.ScoreResult = 2;
        callbackMensaje->execute();
	}
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	if (posicion.x > size.width){
//		resetGame(); enviarEvento fuera de la pantalla por la der
        resultadoMensage.ScoreResult = 1;
        callbackMensaje->execute();

	}
    
    
   
    
    
    
//	if (abs(posicion.x-getContentSize().width/2) < anchoRed){
//		if (posicion.y<160){
//			if(posicion.y<140){
//				resetGame(); //choca con red
//
//			}else{ // rebota por arriba
//				velocidad.x=velocidad.x/2;
//				velocidad.y=100;
//				if (velocidad.x>0){
//					if(velocidad.x<5){
//						velocidad.x=5;
//					}
//				}
//				if (velocidad.x<0){
//					if(velocidad.x>-5){
//						velocidad.x=-5;
//					}
//				}
//			}
//		}
//	}
}

#include <cmath>
#include <algorithm>
using namespace std;
void Bola::colisionPiso()
{
	CCPoint posicion = getPosicion();

	posicion.y = piso;
	
	float direccionX = velocidad.x>=0 ? 1.0 : -1.0;
//	velocidad = ccpRotateByAngle(velocidad, CCPointZero, spin);
	float fuerzaSpin = spin*200.0; // momento rotacional -> lineal
	float velocidadMinima =  200.0;
	float velocidadMaxima = 1000.0;
	
	if (velocidad.x != 0) { // Así se mantiene rebotando antes del primer golpe.
		velocidad.x = direccionX * max(velocidadMinima, min((fabs(velocidad.x)+fuerzaSpin), velocidadMaxima));
		velocidad.y *= -coeficienteRestitucion;
	} else {
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		velocidad.y = size.height;
	}
	spin *= 0.1; // perdida de energia por roce
	
	sprite->setPosition(posicion);
}

CCPoint Bola::getPosicion () {
	return sprite->getPosition();
}
