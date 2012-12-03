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
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Menu::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("background.plist");
    CCSpriteBatchNode *batchNodeBackground = CCSpriteBatchNode::create("background.pvr.ccz");
    this->addChild(batchNodeBackground, 0);
    
    CCSprite *background = CCSprite::createWithSpriteFrameName("backgroundMenu.png");
    background->setPosition(ccp(winSize.width/2, winSize.height/2));
    batchNodeBackground->addChild(background, 0);
    
    CCLabelTTF *menu1 = CCLabelTTF::create("1 jugador", "YELLOW.TTF", 30.0);
    CCLabelTTF *menu2 = CCLabelTTF::create("2 jugadores", "YELLOW.TTF", 30.0);
    CCLabelTTF *menu3 = CCLabelTTF::create("Audio", "YELLOW.TTF", 30.0);
    CCLabelTTF *menu4 = CCLabelTTF::create("Acerca de", "YELLOW.TTF", 30.0);
    
    CCMenuItem *item1 = CCMenuItemLabel::create(menu1, this, menu_selector(Menu::menuJugar1));
    CCMenuItem *item2 = CCMenuItemLabel::create(menu2, this, menu_selector(Menu::menuJugar2));
    CCMenuItem *item3 = CCMenuItemLabel::create(menu3, this, menu_selector(Menu::menuConfig));
    CCMenuItem *item4 = CCMenuItemLabel::create(menu4, this, menu_selector(Menu::menuAboutUs));
    
    CCMenu* pMenu = CCMenu::create(item1, item2, item3, item4, NULL);
    pMenu->alignItemsVerticallyWithPadding(20);
    this->addChild(pMenu, 1);
    
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bitelip_2.mp3", true);
    
    return true;
}

void Menu::menuJugar1(CCObject *pSender)
{
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->playEffect("applause4.wav");
    CCDirector::sharedDirector()->replaceScene(CCTransitionFadeBL::create(0.5, Jugar::scene(1)));
}

void Menu::menuJugar2(CCObject *pSender)
{
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->playEffect("applause4.wav");
    CCDirector::sharedDirector()->replaceScene(CCTransitionFadeBL::create(0.5, Jugar::scene(2)));
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
