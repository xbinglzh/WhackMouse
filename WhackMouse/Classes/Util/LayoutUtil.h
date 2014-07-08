//
//  LayoutUtil.h
//  WhackMouse
//
//  Created by xUanBing on 14-7-9.
//
//

#ifndef __WhackMouse__LayoutUtil__
#define __WhackMouse__LayoutUtil__

#include "cocos2d.h"

USING_NS_CC;

namespace LayoutUtil {
    
    void layoutLeft(Node* view, Node* target, float offsetX = 0.0, float offsetY = 0.0);
    void layoutRight(Node* view, Node* target, float offsetX = 0.0, float offsetY = 0.0);
    void layoutTop(Node* view, Node* target, float offsetX = 0.0, float offsetY = 0.0);
    void layoutBottom(Node* view, Node* target, float offsetX = 0.0, float offsetY = 0.0);
    void layoutCenter(Node* view, Node* target, float offsetX = 0.0, float offsetY = 0.0);
    void layoutTopLeft(Node* view, Node* target, float offsetX = 0.0, float offsetY = 0.0);
    void layoutTopRight(Node* view, Node* target, float offsetX = 0.0, float offsetY = 0.0);
    void layoutBottomLeft(Node* view, Node* target, float offsetX = 0.0, float offsetY = 0.0);
    void layoutBottomRight(Node* view, Node* target, float offsetX = 0.0, float offsetY = 0.0);
    
    void layoutParentLeft(Node* view, float offsetX = 0.0, float offsetY = 0.0);
    void layoutParentRight(Node* view, float offsetX = 0.0, float offsetY = 0.0);
    void layoutParentTop(Node* view, float offsetX = 0.0, float offsetY = 0.0);
    void layoutParentBottom(Node* view, float offsetX = 0.0, float offsetY = 0.0);
    void layoutParentCenter(Node* view, float offsetX = 0.0, float offsetY = 0.0);
    void layoutParentTopLeft(Node* view, float offsetX = 0.0, float offsetY = 0.0);
    void layoutParentTopRight(Node* view, float offsetX = 0.0, float offsetY = 0.0);
    void layoutParentBottomLeft(Node* view, float offsetX = 0.0, float offsetY = 0.0);
    void layoutParentBottomRight(Node* view, float offsetX = 0.0, float offsetY = 0.0);
    
    
    void layout(Node* view, float viewAlignX, float viewAlignY, Node* target,
                float targetAlignX, float targetAlignY, bool targetIsParent = false, float offsetX = 0.0, float offsetY = 0.0);
}


#endif /* defined(__WhackMouse__LayoutUtil__) */
