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

class Bola : CCSprite {	
	CCSprite* sprite;
	
	CCPoint velocidad;
	float gravedad;
	float piso;
	float coeficienteRestitucion;
	
public:
	Bola ();
private:
	void update (float dt);
	void checkStatus ();
	void colisionPiso ();
};

#endif /* defined(__cocos2dxtest1__Bola__) */
