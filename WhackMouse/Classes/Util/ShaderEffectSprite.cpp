//
//  ShaderEffectSprite.cpp
//  WhackMouse
//
//  Created by xUanBing on 14-7-9.
//
//

#include "ShaderEffectSprite.h"
#include <sstream>

ShaderEffectSprite::ShaderEffectSprite(){
    
}

ShaderEffectSprite::~ShaderEffectSprite(){
    
}

ShaderEffectSprite* ShaderEffectSprite::create(string shader){
	ShaderEffectSprite* graySprite = new ShaderEffectSprite();
	if (graySprite && graySprite->init()){
        graySprite->setShader(shader);
		graySprite->autorelease();
		return graySprite;
	}else{
		CC_SAFE_RELEASE(graySprite);
		return NULL;
	}
}

ShaderEffectSprite* ShaderEffectSprite::create( const char* pszFileName,string shader){
	ShaderEffectSprite* graySprite = new ShaderEffectSprite();
	if (graySprite && graySprite->initWithFile(pszFileName)){
        //        graySprite->_texturefileName = pszFileName;
        graySprite->setShader(shader);
		graySprite->autorelease();
		return graySprite;
	}else{
		CC_SAFE_RELEASE(graySprite);
		return NULL;
	}
}

ShaderEffectSprite* ShaderEffectSprite::createWithSpriteFrame(SpriteFrame *pSpriteFrame,string shader){
	ShaderEffectSprite* graySprite = new ShaderEffectSprite();
	if (graySprite && graySprite->initWithSpriteFrame(pSpriteFrame)){
        graySprite->setShader(shader);
		graySprite->autorelease();
		return graySprite;
	}else{
		CC_SAFE_RELEASE(graySprite);
		return NULL;
	}
}

void ShaderEffectSprite::changeShader(string shaderType){
	setShader(shaderType);
}

void ShaderEffectSprite::setShader(string shaderType){
	GLProgram* pProgram = ShaderManager::sharedInstance()->getShaderProgram(shaderType);
	this->setGLProgram(pProgram);
}

void ShaderEffectSprite::draw(Renderer *renderer, const Mat4& transform, uint32_t flags){
    Sprite::draw(renderer, transform, flags);
}



