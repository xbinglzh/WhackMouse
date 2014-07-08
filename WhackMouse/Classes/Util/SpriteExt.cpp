//
//  SpriteExt.cpp
//  WhackMouse
//
//  Created by xUanBing on 14-7-9.
//
//

#include "SpriteExt.h"

std::map<std::string, int32_t> SpriteExt::_textureRefs;

SpriteExt::SpriteExt() {
    
}

SpriteExt::~SpriteExt() {
    if (_texturefileName.length() > 0) {
        std::map<std::string, int32_t>::iterator iter =  _textureRefs.find(_texturefileName);
        if (iter != _textureRefs.end()) {
            iter->second --;
            if (iter->second <= 0) {
                iter->second = 0;
                
                TextureCache::getInstance()->removeTextureForKey(_texturefileName.c_str());
            }
        }
    }
}

bool SpriteExt::initWithFile(const char *pszFilename) {
    
    if(Sprite::initWithFile(pszFilename)) {
        std::map<std::string, int32_t>::iterator iter =  _textureRefs.find(pszFilename);
        if (iter != _textureRefs.end()) {
            iter->second ++;
        }else{
            _textureRefs[pszFilename] = 1;
        }
        this->_texturefileName = pszFilename;
        return true;
    }
    return false;
}

SpriteExt* SpriteExt::create(const char *pszFileName){
    SpriteExt *pobSprite = new SpriteExt();
    
    if (pobSprite && pobSprite->initWithFile(pszFileName)) {
        
        pobSprite->autorelease();
        return pobSprite;
    }
    
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}
