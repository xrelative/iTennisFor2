//
//  AboutUsScene.cpp
//  cocos2dxtest1
//
//  Created by Ignacio Gómez Espinoza on 13-10-12.
//
//

#include "AboutUsScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* AboutUs::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    AboutUs *layer = AboutUs::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool AboutUs::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("background.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("sprites.plist");
    CCSpriteBatchNode *batchNodeBackground = CCSpriteBatchNode::create("background.pvr.ccz");
    CCSpriteBatchNode *batchNodeSprites = CCSpriteBatchNode::create("sprites.pvr.ccz");
    this->addChild(batchNodeBackground, 0);
    this->addChild(batchNodeSprites, 1);
    
    CCSprite *backgroud = CCSprite::createWithSpriteFrameName("backgroundSubmenu.png");
    backgroud->cocos2d::CCNode::setPosition(winSize.width/2, winSize.height/2);
    batchNodeBackground->addChild(backgroud, 0);
    
    CCSprite *spriteBack = CCSprite::createWithSpriteFrameName("raqueta.png");
    CCMenuItemSprite *pBackItem = CCMenuItemSprite::create(spriteBack, spriteBack, this, menu_selector(AboutUs::back));
    pBackItem->setPosition(ccp(60.0, winSize.height - 30.0));
    
    CCMenu* pMenu = CCMenu::create(pBackItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 2);
    
    CCLabelTTF *titulo = CCLabelTTF::create("Desarrollado por", "aftershockdebris.ttf", 30.0);
    titulo->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2 + 30.0));
    CCLabelTTF *integrante1 = CCLabelTTF::create("Cristian Arenas U.", "YELLOW.TTF", 24.0);
    integrante1->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2));
    CCLabelTTF *integrante2 = CCLabelTTF::create("Ignacio Gómez E.", "YELLOW.TTF", 24.0);
    integrante2->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2 - 24.0));
    CCLabelTTF *integrante3 = CCLabelTTF::create("Lukas Pérez I.", "YELLOW.TTF", 24.0);
    integrante3->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2 - 48.0));
    CCLabelTTF *integrante4 = CCLabelTTF::create("Diego Villouta F.", "YELLOW.TTF", 24.0);
    integrante4->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2 - 72.0));
    
    this->addChild(titulo, 3);
    this->addChild(integrante1, 3);
    this->addChild(integrante2, 3);
    this->addChild(integrante3, 3);
    this->addChild(integrante4, 3);
    
    return true;
}

void AboutUs::back(CCObject* pSender)
{
    SimpleAudioEngine::sharedEngine()->playEffect("tennisserve.wav");
    CCDirector::sharedDirector()->popScene();
}
