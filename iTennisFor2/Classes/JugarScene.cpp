//
//  JugarScene.cpp
//  cocos2dxtest1
//
//  Created by Ignacio Gómez Espinoza on 13-10-12.
//
//

#include "JugarScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
Jugar* Jugar::create(int players)
{
	Jugar *pRet = new Jugar();
	if (pRet) {
		pRet->players = players;
	}
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
CCScene* Jugar::scene(int players)
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();
	
	// 'layer' is an autorelease object
	Jugar *layer = Jugar::create(players);
	if (players == 1) {
		layer->scheduleUpdate();
	}
	
	// add layer as a child to scene
	scene->addChild(layer);
    
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Jugar::init()
{
	bool bRet = false;
	do
	{
		if ( !CCLayer::init() )
        {
            return false;
        }
		
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("background.plist");
        CCSpriteBatchNode *batchNodeBackground = CCSpriteBatchNode::create("background.pvr.ccz");
        this->addChild(batchNodeBackground, 0);
        
        CCSprite *background = CCSprite::createWithSpriteFrameName("backgroundPlay.png");
		background->setPosition(ccp(winSize.width/2, winSize.height/2));
		batchNodeBackground->addChild(background, 0);
        
        CCLabelTTF *labelPlayer1 = CCLabelTTF::create("Jugador 1", "aftershockdebris.ttf", 20);
        CCLabelTTF *labelPlayer2 = CCLabelTTF::create("Jugador 2", "aftershockdebris.ttf", 20);
        scoreLabelPlayer1 = CCLabelTTF::create("0", "aftershockdebris.ttf", 20);
        scoreLabelPlayer2 = CCLabelTTF::create("0", "aftershockdebris.ttf", 20);
        labelPlayer1->setColor(ccc3(0, 0, 0));
        labelPlayer2->setColor(ccc3(0, 0, 0));
        scoreLabelPlayer1->setColor(ccc3(0, 0, 0));
        scoreLabelPlayer2->setColor(ccc3(0, 0, 0));
        labelPlayer1->setPosition(ccp(winSize.width*0.4, winSize.height*0.9));
        labelPlayer2->setPosition(ccp(winSize.width*0.4, winSize.height*0.8));
        scoreLabelPlayer1->setPosition(ccp(winSize.width*0.6, winSize.height*0.9));
        scoreLabelPlayer2->setPosition(ccp(winSize.width*0.6, winSize.height*0.8));
        this->addChild(labelPlayer1, 1);
        this->addChild(labelPlayer2, 1);
        this->addChild(scoreLabelPlayer1, 1);
        this->addChild(scoreLabelPlayer2, 1);
        
		piso = 40;
		
		/* Creación y ubicación de jugadores */
		int anchoClick;
		CCRect clickArea;
		int ancho     = winSize.width/5; // 20% del ancho
		int inicio    = winSize.width/10;// 10% del ancho
		anchoClick    = winSize.width/3;
		CCRect area   = CCRectMake(inicio, 0, ancho, winSize.height);
		clickArea     = CCRectMake(0, 0, anchoClick, winSize.height);
		j1            = new Jugador(area, clickArea, this, callfuncO_selector(Jugar::golpearJ1), "stay1.png", "jump1.png", "hit11.png", "hit13.png", "hit14.png");
		area.origin.x = winSize.width - ancho - inicio;
		clickArea.origin.x = winSize.width - anchoClick;
		if (players == 1) {
			area.origin.x -= inicio; // le pegamos antes
			clickArea = CCRectMake(winSize.width*2, winSize.height*2, 0, 0); // afuera de la pantalla!
		}
		j2            = new Jugador(area, clickArea, this, callfuncO_selector(Jugar::golpearJ2), "stay2.png", "jump2.png", "hit21.png", "hit23.png", "hit24.png");
		
		this->addChild(j1, 1);
		this->addChild(j2, 1);
		
		CCSize  spriteJugador   = j1->getContentSize();
		CCPoint posicionJugador = ccp(spriteJugador.width/2.0, spriteJugador.height/2.0 + piso-10);
		j1->setPosition(posicionJugador);
		posicionJugador.x = winSize.width - posicionJugador.x;
		j2->setPosition(posicionJugador);
		
		setTouchEnabled(true);
        
        set = 1;
        scorePlayer1 = 0;
        scorePlayer2 = 0;
		
		bRet = true;
		
		bola = new Bola(piso,this, callfuncO_selector(Jugar::ResultadoJugada));
		this->addChild(bola, 1);
        
        point = Point::create();
        this->addChild(point, 2);
        
        win = Win::create();
        this->addChild(win, 3);
	} while (0);
	
	return bRet;
}

void Jugar::update(float dt)
{
	static float countdown = 0;
	if (players > 1) {
		return;
	}
	Bola    &b    = *bola;
	Jugador &j    = *j2;
	CCRect  area    = j.getHitArea();
	CCPoint posBola = b.getPosicion();
	
	static GolpeEvent golpeImaginario;
	golpeImaginario.power = 7;
	golpeImaginario.spin  = -2;
	
	if (countdown > 0) {
		countdown -= dt;
		return;
	}
	if (area.containsPoint(posBola)) {
		golpearJ2(&golpeImaginario);
		countdown = 2.0f;
	}
}

void Jugar::resetGame()
{
//    bola->resetBall(1);
	if(scorePlayer1 < scorePlayer2)
		bola->resetBall(1);
	else
		bola->resetBall(2);
}

#include <stdio.h>
void Jugar::golpearJ1 (GolpeEvent* golpe)
{
	golpear(1, golpe);
}

void Jugar::golpearJ2 (GolpeEvent* golpe)
{
	golpear(2, golpe);
}

void Jugar::golpear (int id, GolpeEvent* golpe)
{
	Bola    &b    = *bola;
	Jugador &j    = id == 1 ? *j1 : *j2;
	int direccion = id == 1 ?   1 :  -1;
	int dirbola = b.velocidad.x == 0 ? 0 : b.velocidad.x > 0 ? 1 :  -1;
	bool pelotaEsGolpeable = (direccion == 0) || (direccion != dirbola);
	
	CCRect  area    = j.getHitArea();
	CCPoint posBola = b.getPosicion();
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();
//	float posicionBolaPorcentual = posBola.x/size.width;
//	float distanciaRestantePorcentual = direccion * (0.50f - posicionBolaPorcentual);
//	pelotaEsGolpeable &= distanciaRestantePorcentual > 0.05;
//	
	pelotaEsGolpeable &= j.isHitting == false;
	
	if (!pelotaEsGolpeable) {// && area.containsPoint(posBola)) {
		return;
	}
	j.isHitting = true;
//		int piso = 70;
	int alturaRaqueta = 40;
	
	float tDeGolpe = (b.t + 0.3);
	float t = fmodf(tDeGolpe, b.t1); // tiempo desde el ultimo rebote
	float estimacionAlturaPelota = b.flr+t*(b.vy+t*b.a*0.5);
				
	JugadorGolpeaEvent* jg = new JugadorGolpeaEvent(golpe, j, id, b);
	
	CCPoint p = j.getPosition();
	CCCallFunc  *hitAnim1      =  CCCallFunc::create(&j, callfunc_selector(Jugador::hitFrame1));
	CCCallFunc  *hitAnim2      =  CCCallFunc::create(&j, callfunc_selector(Jugador::hitFrame2));
	CCCallFunc  *hitAnim3      =  CCCallFunc::create(&j, callfunc_selector(Jugador::hitFrame3));
	CCDelayTime *delay         = CCDelayTime::create(0.070f);
	CCCallFuncO *empujar       = CCCallFuncO::create(&j, callfuncO_selector(Jugar::empujarPelota), jg);
	
	CCCallFunc *animacionSalto = CCCallFunc::create(&j, callfunc_selector(Jugador::Jump));
	
	CCActionInterval* subir    =   CCMoveTo::create(0.160f, ccp(p.x, estimacionAlturaPelota + alturaRaqueta));
	CCActionInterval* bajar    =   CCMoveTo::create(0.200f, ccp(p.x, p.y));
	CCFiniteTimeAction* saltar =  CCEaseOut::create(subir, 2.0);
	CCFiniteTimeAction* caer   =   CCEaseIn::create(bajar, 2.0);
	CCCallFunc *animacionPiso  = CCCallFunc::create(&j, callfunc_selector(Jugador::Fall));
	
	CCFiniteTimeAction* accion;
	if (estimacionAlturaPelota > piso + alturaRaqueta + 5) { // piso + altura raqueta + margen salto minimo
		accion = CCSequence::create(animacionSalto,
					    saltar,
					    hitAnim1, delay,
					    hitAnim2, delay,
					    empujar,
					    hitAnim3, delay,
					    caer,
					    animacionPiso,
					    NULL);
	} else {
		accion = CCSequence::create(delay, delay,
					    hitAnim1, delay,
					    hitAnim2, delay,
					    empujar,
					    hitAnim3, delay,
					    animacionPiso,
					    NULL);
	}
	j.runAction(accion);
	//printf("Jugador #%i golpea con Spin: %f y Power: %f\n", id, golpe->spin, golpe->power);
}

void Jugar::empujarPelota(JugadorGolpeaEvent* jg) {
	
	Bola       & b     = jg->bola;
	Jugador    & j     = jg->jugador;
	GolpeEvent * golpe = jg->golpe;
	int          id    = jg->id;
	
	int direccion = id == 1 ?   1 :  -1;
	int dirbola = b.vx == 0 ? 0 : b.vx > 0 ? 1 :  -1;
	bool pelotaEsGolpeable = (direccion == 0) || (direccion != dirbola);
	
	CCRect  area    = j.getHitArea();
	CCPoint posBola = b.getPosicion();
	
	if (pelotaEsGolpeable && area.containsPoint(posBola)) {
		b.t1 *= 0.95;
		
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		b.a = -3*size.height/(b.t1 * b.t1);
		float distancia = size.width*(0.05 +(golpe->power-5.0)/3.0 * 0.3);
//		fminf(size.width*0.4, fmaxf(golpe->power*10, size.width* 0.03));
		b.trg = size.width/2 + direccion * distancia;
		b.dy  = posBola.y - b.flr;
		b.xo = posBola.x;
		b.yo = posBola.y;
		b.golpear();
		
//		b.velocidad.x = velx * direccion;
//		float vely = 500; //algun valor para que caiga dentro de la cancha
//		b.velocidad.y = vely;
		float bd = (b.trg - b.xo)*direccion;
		float spin = size.width * 0.3 * golpe->spin; // El spin
		spin = fmaxf(size.width * 0.90, spin+bd*2)-bd*2;
		spin = fmaxf(size.width * 0.05, spin+bd)-bd;
		b.spin = spin * direccion; // El spin depende de donde se le pega
		
		SimpleAudioEngine::sharedEngine()->playEffect("tennisserve.wav");
	}
}

void Jugar::ResultadoJugada(ScoreMensage *mensage)
{
    //printf("Punto para%d\n",mensage->ScoreResult);
    
    if(mensage->ScoreResult==1){
        scorePlayer1++;
        switch (scorePlayer1) {
            case 1:
                SimpleAudioEngine::sharedEngine()->playEffect("applause4.wav");
                point->showPoint(1);
                scoreLabelPlayer1->setString("15");
                this->scheduleOnce(schedule_selector(Jugar::resetGame), 1.5);
                break;
            case 2:
                SimpleAudioEngine::sharedEngine()->playEffect("applause4.wav");
                point->showPoint(1);
                scoreLabelPlayer1->setString("30");
                this->scheduleOnce(schedule_selector(Jugar::resetGame), 1.5);
                break;
            case 3:
                SimpleAudioEngine::sharedEngine()->playEffect("applause4.wav");
                point->showPoint(1);
                scoreLabelPlayer1->setString("40");
                this->scheduleOnce(schedule_selector(Jugar::resetGame), 1.5);
                break;
            case 4:
                SimpleAudioEngine::sharedEngine()->playEffect("applause4.wav");
                win->showRestartMenu(1, players);
                break;
            default:
                break;
        }
    }
    else if(mensage->ScoreResult == 2) {
        scorePlayer2++;
        switch (scorePlayer2) {
            case 1:
                SimpleAudioEngine::sharedEngine()->playEffect("applause4.wav");
                point->showPoint(2);
                scoreLabelPlayer2->setString("15");
                this->scheduleOnce(schedule_selector(Jugar::resetGame), 1.5);
                break;
            case 2:
                SimpleAudioEngine::sharedEngine()->playEffect("applause4.wav");
                point->showPoint(2);
                scoreLabelPlayer2->setString("30");
                this->scheduleOnce(schedule_selector(Jugar::resetGame), 1.5);
                break;
            case 3:
                SimpleAudioEngine::sharedEngine()->playEffect("applause4.wav");
                point->showPoint(2);
                scoreLabelPlayer2->setString("40");
                this->scheduleOnce(schedule_selector(Jugar::resetGame), 1.5);
                break;
            case 4:
                SimpleAudioEngine::sharedEngine()->playEffect("applause4.wav");
                win->showRestartMenu(2, players);
                break;
            default:
                break;
        }
    }
}
