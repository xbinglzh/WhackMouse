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
//#include "LayoutUtil.h"

USING_NS_CC;

class GameView : public Layer {
    
public:
    GameView();
    ~GameView();
    
    static Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(GameView);
    
private:
    void onBackMenuCallBack();
    void initPitData();
    void layoutPit();
    
private:
    Node* _pitNode;
    float _pitGridWidth;
    float _pitGridHeight;
};



#endif /* defined(__WhackMouse__GameView__) */
