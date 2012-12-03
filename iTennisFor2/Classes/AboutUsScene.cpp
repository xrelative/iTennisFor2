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
    
    CCLabelTTF *titulo1 = CCLabelTTF::create("Desarrollado por", "aftershockdebris.ttf", 25.0);
    titulo1->setPosition(ccp(winSize.width/2, winSize.height * 0.85));
    CCLabelTTF *integrante1 = CCLabelTTF::create("Cristian Arenas U.", "YELLOW.TTF", 20.0);
    integrante1->setPosition(ccp(winSize.width/2, winSize.height * 0.75));
    CCLabelTTF *integrante2 = CCLabelTTF::create("Ignacio Gómez E.", "YELLOW.TTF", 20.0);
    integrante2->setPosition(ccp(winSize.width/2, winSize.height * 0.70));
    CCLabelTTF *integrante3 = CCLabelTTF::create("Lukas Pérez I.", "YELLOW.TTF", 20.0);
    integrante3->setPosition(ccp(winSize.width/2, winSize.height * 0.65));
    CCLabelTTF *integrante4 = CCLabelTTF::create("Diego Villouta F.", "YELLOW.TTF", 20.0);
    integrante4->setPosition(ccp(winSize.width/2, winSize.height * 0.60));
    
    CCLabelTTF *titulo2 = CCLabelTTF::create("Desarrollado para el ramo", "aftershockdebris.ttf", 25.0);
    titulo2->setPosition(ccp(winSize.width/2, winSize.height * 0.50));
    CCLabelTTF *ramo = CCLabelTTF::create("Taller de creación de videojuegos", "YELLOW.TTF", 20.0);
    ramo->setPosition(ccp(winSize.width/2, winSize.height * 0.40));
    
    CCLabelTTF *titulo3 = CCLabelTTF::create("Profesores", "aftershockdebris.ttf", 25.0);
    titulo3->setPosition(ccp(winSize.width/2, winSize.height * 0.30));
    CCLabelTTF *profesor1 = CCLabelTTF::create("Daniel Winkler Rosa", "YELLOW.TTF", 20.0);
    profesor1->setPosition(ccp(winSize.width/2, winSize.height * 0.20));
    CCLabelTTF *profesor2 = CCLabelTTF::create("Pablo Mera Pastor", "YELLOW.TTF", 20.0);
    profesor2->setPosition(ccp(winSize.width/2, winSize.height * 0.15));
    
    CCLabelTTF *universidad = CCLabelTTF::create("Universidad Técnica Federico Santa María", "YELLOW.TTF", 20.0);
    universidad->setPosition(ccp(winSize.width/2, winSize.height * 0.05));
    
    this->addChild(titulo1, 3);
    this->addChild(integrante1, 3);
    this->addChild(integrante2, 3);
    this->addChild(integrante3, 3);
    this->addChild(integrante4, 3);
    this->addChild(titulo2, 3);
    this->addChild(ramo, 3);
    this->addChild(titulo3, 3);
    this->addChild(profesor1, 3);
    this->addChild(profesor2, 3);
    this->addChild(universidad, 3);
    
    return true;
}

void AboutUs::back(CCObject* pSender)
{
    SimpleAudioEngine::sharedEngine()->playEffect("tennisserve.wav");
    CCDirector::sharedDirector()->popScene();
}
