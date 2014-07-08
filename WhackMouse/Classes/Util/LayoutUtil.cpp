//
//  LayoutUtil.cpp
//  WhackMouse
//
//  Created by xUanBing on 14-7-9.
//
//

#include "LayoutUtil.h"

void LayoutUtil::layoutLeft(Node* view, Node* target, float offsetX /* = 0.0 */, float offsetY /* = 0.0 */) {
    layout(view, 1, 0.5, target, 0, 0.5, false, offsetX, offsetY);
}

void LayoutUtil::layoutRight(Node* view, Node* target, float offsetX /* = 0.0 */, float offsetY /* = 0.0 */) {
    layout(view, 0, 0.5, target, 1, 0.5, false, offsetX, offsetY);
}

void LayoutUtil::layoutTop(Node* view, Node* target, float offsetX /* = 0.0 */, float offsetY /* = 0.0 */) {
    layout(view, 0.5, 0, target, 0.5, 1, false, offsetX, offsetY);
}

void LayoutUtil::layoutBottom(Node* view, Node* target, float offsetX /* = 0.0 */, float offsetY /* = 0.0 */) {
    layout(view, 0.5, 1, target, 0.5, 0, false, offsetX, offsetY);
}

void LayoutUtil::layoutCenter(Node* view, Node* target, float offsetX /* = 0.0 */, float offsetY /* = 0.0 */) {
    layout(view, 0.5, 0.5, target, 0.5, 0.5, false, offsetX, offsetY);
}

void LayoutUtil::layoutTopLeft(Node* view, Node* target, float offsetX /* = 0.0 */, float offsetY /* = 0.0 */) {
    layout(view, 1, 1, target, 0, 1, false, offsetX, offsetY);
}

void LayoutUtil::layoutTopRight(Node* view, Node* target, float offsetX /* = 0.0 */, float offsetY /* = 0.0 */) {
    layout(view, 0, 1, target, 1, 1, false, offsetX, offsetY);
}

void LayoutUtil::layoutBottomLeft(Node* view, Node* target, float offsetX /* = 0.0 */, float offsetY /* = 0.0 */) {
    layout(view, 1, 0, target, 0, 0, false, offsetX, offsetY);
}

void LayoutUtil::layoutBottomRight(Node* view, Node* target, float offsetX /* = 0.0 */, float offsetY /* = 0.0 */) {
    layout(view, 0, 0, target, 1, 0, false, offsetX, offsetY);
}

void LayoutUtil::layoutParentLeft(Node* view, float offsetX /* = 0.0 */, float offsetY /* = 0.0 */) {
    layout(view, 0, 0.5, view->getParent(), 0, 0.5, true, offsetX, offsetY);
}

void LayoutUtil::layoutParentRight(Node* view, float offsetX /* = 0.0 */, float offsetY /* = 0.0 */) {
    layout(view, 1, 0.5, view->getParent(), 1, 0.5, true, offsetX, offsetY);
}

void LayoutUtil::layoutParentTop(Node* view, float offsetX /* = 0.0 */, float offsetY /* = 0.0 */) {
    layout(view, 0.5, 1, view->getParent(), 0.5, 1, true, offsetX, offsetY);
}

void LayoutUtil::layoutParentBottom(Node* view, float offsetX /* = 0.0 */, float offsetY /* = 0.0 */) {
    layout(view, 0.5, 0, view->getParent(), 0.5, 0, true, offsetX, offsetY);
}

void LayoutUtil::layoutParentCenter(Node* view, float offsetX /* = 0.0 */, float offsetY /* = 0.0 */) {
    layout(view, 0.5, 0.5, view->getParent(), 0.5, 0.5, true, offsetX, offsetY);
}

void LayoutUtil::layoutParentTopLeft(Node* view, float offsetX /* = 0.0 */, float offsetY /* = 0.0 */) {
    layout(view, 0, 1, view->getParent(), 0, 1, true, offsetX, offsetY);
}

void LayoutUtil::layoutParentTopRight(Node* view, float offsetX /* = 0.0 */, float offsetY /* = 0.0 */) {
    layout(view, 1, 1, view->getParent(), 1, 1, true, offsetX, offsetY);
}

void LayoutUtil::layoutParentBottomLeft(Node* view, float offsetX /* = 0.0 */, float offsetY /* = 0.0 */) {
    layout(view, 0, 0, view->getParent(), 0, 0, true, offsetX, offsetY);
}

void LayoutUtil::layoutParentBottomRight(Node* view, float offsetX /* = 0.0 */, float offsetY /* = 0.0 */) {
    layout(view, 1, 0, view->getParent(), 1, 0, true, offsetX, offsetY);
}


void LayoutUtil::layout(Node* src, float srcAlignX, float srcAlignY, Node* target,
                        float targetAlignX, float targetAlignY, bool targetIsParent /* = false */, float offsetX /* = 0.0 */, float offsetY /* = 0.0 */) {
    const Point& srcAnchorPoint = src->getAnchorPoint();
    const Point& anchorPointDiff = Point(srcAlignX - srcAnchorPoint.x, srcAlignY - srcAnchorPoint.y);
    const Point& targetAnchorPoint = target->getAnchorPoint();
    
    float targetAlignXPosition,targetAlignYPosition;
    
    if (targetIsParent) {
        targetAlignXPosition = target->getContentSize().width * targetAlignX;
        targetAlignYPosition = target->getContentSize().height * targetAlignY;
    } else {
        targetAlignXPosition = target->getPositionX() + target->boundingBox().size.width * (targetAlignX - targetAnchorPoint.x);
        targetAlignYPosition = target->getPositionY() + target->boundingBox().size.height * (targetAlignY - targetAnchorPoint.y);
    }
    
    src->setPosition(Point(targetAlignXPosition - anchorPointDiff.x * src->boundingBox().size.width + offsetX,
                         targetAlignYPosition - anchorPointDiff.y * src->boundingBox().size.height + offsetY));
    
}
