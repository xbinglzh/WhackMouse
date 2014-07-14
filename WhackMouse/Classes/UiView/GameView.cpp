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

#define PitCount 9
#define Padding_Width   40
#define Padding_height  20

GameView::GameView() :_pitNode(NULL), _pitGridWidth(0), _pitGridHeight(0) {
    
}

GameView::~GameView() {
    CC_SAFE_RELEASE_NULL(_pitNode);
    _pitGridHeight = 0;
    _pitGridWidth = 0;
}

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
    
    _pitNode = Node::create();
    _pitNode->setAnchorPoint(Point::ZERO);
    this->setAnchorPoint(Point::ZERO);
    
    auto bg = Sprite::create("xmap_back_grass.png");
    bg->setScale(this->getContentSize().width / bg->getContentSize().width, this->getContentSize().height / bg->getContentSize().height);
    bg->setAnchorPoint(Point::ZERO);
    this->addChild(bg);
    
    auto mainMenu = Menu::create();
    mainMenu->setAnchorPoint(Point::ZERO);
    mainMenu->setContentSize(this->getContentSize());
    this->addChild(mainMenu);
    LayoutUtil::layoutParentBottomLeft(mainMenu);
    
    auto blueMenuItem = MenuItemImage::create("btn_blue_up.png", "btn_blue_down.png", CC_CALLBACK_0(GameView::onBackMenuCallBack, this));
    mainMenu->addChild(blueMenuItem);
    
    LayoutUtil::layoutParentBottomRight(blueMenuItem, -100, 100);
    
    this->addChild(_pitNode);
    initPitData();
    layoutPit();
    
    _pitNode->setContentSize(Size(Vec2(_pitGridWidth * 3, _pitGridHeight * 3)));
    CCLOG("pitNode w : %f, h : %f", _pitNode->getContentSize().width, _pitNode->getContentSize().height);
    LayoutUtil::layoutParentTop(_pitNode);
    
    return true;
}

void GameView::initPitData() {
    for (int i = 0; i < PitCount; i++) {
        auto pit = Sprite::create("grass_pit.png");
        pit->setAnchorPoint(Point::ZERO);
        _pitNode->addChild(pit, 1000, i);
    }
}

void GameView::layoutPit() {
    
    _pitGridWidth = _pitNode->getChildByTag(0)->getContentSize().width ;
    _pitGridHeight = _pitNode->getChildByTag(0)->getContentSize().height ;
    
    for (int i = 0; i < PitCount; i++) {
        LayoutUtil::layoutParentTop(_pitNode->getChildByTag(i), _pitGridWidth * (i % 3), -1 * _pitGridHeight * (i / 3));
    }
}

void GameView::onBackMenuCallBack() {
    auto loaddingScene = UiLoaddingView::createScene();
    auto p = TransitionZoomFlipX::create(1, loaddingScene, cocos2d::TransitionScene::Orientation::RIGHT_OVER);
    Director::getInstance()->replaceScene(p);
}


