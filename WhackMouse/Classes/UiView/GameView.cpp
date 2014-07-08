//
//  GameView.cpp
//  WhackMouse
//
//  Created by xUanBing on 14-7-6.
//
//

#include "GameView.h"
#include "UiLoaddingView.h"
#include "LayoutUtil.h"

Scene* GameView::createScene() {
    auto gameScene = Scene::create();
    auto gameview = GameView::create();
    gameScene->addChild(gameview);
    return gameScene;
}

bool GameView::init() {
    if (!Layer::init()) {
        return false;
    }
    this->setAnchorPoint(Point::ZERO);
    
    auto bg = Sprite::create("gamebg1.png");
    bg->setAnchorPoint(Point::ZERO);
    this->addChild(bg);
    
    auto mainMenu = Menu::create();
    mainMenu->setAnchorPoint(Point::ZERO);
    mainMenu->setContentSize(this->getContentSize());
    this->addChild(mainMenu);
    LayoutUtil::layoutParentBottomLeft(mainMenu);
    
    auto blueMenuItem = MenuItemImage::create("btn_blue_up.png", "btn_blue_down.png", CC_CALLBACK_0(GameView::onBackMenuCallBack, this));
    mainMenu->addChild(blueMenuItem);
    
    LayoutUtil::layoutParentCenter(blueMenuItem);
    
    
    
    
    return true;
}

void GameView::onBackMenuCallBack() {
    auto loaddingScene = UiLoaddingView::createScene();
    auto p = TransitionZoomFlipX::create(1, loaddingScene, cocos2d::TransitionScene::Orientation::RIGHT_OVER);
    Director::getInstance()->replaceScene(p);
}