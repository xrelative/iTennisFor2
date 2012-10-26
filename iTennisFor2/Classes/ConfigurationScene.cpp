//
//  ConfigurationScene.cpp
//  cocos2dxtest1
//
//  Created by Ignacio Gómez Espinoza on 13-10-12.
//
//

#include "ConfigurationScene.h"
#include "SimpleAudioEngine.h"
#include "CCControlExtensions.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace CocosDenshion;

CCScene* Configuration::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Configuration *layer = Configuration::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Configuration::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("sprites.plist");
    CCSpriteBatchNode *batchNode = CCSpriteBatchNode::create("sprites.png");
    this->addChild(batchNode, 0);
    
    CCSprite *backgroud = CCSprite::create("backgroundSubmenu.png");
    backgroud->setScaleX(winSize.width/backgroud->getContentSize().width);
    backgroud->setScaleY(winSize.height/backgroud->getContentSize().height);
    backgroud->cocos2d::CCNode::setPosition(winSize.width/2, winSize.height/2);
    this->addChild(backgroud, 0);
    
    CCSprite *backSprite = CCSprite::createWithSpriteFrameName("raqueta.png");
    CCMenuItemSprite *pBackItem = CCMenuItemSprite::create(backSprite, backSprite, this, menu_selector(Configuration::back));
    pBackItem->setPosition(ccp(60.0, winSize.height - 30.0));
    
    CCMenu* pMenu = CCMenu::create(pBackItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    CCLabelTTF *titulo = CCLabelTTF::create("Propiedades de audio", "aftershockdebris.ttf", 30.0);
    titulo->setPosition(ccp(winSize.width/2, winSize.height/2 + 60.0));
    
    CCLabelTTF *efectos = CCLabelTTF::create("Efectos", "YELLOW.TTF", 24.0);
    efectos->setPosition(ccp(winSize.width/2, winSize.height/2));
    
    CCLabelTTF *backgroundMusic = CCLabelTTF::create("Música de fondo", "YELLOW.TTF", 24.0);
    backgroundMusic->setPosition(ccp(winSize.width/2, winSize.height/2 - 60.0));
    
    CCSprite *sliderTrackSprite1 = CCSprite::createWithSpriteFrameName("sliderTrack.png");
    CCSprite *sliderProgressSprite1 = CCSprite::createWithSpriteFrameName("sliderProgress.png");
    CCSprite *sliderThumbSprite1 = CCSprite::createWithSpriteFrameName("sliderThumb.png");
    CCControlSlider *sliderEffects = CCControlSlider::create(sliderTrackSprite1, sliderProgressSprite1, sliderThumbSprite1);
    sliderEffects->setMinimumValue(0.0);
    sliderEffects->setMaximumValue(1.0);
    sliderEffects->setValue(SimpleAudioEngine::sharedEngine()->getEffectsVolume());
    sliderEffects->addTargetWithActionForControlEvents(this, cccontrol_selector(Configuration::valueChangedEffects), CCControlEventValueChanged);
    sliderEffects->setPosition(ccp(winSize.width/2, winSize.height/2 - 20.0));
    
    CCSprite *sliderTrackSprite2 = CCSprite::createWithSpriteFrameName("sliderTrack.png");
    CCSprite *sliderProgressSprite2 = CCSprite::createWithSpriteFrameName("sliderProgress.png");
    CCSprite *sliderThumbSprite2 = CCSprite::createWithSpriteFrameName("sliderThumb.png");
    CCControlSlider *sliderBackgroundMusic = CCControlSlider::create(sliderTrackSprite2, sliderProgressSprite2, sliderThumbSprite2);
    sliderBackgroundMusic->setMinimumValue(0.0);
    sliderBackgroundMusic->setMaximumValue(1.0);
    sliderBackgroundMusic->setValue(SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume());
    sliderBackgroundMusic->addTargetWithActionForControlEvents(this, cccontrol_selector(Configuration::valueChangedBackgroundMusic), CCControlEventValueChanged);
    sliderBackgroundMusic->setPosition(ccp(winSize.width/2, winSize.height/2 - 80.0));
    
    this->addChild(titulo, 2);
    this->addChild(efectos, 2);
    this->addChild(backgroundMusic, 2);
    this->addChild(sliderEffects, 2);
    this->addChild(sliderBackgroundMusic, 2);
    
    return true;
}

void Configuration::valueChangedEffects(CCObject *pSender, CCControlEvent *cEvent)
{
    CCControlSlider *pSlider = (CCControlSlider *) pSender;
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(pSlider->getValue());
}

void Configuration::valueChangedBackgroundMusic(CCObject *pSender, CCControlEvent *cEvent)
{
    CCControlSlider *pSlider = (CCControlSlider *) pSender;
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(pSlider->getValue());
}

void Configuration::back(CCObject* pSender)
{
    SimpleAudioEngine::sharedEngine()->playEffect("tennisserve.wav");
    CCDirector::sharedDirector()->popScene();
}
