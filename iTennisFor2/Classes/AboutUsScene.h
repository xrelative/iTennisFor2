//
//  AboutUsScene.h
//  cocos2dxtest1
//
//  Created by Ignacio Gómez Espinoza on 13-10-12.
//
//

#ifndef __cocos2dxtest1__AboutUsScene__
#define __cocos2dxtest1__AboutUsScene__

#include "cocos2d.h"

class AboutUs : public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    
    void back(CCObject* pSender);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(AboutUs);
};

#endif /* defined(__cocos2dxtest1__AboutUsScene__) */
