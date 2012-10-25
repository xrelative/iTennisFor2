//
//  Bola.cpp
//  cocos2dxtest1
//
//  Created by Cristián Arenas Ulloa on 10/23/12.
//
//

#include "Bola.h"

Bola::Bola (float piso)
: piso(piso),
  gravedad(-1000.0f),
  spin(0),
  coeficienteRestitucion(0.70f) // Sacado de canchas de verdad
{
	schedule(schedule_selector(Bola::update));

	sprite = CCSprite::create("Projectile.png");
	//	CC_BREAK_IF(!sprite); //Dejemos que se caiga si esto no funca
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	sprite->setPosition(ccp(size.width*0.1, size.height*3/4));
	addChild(sprite, 0);
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
	}
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	if (posicion.x > size.width){
//		resetGame(); enviarEvento fuera de la pantalla por la der

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

void Bola::colisionPiso()
{
	CCPoint posicion = getPosicion();

	posicion.y = piso;
	velocidad.y *= -coeficienteRestitucion;
	
//	velocidad = ccpRotateByAngle(velocidad, CCPointZero, spin);
	velocidad.x += spin*200; // momento rotacional -> lineal
	spin *= 0.1; // perdida de energia por roce
	
	sprite->setPosition(posicion);
}

CCPoint Bola::getPosicion () {
	return sprite->getPosition();
}
