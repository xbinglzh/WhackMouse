//
//  GameView.h
//  WhackMouse
//
//  Created by xUanBing on 14-7-6.
//
//

#ifndef __WhackMouse__GameView__
#define __WhackMouse__GameView__

#include "cocos2d.h"

USING_NS_CC;

class GameView : public Layer {
    
public:
    static Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(GameView);
    
private:
    void onBackMenuCallBack();
    
};



#endif /* defined(__WhackMouse__GameView__) */
