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
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////
		
		CC_BREAK_IF(! CCLayer::init());
		
		//////////////////////////////////////////////////////////////////////////
		// add your codes below...
		//////////////////////////////////////////////////////////////////////////
		
		// 1. Add a menu item with "X" image, which is clicked to quit the program.
		
		// Create a "close" menu item with close icon, it's an auto release object.
		CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
								      "CloseNormal.png",
								      "CloseSelected.png",
								      this,
								      menu_selector(Jugar::back));
		CC_BREAK_IF(! pCloseItem);
		
		// Place the menu item bottom-right conner.
		pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));
		
		// Create a menu with the "close" menu item, it's an auto release object.
		CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
		pMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! pMenu);
		
		addChild(pMenu, 1);
		
        CCSize size = CCDirector::sharedDirector()->getWinSize();
//      CCLabelTTF* pLabel = CCLabelTTF::create("Tennis", "Arial", 24);
//		CC_BREAK_IF(! pLabel);
//		pLabel->setPosition(ccp(size.width / 2, size.height - 50));
//		addChild(pLabel, 1);
		
//-----------INIT SPRITES
		
		background = CCSprite::create("maqueta3.png");
		CC_BREAK_IF(!  background);
		
		background->setPosition(ccp(size.width/2, size.height/2));
		
		addChild(background);
		
		piso = 40;
		/* Creación y ubicación de jugadores */
		int ancho     = size.width/5; // 20% del ancho
		CCRect area   = CCRectMake(0, 0, ancho, size.height);
		j1            = new Jugador(false, area, this, callfuncO_selector(Jugar::golpearJ1));
		area.origin.x = size.width - ancho;
		j2            = new Jugador(true , area, this, callfuncO_selector(Jugar::golpearJ2));
		
		addChild(j1);
		addChild(j2);
		
		CCSize  spriteJugador   = j1->getContentSize();
		CCPoint posicionJugador = ccp(spriteJugador.width/2.0, spriteJugador.height/2.0 + piso);
		j1->setPosition(posicionJugador);
		posicionJugador.x = size.width - posicionJugador.x;
		j2->setPosition(posicionJugador);
		
		setTouchEnabled(true);
//		schedule( schedule_selector(Jugar::update));
		
		bRet = true;
		
		bola = new Bola(piso);
		addChild(bola);
	} while (0);
	
	
	return bRet;
}

void Jugar::back(CCObject* pSender)
{
	CCDirector::sharedDirector()->popScene();
}

void Jugar::resetGame(){
//	bola.reset(pos, vel);
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
	
	CCRect area = j.getHitArea();
	if (area.containsPoint(b.getPosicion())) {
		float velx = golpe->power * 60; // = la fuerza de este jugador
		b.velocidad.x = velx * direccion;
		
		float vely = 500; //algun valor para que caiga dentro de la cancha
		b.velocidad.y = vely;
		
		b.spin = golpe->spin * direccion; // El spin depende de donde se le pega
	}
	printf("Jugador #%i golpea con Spin: %f y Power: %f\n", id, golpe->spin, golpe->power);
}
