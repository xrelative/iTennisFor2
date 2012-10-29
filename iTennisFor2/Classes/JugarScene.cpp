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

CCScene* Jugar::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();
	
	// 'layer' is an autorelease object
	Jugar *layer = Jugar::create();
	
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
        scoreLabelPlayer1 = CCLabelTTF::create("0", "Arial", 20);
        scoreLabelPlayer2 = CCLabelTTF::create("0", "Arial", 20);
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
		int ancho     = winSize.width/5; // 20% del ancho
		CCRect area   = CCRectMake(0, 0, ancho, winSize.height);
		j1            = new Jugador(area, this, callfuncO_selector(Jugar::golpearJ1), "stay1.png", "jump1.png");
		area.origin.x = winSize.width - ancho;
		j2            = new Jugador(area, this, callfuncO_selector(Jugar::golpearJ2), "stay2.png", "jump2.png");
		
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

void Jugar::resetGame()
{
    bola->resetBall(1);
//	if(scorePlayer1 < scorePlayer2)
//        bola->resetBall(1);
//    
//    else
//        bola->resetBall(2);
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
	
	if (pelotaEsGolpeable && area.containsPoint(posBola)) {
		float velx = golpe->power * 60; // = la fuerza de este jugador
		b.velocidad.x = velx * direccion;
		float vely = 500; //algun valor para que caiga dentro de la cancha
		b.velocidad.y = vely;
		b.spin = golpe->spin * direccion; // El spin depende de donde se le pega

		SimpleAudioEngine::sharedEngine()->playEffect("tennisserve.wav");

		int piso = 70;
		int alturaRaqueta = 30;
		if (posBola.y > piso + alturaRaqueta + 5) { // piso + altura raqueta + margen salto minimo
			CCPoint p = j.getPosition();
			CCCallFunc *animacionSalto = CCCallFunc::create(&j, callfunc_selector(Jugador::Jump));
			CCActionInterval* subir    =   CCMoveTo::create(0.200f, ccp(p.x, posBola.y + alturaRaqueta));
			CCActionInterval* bajar    =   CCMoveTo::create(0.300f, ccp(p.x, p.y));
			CCFiniteTimeAction* saltar =  CCEaseOut::create(subir, 2.0);
			CCFiniteTimeAction* caer   =   CCEaseIn::create(bajar, 2.0);
			CCCallFunc *animacionPiso  = CCCallFunc::create(&j, callfunc_selector(Jugador::Fall));
			CCFiniteTimeAction* accion = CCSequence::create(animacionSalto, saltar, caer, animacionPiso, NULL);
			j.runAction(accion);
		}
	}
	printf("Jugador #%i golpea con Spin: %f y Power: %f\n", id, golpe->spin, golpe->power);
}

void Jugar::ResultadoJugada(ScoreMensage *mensage)
{
    if(mensage->ScoreResult == 1) {
        scorePlayer1++;
        switch (scorePlayer1) {
            case 1:
                SimpleAudioEngine::sharedEngine()->playEffect("applause4.wav");
                point->showPoint(1);
                scoreLabelPlayer1->setString("15");
                resetGame();
                break;
            case 2:
                SimpleAudioEngine::sharedEngine()->playEffect("applause4.wav");
                point->showPoint(1);
                scoreLabelPlayer1->setString("30");
                resetGame();
                break;
            case 3:
                SimpleAudioEngine::sharedEngine()->playEffect("applause4.wav");
                point->showPoint(1);
                scoreLabelPlayer1->setString("40");
                resetGame();
                break;
            case 4:
                SimpleAudioEngine::sharedEngine()->playEffect("applause4.wav");
                win->showRestartMenu(1);
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
                resetGame();
                break;
            case 2:
                SimpleAudioEngine::sharedEngine()->playEffect("applause4.wav");
                point->showPoint(2);
                scoreLabelPlayer2->setString("30");
                resetGame();
                break;
            case 3:
                SimpleAudioEngine::sharedEngine()->playEffect("applause4.wav");
                point->showPoint(2);
                scoreLabelPlayer2->setString("40");
                resetGame();
                break;
            case 4:
                SimpleAudioEngine::sharedEngine()->playEffect("applause4.wav");
                win->showRestartMenu(2);
                break;
            default:
                break;
        }
    }
}
