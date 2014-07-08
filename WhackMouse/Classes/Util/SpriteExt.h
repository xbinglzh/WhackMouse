//
//  SpriteExt.h
//  WhackMouse
//
//  Created by xUanBing on 14-7-9.
//
//

#ifndef __WhackMouse__SpriteExt__
#define __WhackMouse__SpriteExt__

#include "cocos2d.h"

USING_NS_CC;

class  SpriteExt : public Sprite {
    
public:
    SpriteExt();
    virtual ~SpriteExt();
    static SpriteExt* create(const char *pszFileName);
    bool initWithFile(const char *pszFilename);
    
private:
    static std::map<std::string, int32_t> _textureRefs;
    
private:
    std::string _texturefileName;
    
};


#endif /* defined(__WhackMouse__SpriteExt__) */
