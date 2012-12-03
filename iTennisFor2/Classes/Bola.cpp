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
funcionando(true),
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
	CCAnimate *theAnim = CCAnimate::create(anim);
	sprite = CCSprite::createWithSpriteFrameName("ball1.png");
	sprite->runAction(CCRepeatForever::create(theAnim));
	batchNode->addChild(sprite, 0);
	
	LastFloorColision=0;
	
	callbackMensaje = CCCallFuncO::create(pselectorCargaTarget, selectorCarga, &resultadoMensage);
	callbackMensaje->retain(); // No estoy totalmente seguro por qué
	
	//todo de nuevo por la rctm:
	t1  = 1.4;
	
	a   = -size.height*3;
	
	flr = piso;
	
	//inicio
	xo = size.width  * 0.1;
	yo = flr;
	
	trg = xo;
	golpear(t1*0.5);
	//todo de nuevo, fin
}

void Bola::golpear (float inicio) {
	float dx = trg - xo;
	dy = flr - yo;
	t = inicio;
	
	vx = dx/t1;
	vy = dy/t1 - t1*a*0.5;
}

void Bola::update (float dt) {
	t+=dt;
	
	float bx = xo+t*vx;
	float by = yo+t*(vy+t*a*0.5);
	
	checkStatus(bx, by);
	
	if (t >= t1) {
		float dx = trg - xo;
		
		xo = trg;
		yo = flr;
		
		trg += dx + spin;
		spin = 0;
		
		float exceso = t - t1;
		golpear(exceso);
		
		//recalcular
		bx = xo+t*vx;
		by = yo+t*(vy+t*a*0.5);
	}
	
	sprite->setPosition(ccp(bx, by));
}

void Bola::resetBall(int p){
	t1  = 1.4;
	
	spin = 0;
	funcionando = true;
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCPoint pos;
	if (p==1) {
		xo = size.width*0.1;
	} else {
		xo = size.width*0.9;
	}
	
	yo = flr;
	
	trg = xo;
	golpear(t1*0.5);
}


void Bola::checkStatus (float bx, float by) {
	if (funcionando == false) {
		return;
	}
	
	if (bx < 0){
		funcionando = false;
		//resetGame(); enviarEvento fuera de la pantalla por la izq
		if (LastFloorColision==1) {
			resultadoMensage.ScoreResult = 2;
			callbackMensaje->execute();
		} else {
			resultadoMensage.ScoreResult = 1;
			callbackMensaje->execute();
		}
	}
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	if (bx > size.width){
		funcionando = false;
		//resetGame(); enviarEvento fuera de la pantalla por la der
		if (LastFloorColision==2) {
			resultadoMensage.ScoreResult = 1;
			callbackMensaje->execute();
		} else {
			resultadoMensage.ScoreResult = 2;
			callbackMensaje->execute();
		}
	}
}

#include <cmath>
#include <algorithm>
using namespace std;
void Bola::colisionPiso (float bx, float by) {
//	CCSize size = CCDirector::sharedDirector()->getWinSize();
//	LastFloorColision = (bx > size.width/2) ? 2 : 1;
//	
//	float dx = trg - xo;
//	
//	xo = trg;
//	yo = flr;
//	
//	trg += dx;
//	
//	float exceso = t - t1;
//	golpear();
//
//	float direccionX = velocidad.x>=0 ? 1.0 : -1.0;
//	//	velocidad = ccpRotateByAngle(velocidad, CCPointZero, spin);
//	float fuerzaSpin = spin*200.0; // momento rotacional -> lineal
//	float velocidadMinima =  200.0;
//	float velocidadMaxima = 1000.0;
//	
//	if (velocidad.x != 0) { // Así se mantiene rebotando antes del primer golpe.
//		velocidad.x = direccionX * max(velocidadMinima, min((fabs(velocidad.x+fuerzaSpin)), velocidadMaxima));
//		velocidad.y *= -coeficienteRestitucion;
//	} else {
//		CCSize size = CCDirector::sharedDirector()->getWinSize();
//		velocidad.y = size.height;
//	}
//	spin *= 0.1; // perdida de energia por roce
//
	
}

CCPoint Bola::getPosicion () {
	return sprite->getPosition();
}
