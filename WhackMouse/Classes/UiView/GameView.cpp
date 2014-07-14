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
#include "GLES-Render.h"


#define PitCount 9
#define Padding_Width   100
#define Padding_height  70

#define Pit_Base_Tag    1000
#define Mouse_Base_Tag  2000

GameView::GameView() :_pitNode(NULL) {
    
}

GameView::~GameView() {
    CC_SAFE_RELEASE_NULL(_pitNode);
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
    this->setAnchorPoint(Point::ZERO);
    
    _pitNode = Node::create();
    _pitNode->setAnchorPoint(Point::ZERO);

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
    
    initPitData();
    initMouseData();

    this->addChild(_pitNode);
    
    LayoutUtil::layoutParentCenter(_pitNode, 50,-20);
    
    return true;
}

void GameView::initPitData() {
    float pitWidth = 0;
    float pitHeight = 0;
    
    for (int i = 0; i < PitCount; i++) {
        auto pit = Sprite::create("grass_pit.png");
        
        pitWidth = pit->getContentSize().width;
        pitHeight = pit->getContentSize().height;
        
        pit->setAnchorPoint(Point::ZERO);
        _pitNode->addChild(pit, 1000, Pit_Base_Tag + i);
    }
    
    _pitNode->setContentSize(Size((pitWidth + Padding_Width) * 3, (pitHeight + Padding_height) *3));
    
    for (int i =0; i < PitCount; i++) {
        LayoutUtil::layoutParentTopLeft(_pitNode->getChildByTag(Pit_Base_Tag + i),(pitWidth + Padding_Width) * (i % 3), -1 * (pitHeight + Padding_height) * (i / 3));
    }
    
}

void GameView::initMouseData() {
    for (int i = 0; i < PitCount; i++) {
        auto mouse = Sprite::create("avatar.png");
        mouse->setAnchorPoint(Point::ZERO);
        _pitNode->addChild(mouse, 2000, Mouse_Base_Tag + i);
    }
    
    for (int i = 0; i < PitCount; i++) {
        LayoutUtil::layoutCenter(_pitNode->getChildByTag(Mouse_Base_Tag + i), _pitNode->getChildByTag(Pit_Base_Tag + i), 0, 50);
    }
}

void GameView::onBackMenuCallBack() {
    auto loaddingScene = UiLoaddingView::createScene();
    auto p = TransitionZoomFlipX::create(1, loaddingScene, cocos2d::TransitionScene::Orientation::RIGHT_OVER);
    Director::getInstance()->replaceScene(p);
}


