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
    
    CCSprite *backgroud = CCSprite::create("fondoAboutUs.png");
    CCDirector *dir = CCDirector::sharedDirector();
    CCSize size = dir->getWinSize();
    backgroud->setScaleX(size.width/backgroud->getContentSize().width);
    backgroud->setScaleY(size.height/backgroud->getContentSize().height);
    backgroud->cocos2d::CCNode::setPosition(size.width/2, size.height/2);
    this->addChild(backgroud, 0);
    
    CCMenuItemImage *pBackItem = CCMenuItemImage::create("raqueta.png", "raqueta.png", this, menu_selector(Configuration::back));
    pBackItem->setPosition(ccp(60.0, size.height - 30.0));
    
    CCMenu* pMenu = CCMenu::create(pBackItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    CCLabelTTF *titulo = CCLabelTTF::create("Propiedades de audio", "aftershockdebris.ttf", 30.0);
    titulo->setPosition(ccp(size.width/2, size.height/2 + 60.0));
    
    CCLabelTTF *efectos = CCLabelTTF::create("Efectos", "YELLOW.TTF", 24.0);
    efectos->setPosition(ccp(size.width/3, size.height/2));
    
    CCLabelTTF *backgroundMusic = CCLabelTTF::create("Música de fondo", "YELLOW.TTF", 24.0);
    backgroundMusic->setPosition(ccp(size.width/3, size.height/2 - 40.0));
    
    CCControlSlider *sliderEffects = CCControlSlider::create("sliderTrack.png", "sliderProgress.png", "sliderThumb.png");
    sliderEffects->setMinimumValue(0.0);
    sliderEffects->setMaximumValue(1.0);
    sliderEffects->setValue(SimpleAudioEngine::sharedEngine()->getEffectsVolume());
    sliderEffects->addTargetWithActionForControlEvents(this, cccontrol_selector(Configuration::valueChangedEffects), CCControlEventValueChanged);
    sliderEffects->setPosition(ccp(3*size.width/4, size.height/2));
    
    CCControlSlider *sliderBackgroundMusic = CCControlSlider::create("sliderTrack.png", "sliderProgress.png", "sliderThumb.png");
    sliderBackgroundMusic->setMinimumValue(0.0);
    sliderBackgroundMusic->setMaximumValue(1.0);
    sliderBackgroundMusic->setValue(SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume());
    sliderBackgroundMusic->addTargetWithActionForControlEvents(this, cccontrol_selector(Configuration::valueChangedBackgroundMusic), CCControlEventValueChanged);
    sliderBackgroundMusic->setPosition(ccp(3*size.width/4, size.height/2 - 40.0));
    
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
