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
    
    CCSpriteFrame *bola1 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ball1.png");
    CCSpriteFrame *bola2 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ball2.png");
    CCSpriteFrame *bola3 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ball3.png");
    CCSpriteFrame *bola4 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ball4.png");
    CCArray *arraySpriteFrames = CCArray::create(bola1, bola2, bola3, bola4, NULL);
    CCAnimation * anim = CCAnimation::createWithSpriteFrames(arraySpriteFrames);
//    CCAnimation *anim = CCAnimation::create();
    anim->setDelayPerUnit(0.0);
    anim->setLoops(INFINITY);
//    anim->addSpriteFrame(bola1);
//    anim->addSpriteFrame(bola2);
//    anim->addSpriteFrame(bola3);
//    anim->addSpriteFrame(bola4);
    CCAnimate *theAnim = CCAnimate::create(anim);
    sprite = CCSprite::createWithSpriteFrameName("ball1.png");
    sprite->setPosition(ccp(size.width * 0.1, size.height * 0.75));
    sprite->runAction(CCRepeatForever::create(theAnim));
    batchNode->addChild(sprite, 0);
    
    LastFloorColision=0;
    
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

void Bola::resetBall(int p){
    if(p==1){
        CCPoint posicion = getPosicion();
        //posicion.x=size.width * 0.1;
        //posi
        velocidad.x=0;
        velocidad.y=0;
        sprite->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width*0.1, CCDirector::sharedDirector()->getWinSize().height * 0.50));
        
    }else{
        velocidad.x=0;
        velocidad.y=0;
        sprite->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width*0.9, CCDirector::sharedDirector()->getWinSize().height * 0.50));
    }
}


void Bola::checkStatus()
{
	CCPoint posicion = getPosicion();
	
	if(posicion.y < piso) {
		colisionPiso();
	}
	
	if (posicion.x<0){
//		resetGame(); enviarEvento fuera de la pantalla por la izq
        if(LastFloorColision==1){
            resultadoMensage.ScoreResult = 2;
            callbackMensaje->execute();
        }else{
            resultadoMensage.ScoreResult = 1;
            callbackMensaje->execute();
        }
	}
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	if (posicion.x > size.width){
//		resetGame(); enviarEvento fuera de la pantalla por la der


        if(LastFloorColision==2){
            resultadoMensage.ScoreResult = 1;
            callbackMensaje->execute();
        }else{
            resultadoMensage.ScoreResult = 2;
            callbackMensaje->execute();
        }
        
        
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
	
    if(posicion.x>CCDirector::sharedDirector()->getWinSize().width/2){
        LastFloorColision=2;
    }else{
        LastFloorColision=1;
    }
    
    
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
