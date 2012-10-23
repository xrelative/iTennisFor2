//
//  Multitouch jugador.cpp
//  Test Multitouch
//
//  Created by Cristián Arenas Ulloa on 10/17/12.
//
//

#include "MultitouchJugador.h"
#include "CCDirector.h"
#include "touch_dispatcher/CCTouchDispatcher.h"

USING_NS_CC;

#include <stdio.h> //Debuggeando con printf, no se formatear con <<, yet

MultitouchJugador::MultitouchJugador(int id, float kcarga, float kdescarga, float x, float y, float width, float height)
{
	ID = id; // Solo para debugging.
	area = CCRectMake(x, y, width, height);
	
	/* ¿ Por qué kdescarga * kcarga ?
	 *  La constante de descarga está multiplicada por la
	 * de carga, para desacoplar el valor de esta constante.
	 * en caso contrario, un cambio en sensibilidadCarga
	 * cambiaría también el tiempo de descarga!
	 */
	sensibilidadCarga    = kcarga;
	sensibilidadDescarga = kdescarga * kcarga;
	
	isTouching = 0;
	
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool MultitouchJugador::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (isTouching) {
		/* Si ya está tocando,
		 * no hay nada más que hacer acá
		 */
		return false;
	}
	CCPoint posicion = pTouch->getLocation();
	if (area.containsPoint(posicion)) {
		printf("ccTouchBegan %i\t(%4f, %4f)\n", ID, posicion.x, posicion.y);
		
		// Preparar cálculo del efecto
//		tapTime   = getTimeTick();
		lastTime  = getTimeTick();
		yPosition = posicion.y;
		yVelocity = 0;
		
		return (isTouching = true);
	}
	return false;
}

#include <algorithm>
#include <math.h>
void MultitouchJugador::calcularVelocidad(float newPos)
{
	float newTime, deltaT;
	newTime  = getTimeTick();
	deltaT   = newTime - lastTime;
	if (deltaT == 0) return;
	lastTime = newTime;
	
	float deltaPos;
	deltaPos  = newPos - yPosition;
	yPosition = newPos;
	
	float carga, descarga;
	carga     = sensibilidadCarga    * deltaPos / deltaT;
	descarga  = sensibilidadDescarga * deltaT;
	
	float newVelocity = yVelocity + carga;
	if (fabs(descarga) >= fabs(newVelocity)) {
		yVelocity = 0;
	} else {
		descarga *= newVelocity >= 0 ? 1 : -1;
		yVelocity = newVelocity - descarga;
	}
}

void MultitouchJugador::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint posicion = pTouch->getLocation();
	calcularVelocidad(posicion.y);
	printf("ccTouchMoved %i\t con velocidad: %f\n", ID, yVelocity);
}

void MultitouchJugador::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	isTouching = false;
	CCPoint posicion = pTouch->getLocation();
	calcularVelocidad(posicion.y);
	
	printf("ccTouchEnded %i\t con velocidad: %f\n", ID, yVelocity);
}

void MultitouchJugador::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
	isTouching = false;
	printf("ccTouchCancelled %i\n", ID);
}

#include <sys/time.h>
float getTimeTick() {
	timeval time;
	gettimeofday(&time, NULL);
	unsigned long millisecs = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (float) millisecs;
}
