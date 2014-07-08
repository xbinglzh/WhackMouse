//
//  UiLoaddingView.cpp
//  WhackMouse
//
//  Created by xUanBing on 14-7-6.
//
//

#include "UiLoaddingView.h"
#include "GameView.h"
#include "LayoutUtil.h"

USING_NS_CC;

Scene* UiLoaddingView::createScene() {
    
    auto mainScene = Scene::create();
    auto loaddingLayer = UiLoaddingView::create();
    mainScene->addChild(loaddingLayer);
    return mainScene;
    
}

bool UiLoaddingView::init() {
    if (!Layer::init()) {
        return false;
    }
    
    auto bgSprite = Sprite::create("xui_land_bg.png");
    bgSprite->setAnchorPoint(Point::ZERO);
    this->addChild(bgSprite);
    
    auto mainMenu = Menu::create();
    auto blueMenuItem = MenuItemImage::create("btn_blue_up.png", "btn_blue_down.png", CC_CALLBACK_1(UiLoaddingView::onMenuBlueButtonCallBack, this));
    mainMenu->addChild(blueMenuItem);
    this->addChild(mainMenu);
    mainMenu->setPosition(getContentSize().width - 100, 100);
    
    auto about1 = Sprite::create("aboutA.png");
    auto about2 = Sprite::create("aboutB.png");
    
    this->addChild(about1);
    this->addChild(about2);
    LayoutUtil::layoutParentCenter(about1);
    LayoutUtil::layoutBottomLeft(about2, about1);
    
    return true;
}

void UiLoaddingView::onMenuBlueButtonCallBack(cocos2d::Ref *pSender) {
    auto gameScene = GameView::createScene();
    auto p = TransitionZoomFlipX::create(1, gameScene, cocos2d::TransitionScene::Orientation::RIGHT_OVER);
    Director::getInstance()->replaceScene(p);
    
}

