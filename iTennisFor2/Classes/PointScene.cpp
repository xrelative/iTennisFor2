//
//  PointScene.cpp
//  iTennisFor2
//
//  Created by Ignacio Gómez Espinoza on 28-10-12.
//
//

#include "PointScene.h"
#include "JugarScene.h"

USING_NS_CC;

void Point::showPoint(int player)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    const char *message;
    if (player == 1) {
        message = "Punto para el Jugador 1";
    }
    else if (player == 2) {
        message = "Punto para el Jugador 2";
    }
    
    CCLabelTTF *label = CCLabelTTF::create(message, "YELLOW.TTF", 30.0);
    label->setColor(ccc3(64, 64, 64));
    label->setScale(0.0);
    label->setPosition(ccp(winSize.width/2, winSize.height*0.55));
    this->addChild(label, 0);
    
    CCDelayTime *delay = CCDelayTime::create(0.5);
    CCScaleTo *scaleIn = CCScaleTo::create(0.5, 1.0);
    CCScaleTo *scaleOut = CCScaleTo::create(0.5, 0.0);
    //CCCallFunc *restartBall = CCCallFunc::create(this, callfunc_selector(Jugar::resetGame));
    CCFiniteTimeAction* accion = CCSequence::create(scaleIn, delay, scaleOut, NULL);
    label->runAction(accion);
}