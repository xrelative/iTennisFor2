//
//  WinScene.cpp
//  iTennisFor2
//
//  Created by Ignacio Gómez Espinoza on 28-10-12.
//
//

#include "WinScene.h"
#include "MenuScene.h"
#include "JugarScene.h"

USING_NS_CC;

void Win::showRestartMenu(int player)
{    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    const char *message;
    if (player == 1) {
        message = "Jugador 1 ha ganado!";
    }
    else if (player == 2) {
        message = "Jugador 2 ha ganado!";
    }
    
    CCLabelTTF *label = CCLabelTTF::create(message, "YELLOW.TTF", 40.0);
    label->setColor(ccc3(64, 64, 64));
    label->setScale(0.1);
    label->setPosition(ccp(winSize.width/2, winSize.height * 0.7));
    this->addChild(label, 0);
    
    CCMenuItemFont *restartItem = CCMenuItemFont::create("Volver a jugar", this, menu_selector(Win::restartGame));
    restartItem->setColor(ccc3(128, 128, 128));
    restartItem->setScale(0.1);
    restartItem->setPosition(ccp(winSize.width/2, winSize.height * 0.5));
    
    CCMenuItemFont *finishItem = CCMenuItemFont::create("Finalizar", this, menu_selector(Win::finishGame));
    finishItem->setColor(ccc3(128, 128, 128));
    finishItem->setScale(0.1);
    finishItem->setPosition(ccp(winSize.width/2, winSize.height * 0.3));
    
    CCMenu *menu = CCMenu::create(restartItem, finishItem, NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu, 1);
    
    label->runAction(CCScaleTo::create(1.0, 1.0));
    restartItem->runAction(CCScaleTo::create(1.0, 1.0));
    finishItem->runAction(CCScaleTo::create(1.0, 1.0));
}

void Win::restartGame()
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5, Jugar::scene()));
}

void Win::finishGame()
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5, Menu::scene()));
}