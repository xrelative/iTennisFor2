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

void Win::showRestartMenu(int player, int players)
{
	this->players = players;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    const char *message = "";
    if (player == 1) {
        message = "Jugador 1 ha ganado!";
    }
    else if (player == 2) {
        message = "Jugador 2 ha ganado!";
    }
    
    CCLabelTTF *label = CCLabelTTF::create(message, "YELLOW.TTF", 40.0);
    label->setColor(ccc3(92, 92, 92));
    label->setScale(0.1);
    label->setPosition(ccp(winSize.width/2, winSize.height * 0.7));
    this->addChild(label, 0);
    
    CCLabelTTF *restartLabel = CCLabelTTF::create("Reiniciar", "YELLOW.TTF", 30.0);
    restartLabel->setColor(ccc3(0, 0, 0));
    CCMenuItem *restartItem = CCMenuItemLabel::create(restartLabel, this, menu_selector(Win::restartGame));
    restartItem->setScale(0.1);
    
    CCLabelTTF *finishLabel = CCLabelTTF::create("Finalizar", "YELLOW.TTF", 30.0);
    finishLabel->setColor(ccc3(0, 0, 0));
    CCMenuItem *finishItem = CCMenuItemLabel::create(finishLabel, this, menu_selector(Win::finishGame));
    finishItem->setScale(0.1);
    
    CCMenu *menu = CCMenu::create(restartItem, finishItem, NULL);
    menu->alignItemsVerticallyWithPadding(30.0);
    menu->setPosition(ccp(winSize.width/2, winSize.height * 0.55));
    this->addChild(menu, 1);
    
    label->runAction(CCScaleTo::create(1.0, 1.0));
    restartItem->runAction(CCScaleTo::create(1.0, 1.0));
    finishItem->runAction(CCScaleTo::create(1.0, 1.0));
}

void Win::restartGame()
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5, Jugar::scene(players)));
}

void Win::finishGame()
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5, Menu::scene()));
}