//
//  Jugador.cpp
//  cocos2dxtest1
//
//  Created by Cristián Arenas Ulloa on 10/23/12.
//
//

#include "Jugador.h"
Jugador::Jugador (bool isSecondPlayer, CCRect area, CCObject* pSelectorTarget, SEL_CallFuncO selector, string staySpriteName, string jumpSpriteName)
: multitouch(100.0, 0.01, 0.005, 4.5, 8.0, area, pSelectorTarget, selector, this, NULL),
  isSecondPlayer(isSecondPlayer),
  staySpriteName(staySpriteName),
  jumpSpriteName(jumpSpriteName)
{
//	this->schedule(schedule_selector(Jugador::update));
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("sprites.plist");
    CCSpriteBatchNode *batchNode = CCSpriteBatchNode::create("sprites.pvr.ccz");
    this->addChild(batchNode);

	sprite = CCSprite::createWithSpriteFrameName(staySpriteName.c_str());

    sprite->setPosition(CCPointZero);
    batchNode->addChild(sprite, 0);
	
	setContentSize(sprite->getContentSize()); // Estupido cocos2d...
//	sprite->setFlipX(isSecondPlayer);
}


CCRect const Jugador::getHitArea ()
{
	return multitouch.area;
}

void Jugador::Jump(CargaEvent *event)
{    
	CCSpriteFrame *spriteFrameJump = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(jumpSpriteName.c_str());
	sprite->setDisplayFrame(spriteFrameJump);
//    else
//        spriteFrameJump = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("jump1.png");
//    if(event->y > 30 + sprite->getContentSize().height/2) {
//        CCFiniteTimeAction *actionMove = CCMoveTo::actionWithDuration((float)0.3f, ccp(0, event->y-30-sprite->getContentSize().height/2));
//        sprite->runAction(CCSequence::actions(actionMove, NULL, NULL));
//    }
//    else {
//        CCFiniteTimeAction *actionMove = CCMoveTo::actionWithDuration((float)0.3f, ccp(0, 0));
//        sprite->runAction(CCSequence::actions(actionMove, NULL, NULL));
//    }
//	CCActionInterval *intervalo = CCActionInterval::create(1.000);
//	CCEaseIn *ease = CCEaseIn::create(intervalo, 2.0);
//	this->runAction(ease);
	
//	id action = [CCMoveTo actionWithDuration:2 position:ccp(100,100)];
//	id ease = [CCEaseIn actionWithAction:action rate:2];
//	[sprite runAction: ease];
	
//    if(event->y>30+sprite->getContentSize().height/2){
//        CCFiniteTimeAction* actionMove =
//        CCMoveTo::actionWithDuration( (float)0.3f,
//                                     ccp(0, event->y-30-sprite->getContentSize().height/2) );
//        
//        sprite->runAction( CCSequence::actions(actionMove,
//                                               NULL, NULL) );
//    }
//    else{
//        CCFiniteTimeAction* actionMove =
//        CCMoveTo::actionWithDuration( (float)0.3f,
//                                     ccp(0, 0) );
//        
//        sprite->runAction( CCSequence::actions(actionMove,
//                                               NULL, NULL) );
//    }
}

void Jugador::Fall()
{
    CCSpriteFrame *spriteFrameJump = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(staySpriteName.c_str());
    sprite->setDisplayFrame(spriteFrameJump);
//    CCFiniteTimeAction* actionMove = CCMoveTo::actionWithDuration((float)0.3f, ccp(0, 0));
//    sprite->runAction(CCSequence::actions(actionMove, NULL, NULL));
}

/* iniciando golpe */

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


/* golpe */

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
