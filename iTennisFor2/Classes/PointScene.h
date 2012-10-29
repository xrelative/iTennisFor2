//
//  PointScene.h
//  iTennisFor2
//
//  Created by Ignacio Gómez Espinoza on 28-10-12.
//
//

#ifndef __iTennisFor2__PointScene__
#define __iTennisFor2__PointScene__

#include "cocos2d.h"

class Point : public cocos2d::CCLayer
{
public:
    void showPoint(int player);
    
    CREATE_FUNC(Point);
};

#endif /* defined(__iTennisFor2__PointScene__) */
