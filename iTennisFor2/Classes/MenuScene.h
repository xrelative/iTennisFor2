//
//  MenuScene.h
//  cocos2dxtest1
//
//  Created by Ignacio Gómez Espinoza on 13-10-12.
//
//

#ifndef __cocos2dxtest1__MenuScene__
#define __cocos2dxtest1__MenuScene__

#include "cocos2d.h"

class Menu : public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    
    void menuCloseCallback(CCObject* pSender);
    void menuJugar(CCObject* pSender);
    void menuConfig(CCObject* pSender);
    void menuAboutUs(CCObject* pSender);
    void ActivateSound(CCObject* pSender);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(Menu);
};

#endif /* defined(__cocos2dxtest1__MenuScene__) */
