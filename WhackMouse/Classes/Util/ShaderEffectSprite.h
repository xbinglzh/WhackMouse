//
//  ShaderEffectSprite.h
//  WhackMouse
//
//  Created by xUanBing on 14-7-9.
//
//

#ifndef __WhackMouse__ShaderEffectSprite__
#define __WhackMouse__ShaderEffectSprite__

#include "ShaderManager.h"
#include "cocos2d.h"
#include <string>
#include "SpriteExt.h"

using namespace std;
USING_NS_CC;

class ShaderEffectSprite : public Sprite {
    
public:
	ShaderEffectSprite();
	virtual ~ShaderEffectSprite();
    
	static ShaderEffectSprite* create(string shaderType);
	static ShaderEffectSprite* create(const char* pszFileName,string shaderType);
    
    static ShaderEffectSprite* createWithSpriteFrame(SpriteFrame *pSpriteFrame,string shaderType);
    
    void changeShader(string shaderType);
    virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
    
private:
	void setShader(string shaderType);
    
};


#endif /* defined(__WhackMouse__ShaderEffectSprite__) */
