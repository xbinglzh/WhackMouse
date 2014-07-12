//
//  GameConfig.h
//  WhackMouse
//
//  Created by xUanBing on 14-7-12.
//
//

#ifndef __WhackMouse__GameConfig__
#define __WhackMouse__GameConfig__

#include "cocos2d.h"
#include "ConstantsDef.h"

class GameConfig : public cocos2d::Ref {
    
protected:
	GameConfig();
	virtual ~GameConfig();
	bool init();
    
public:
    static GameConfig *getInstance();
    static void purgeInstance();
    
public:
    /**
     * 当前屏幕尺寸
     */
    CC_PROPERTY(int, _screenSize, ScreenSize);
    
};


#endif /* defined(__WhackMouse__GameConfig__) */
