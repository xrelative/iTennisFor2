//
//  ConfigurationScene.h
//  cocos2dxtest1
//
//  Created by Ignacio Gómez Espinoza on 13-10-12.
//
//

#ifndef __cocos2dxtest1__ConfigurationScene__
#define __cocos2dxtest1__ConfigurationScene__

#include "cocos2d.h"
#include "CCControlExtensions.h"

class Configuration : public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    
    void back(CCObject *pSender);
    void valueChangedEffects(CCObject *pSender, cocos2d::extension::CCControlEvent *cEvent);
    void valueChangedBackgroundMusic(CCObject *pSender, cocos2d::extension::CCControlEvent *cEvent);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(Configuration);
};

#endif /* defined(__cocos2dxtest1__ConfigurationScene__) */
