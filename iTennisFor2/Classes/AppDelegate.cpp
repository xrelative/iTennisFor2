//
//  cocos2dxtest1AppDelegate.cpp
//  cocos2dxtest1
//
//  Created by Ignacio Gómez Espinoza on 13-10-12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//

#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "MenuScene.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    pDirector->enableRetinaDisplay(true);
    
    //TargetPlatform target = getTargetPlatform();
    
//    if (target == kTargetIpad)
//    {
//        // ipad
//        
//        // try to enable retina on device
//        if (true == pDirector->enableRetinaDisplay(true))
//        {
//            // iphone hd
//            CCFileUtils::sharedFileUtils()->setResourceDirectory("spriteshd");
//            CCFileUtils::sharedFileUtils()->setResourceDirectory("backgroundhd");
//        }
//        else
//        {
//            CCFileUtils::sharedFileUtils()->setResourceDirectory("sprites");
//            CCFileUtils::sharedFileUtils()->setResourceDirectory("background");
//        }
//    }
//    else if (target == kTargetIphone)
//    {
//        // iphone
//        
//        // try to enable retina on device
//        if (true == pDirector->enableRetinaDisplay(true))
//        {
//            // iphone hd
//            CCFileUtils::sharedFileUtils()->setResourceDirectory("spriteshd");
//            CCFileUtils::sharedFileUtils()->setResourceDirectory("backgroundhd");
//        }
//        else
//        {
//            CCFileUtils::sharedFileUtils()->setResourceDirectory("sprites");
//            CCFileUtils::sharedFileUtils()->setResourceDirectory("background");
//            
//        }
//    }
//    else
//    {
//        // android, windows, blackberry, linux or mac
//        // use 960*640 resources as design resolution size
//        CCFileUtils::sharedFileUtils()->setResourceDirectory("spriteshd");
//        CCFileUtils::sharedFileUtils()->setResourceDirectory("backgroundhd");
//        //CCEGLView::sharedOpenGLView()->setDesignResolutionSize(800, 480, kResolutionNoBorder);
//    }
    //CCFileUtils::sharedFileUtils()->setResourceDirectory("spriteshd");
    //CCFileUtils::sharedFileUtils()->setResourceDirectory("backgroundhd");

    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = Menu::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();

    // if you use SimpleAudioEngine, it must be paused
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
    
    // if you use SimpleAudioEngine, it must resume here
    if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    }
}
