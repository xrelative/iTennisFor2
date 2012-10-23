//
//  MenuScene.cpp
//  cocos2dxtest1
//
//  Created by Ignacio Gómez Espinoza on 13-10-12.
//
//

#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "JugarScene.h"
#include "ConfigurationScene.h"
#include "AboutUsScene.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* Menu::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Menu *layer = Menu::create();
    CCSprite *backgroud = CCSprite::create("fondo.png");
    CCDirector *dir = CCDirector::sharedDirector();
    backgroud->setScaleX(dir->getWinSize().width/backgroud->getContentSize().width);
    backgroud->setScaleY(dir->getWinSize().height/backgroud->getContentSize().height);
    backgroud->cocos2d::CCNode::setPosition(dir->getWinSize().width/2, dir->getWinSize().height/2);
    layer->addChild(backgroud, 0);
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Menu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCLabelTTF *menu1 = CCLabelTTF::create("Jugar", "YELLOW.TTF", 30.0);
    CCLabelTTF *menu2 = CCLabelTTF::create("Audio", "YELLOW.TTF", 30.0);
    CCLabelTTF *menu3 = CCLabelTTF::create("Acerca de", "YELLOW.TTF", 30.0);
    CCLabelTTF *menu4 = CCLabelTTF::create("Salir", "YELLOW.TTF", 30.0);
    
    CCMenuItem *item1 = CCMenuItemLabel::create(menu1, this, menu_selector(Menu::menuJugar));
    CCMenuItem *item2 = CCMenuItemLabel::create(menu2, this, menu_selector(Menu::menuConfig));
    CCMenuItem *item3 = CCMenuItemLabel::create(menu3, this, menu_selector(Menu::menuAboutUs));
    CCMenuItem *item4 = CCMenuItemLabel::create(menu4, this, menu_selector(Menu::menuCloseCallback));
    
    CCMenu* pMenu = CCMenu::create(item1, item2, item3, item4, NULL);
    pMenu->alignItemsVerticallyWithPadding(20);
    this->addChild(pMenu, 1);
    
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bitelip_2.mp3", true);
    
    return true;
}

void Menu::menuJugar(CCObject *pSender)
{
    SimpleAudioEngine::sharedEngine()->playEffect("tennisserve.wav");
    CCDirector::sharedDirector()->pushScene(CCTransitionFadeBL::create(0.5, Jugar::scene()));
}

void Menu::menuConfig(CCObject *pSender)
{
    SimpleAudioEngine::sharedEngine()->playEffect("tennisserve.wav");
    CCDirector::sharedDirector()->pushScene(CCTransitionCrossFade::create(0.5, Configuration::scene()));
}

void Menu::menuAboutUs(CCObject *pSender)
{
    SimpleAudioEngine::sharedEngine()->playEffect("tennisserve.wav");
    CCDirector::sharedDirector()->pushScene(CCTransitionCrossFade::create(0.5, AboutUs::scene()));
}

void Menu::menuCloseCallback(CCObject* pSender)
{
    SimpleAudioEngine::sharedEngine()->playEffect("tennisserve.wav");
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
