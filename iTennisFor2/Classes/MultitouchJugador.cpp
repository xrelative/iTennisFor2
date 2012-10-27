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

MultitouchJugador::MultitouchJugador(float kcarga, float kdescarga, float fuerza, float potenciaMinima, float potenciaMaxima, CCRect area, CCObject* pselectorGolpeTarget, SEL_CallFuncO selectorGolpe, CCObject* pselectorCargaTarget, SEL_CallFuncO selectorCarga)
: fuerza(fuerza),
//  ID(id), // Solo para debugging.
  potenciaMinima(potenciaMinima),
  potenciaMaxima(potenciaMaxima),
  area(area)
{	
	/* ¿ Por qué kdescarga * kcarga ?
	 *  La constante de descarga está multiplicada por la
	 * de carga, para desacoplar el valor de esta constante.
	 * en caso contrario, un cambio en sensibilidadCarga
	 * cambiaría también el tiempo de descarga!
	 */
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	sensibilidadCarga    = kcarga / size.height;
	sensibilidadDescarga = kdescarga * sensibilidadCarga;
	
	isTouching = 0;
	
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	callbackGolpe = CCCallFuncO::create(pselectorGolpeTarget, selectorGolpe, &resultadoGolpe);
	callbackGolpe->retain(); // No estoy totalmente seguro por qué
	
	callbackCarga = CCCallFuncO::create(pselectorCargaTarget, selectorCarga, &resultadoCarga);
	callbackCarga->retain(); // No estoy totalmente seguro por qué

	
	((CCNode*)pselectorGolpeTarget)->addChild(this); // Esto es excesivamente chanta, pero sirve por mientras para probar la nueva función de timing
	schedule(schedule_selector(MultitouchJugador::timing));
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
//		printf("ccTouchBegan %i\t(%4f, %4f)\n", ID, posicion.x, posicion.y);
		
		// Preparar cálculo del efecto
		totaldt = 0;
		     dt = 0;
//		tapTime   = getTimeTick();
//		lastTime  = tapTime;
		yPosition = posicion.y;
		yVelocity = 0;
		
		resultadoCarga.y = yPosition;
		callbackCarga->execute();
		return (isTouching = true);
	}
	return false;
}

#include <algorithm>
#include <math.h>
void MultitouchJugador::calcularVelocidad(float newPos)
{
//	float newTime, deltaT;
//	newTime  = getTimeTick();
//	deltaT   = newTime - lastTime;
//	lastTime = newTime;
	float deltaT = getDeltaT();
	if (deltaT == 0) return;
	
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
//	printf("ccTouchMoved %i\t con velocidad: %f\n", ID, yVelocity);
}

void MultitouchJugador::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	isTouching = false;
	CCPoint posicion = pTouch->getLocation();
	calcularVelocidad(posicion.y);
	
//	float ahora, power;
//	ahora = getTimeTick();
	float power;
	getDeltaT(); // actualiza totaldt
	power  = potenciaMinima + (totaldt) * fuerza;
	power  = MIN(power, potenciaMaxima);
	
//	printf("ccTouchEnded %i\t con velocidad: %f; y potencia: %f:\n", ID, yVelocity, power);
	resultadoGolpe.spin  = yVelocity;
	resultadoGolpe.power = power;
	callbackGolpe->execute();
}

void MultitouchJugador::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
	isTouching = false;
	printf("ccTouchCancelled\n"); //%i\n", ID);
}
//
//#include <sys/time.h>
//float getTimeTick() {
//	timeval time;
//	gettimeofday(&time, NULL);
//	unsigned long millisecs = (time.tv_sec * 1000.0) + (time.tv_usec / 1000.0);
//	return (float) millisecs;
//}

void MultitouchJugador::timing(float mdt)
{
	dt += mdt*1000; // Trabajamos en segundos
}

float MultitouchJugador::getDeltaT ()
{
	float deltaT = dt;
	totaldt += deltaT;
	dt = 0;
	return deltaT;
}
