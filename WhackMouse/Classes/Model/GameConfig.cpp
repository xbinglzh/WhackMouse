//
//  GameConfig.cpp
//  WhackMouse
//
//  Created by xUanBing on 14-7-12.
//
//

#include "GameConfig.h"

USING_NS_CC;

static GameConfig * _configSharedInstance = NULL;

GameConfig::GameConfig() : Ref() {
    
}

GameConfig::~GameConfig() {
    
}

GameConfig * GameConfig::getInstance(){
	
	if (! _configSharedInstance) {
        _configSharedInstance = new GameConfig();
        _configSharedInstance->init();
    }
	
	return _configSharedInstance;
}

void GameConfig::purgeInstance() {
    
	CC_SAFE_RELEASE_NULL(_configSharedInstance);
    
}

bool GameConfig::init() {
    
    return true;
}

int GameConfig::getScreenSize() {
    return _screenSize;
}

void GameConfig::setScreenSize(int var) {
    this->_screenSize = var;
}

