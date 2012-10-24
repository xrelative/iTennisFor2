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
		
		// 2. Add a label shows "Hello World".
		
		// Create a label and initialize with string "Hello World".
		CCLabelTTF* pLabel = CCLabelTTF::create("Tennis", "Arial", 24);
		CC_BREAK_IF(! pLabel);
		
		// Get window size and place the label upper.
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		pLabel->setPosition(ccp(size.width / 2, size.height - 50));
		
		// Add the label to HelloWorld layer as a child layer.
		addChild(pLabel, 1);
		
		
		//-----------------INIT VAR--------------
		x=0;
		y=0;
		
		xEnd=0;
		yEnd=0;
		
		planeHit1=false;
		planeHit2=false;
		//-----------INIT SPRITES
		
		background = CCSprite::create("maqueta2.png");
		CC_BREAK_IF(!  background);
		
		background->setPosition(ccp(size.width/2, size.height/2));
		
		addChild(background);
		
		/* Creación y ubicación de jugadores */
		int ancho = size.width/5; // 20% del ancho
		CCRect area = CCRectMake(0, 0, ancho, size.height);
		j1 = new Jugador(false, area);
		area.origin.x = size.width - ancho;
		j2 = new Jugador(true , area);
		
		addChild(j1);
		addChild(j2);
		
		CCSize spriteJugador = j1->getContentSize();
		CCPoint posicionJugador = ccp(spriteJugador.width/2, spriteJugador.height/2+floor);
		j1->setPosition(posicionJugador);
		posicionJugador.x = size.width - posicionJugador.x;
		j2->setPosition(posicionJugador);
		
		setTouchEnabled(true);
		schedule( schedule_selector(Jugar::update));
		
		bRet = true;
		
		bola = new Bola();
		addChild(bola);
	} while (0);
	
	
	return bRet;
}

void Jugar::back(CCObject* pSender)
{
	CCDirector::sharedDirector()->popScene();
}

void Jugar::update(float dt){
	
}

void Jugar::beganCharge(CCPoint p, int id) {
//	
//	float fX=p.x;
//	float fY=p.y;
//	
//	if(id==1){
//		if(isChargingPLayer1==false){
//			//player1->setPosition(ccp(player1->getContentSize().width/2, location.y));
//			initX1=fX;
//			initY1=fY;
//			
//			isChargingPLayer1=true;
//			
//			
//			CCFiniteTimeAction* actionMove =
//			CCMoveTo::actionWithDuration( (float)0.3f,
//						     ccp(player1->getContentSize().width/2, p.y) );
//			
//			player1->runAction( CCSequence::actions(actionMove,
//								NULL, NULL) );
//		}
//		
//	}
//	
//	
//	if (id == 2) {
//		if(isChargingPLayer2==false){
//			//player2->setPosition(ccp(getContentSize().width-player1->getContentSize().width/2, location.y));
//			isChargingPLayer2=true;
//			
//			initX2 = fX;
//			initY2 = fY;
//			
//			
//			
//			CCFiniteTimeAction* actionMove =
//			CCMoveTo::actionWithDuration( (float)0.3f,
//						     ccp(getContentSize().width-player2->getContentSize().width/2, p.y) );
//			
//			player2->runAction( CCSequence::actions(actionMove,
//								NULL, NULL) );
//		}
//		
//		
//	}
	
	
}

void Jugar::endedCharge(CCPoint p, int id) {
//	xEnd=p.x;
//	yEnd=p.y;
//	
//	if(id==1){
//		if(isChargingPLayer1==true){
//			//player1->setPosition(ccp(player1->getContentSize().width/2, getContentSize().height/4));
//			isChargingPLayer1=false;
//			
//			endX1=xEnd;
//			endY1=yEnd;
//			
//			
//			CCFiniteTimeAction* actionMove =
//			CCMoveTo::actionWithDuration( (float)0.3f,
//						     ccp(player1->getContentSize().width/2, floor+player1->getContentSize().height/2) );
//			
//			player1->runAction( CCSequence::actions(actionMove,
//								NULL, NULL) );
//			
//			
//			if((posBallx<player1->getContentSize().width)&&(posBallx>0)){
//				if((posBally<(player1->getContentSize().height/2+player1->getPositionY()))&&(posBally>(-player1->getContentSize().height/2+player1->getPositionY()))){
//					//if (speedBallX==0){
//					if((initX1-endX1)*(initX1-endX1)+(initY1-endY1)*(initY1-endY1)>1000){
//						float hipo =sqrt((initX1-endX1)*(initX1-endX1)+(initY1-endY1)*(initY1-endY1));
//						
//						speedBallX=-charge1*(initX1-endX1)/hipo;
//						speedBallY=charge1*(endY1-initY1)/hipo;
//					}
//					else{
//						speedBallX=charge1;
//						speedBallY=speedBallY+100;
//					}
//					
//					
//					//speedBallX=charge1;
//					//speedBallY=speedBallY+100;
//					//}
//				}
//				
//				charge1=0;
//				
//			}
//			
//		}
//		
//	}
//	if (id==2){
//		if(isChargingPLayer2==true){
//			//player2->setPosition(ccp(getContentSize().width-player1->getContentSize().width/2, getContentSize().height/4));
//			isChargingPLayer2=false;
//			
//			endX2=xEnd;
//			endY2=yEnd;
//			
//			
//			CCFiniteTimeAction* actionMove =
//			CCMoveTo::actionWithDuration( (float)0.3f,
//						     ccp(getContentSize().width-player2->getContentSize().width/2, floor+player2->getContentSize().height/2) );
//			
//			player2->runAction( CCSequence::actions(actionMove,
//								NULL, NULL) );
//			
//			
//			if((posBallx>getContentSize().width-player2->getContentSize().width)&&(posBallx<getContentSize().width)){
//				if((posBally<(player2->getContentSize().height/2+player2->getPositionY()))&&(posBally>(-player2->getContentSize().height/2+player2->getPositionY()))){
//					//if (speedBallX==0){
//					if((initX2-endX2)*(initX2-endX2)+(initY2-endY2)*(initY2-endY2)>1000){
//						float hipo =sqrt((initX2-endX2)*(initX2-endX2)+(initY2-endY2)*(initY2-endY2));
//						
//						speedBallX=-charge2*(initX2-endX2)/hipo;
//						speedBallY=charge2*(endY2-initY2)/hipo;
//					}
//					else{
//						speedBallX=-charge2;
//						speedBallY=speedBallY+100;
//					}
//					//}
//				}
//			}
//			
//			charge2=0;
//		}
//		
//		
//	}
	
}

void Jugar::resetGame(){
//	bola.reset(pos, vel);
	
	planeHit1=false;
	planeHit2=false;
}