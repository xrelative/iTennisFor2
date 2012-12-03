//
//  WinScene.h
//  iTennisFor2
//
//  Created by Ignacio Gómez Espinoza on 28-10-12.
//
//

#ifndef __iTennisFor2__WinScene__
#define __iTennisFor2__WinScene__

#include "cocos2d.h"

class Win : public cocos2d::CCLayer
{
public:
	int players;
    void showRestartMenu(int player, int players);
    void restartGame();
    void finishGame();
    
    CREATE_FUNC(Win);
};

#endif /* defined(__iTennisFor2__WinScene__) */
