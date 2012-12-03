//
//  Bola.h
//  cocos2dxtest1
//
//  Created by Cristián Arenas Ulloa on 10/23/12.
//
//

#ifndef __cocos2dxtest1__Bola__
#define __cocos2dxtest1__Bola__

#include "cocos2d.h"
USING_NS_CC;

class ScoreMensage : public CCObject {
public:
	int ScoreResult;
};

class Bola : public CCNode {
	//todo de nuevo por la rctm:
public:
	float xo ;
	float yo ;
	float vx ;
	float vy ;
	float a  ;
	float dt ;
	float t  ;
	float t1 ;
	float dy ;
	float flr;
	float trg;
	void golpear (float inicio = 0);
	
	//todo de nuevo, fin
public: //<- para hacer código más chanta no más ;)
	float gravedad;
	float piso;
	float coeficienteRestitucion;
	CCSprite* sprite;
	
public:
	bool funcionando;
	float spin;
	CCPoint velocidad;
	Bola (float piso,CCObject* pselectorCargaTarget, SEL_CallFuncO selectorCarga);
	CCPoint getPosicion ();
    void resetBall(int p);

private:
	void update (float dt);
	void checkStatus (float bx, float by);
	void colisionPiso (float bx, float by);
    
    int LastFloorColision;
    
        
    ScoreMensage resultadoMensage;
	CCCallFuncO *callbackMensaje;
};

#endif /* defined(__cocos2dxtest1__Bola__) */
