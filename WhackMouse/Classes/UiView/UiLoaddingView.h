//
//  UiLoaddingView.h
//  WhackMouse
//
//  Created by xUanBing on 14-7-6.
//
//

#ifndef __WhackMouse__UiLoaddingView__
#define __WhackMouse__UiLoaddingView__

#include "cocos2d.h"

USING_NS_CC;

class UiLoaddingView : public Layer {
    
public:
    static Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(UiLoaddingView);
    
private:
    void onMenuBlueButtonCallBack(Ref* pSender);
    
};

#endif /* defined(__WhackMouse__UiLoaddingView__) */
