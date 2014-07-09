//
//  ShaderManager.h
//  WhackMouse
//
//  Created by xUanBing on 14-7-9.
//
//

#ifndef __WhackMouse__ShaderManager__
#define __WhackMouse__ShaderManager__

#include <string>
#include <list>

#include "cocos2d.h"

using namespace std;

USING_NS_CC;

class SingleShader{
    
public:
	string shaderType;
	GLProgram* pProgram;
	string pszFragSource;
    
public:
    
	SingleShader(string pShaderType, GLProgram* pPProgram, string pPszFragSource):
    shaderType(pShaderType),
    pProgram(pPProgram),
    pszFragSource(pPszFragSource){
        
	}
    
	~SingleShader(){
		delete pProgram;
	}
    
};

class ShaderManager : public Ref {
    
public:
    
	static ShaderManager* sharedInstance(){
		static ShaderManager instance;
		return &instance;
	}
    
    void reloadShaderTexture();
	void init();
	void reset();
    
    GLProgram *getShaderProgram(string shaderType);
    GLProgram *getColorShaderProgramOrCompile(const Color4F& color);
    
public:
    
    static string effect_color_brownWhite;
	//无效果
	static string effect_null;
	//按钮变暗的点击效果
	static string effect_color_dusk;
	//灰白
	static string effect_color_gray;
	//黑剪影
	static string effect_color_black;
    //白剪影
    static string effect_color_white;
	//半透灰白（淡轮廓效果）
	static string effect_color_grayAlpha;
	//黄昏化效果
	static string effect_Sephia;
    
    static string effect_color_gray_light;
    //高斯模糊
	static string effect_gaussian;
    
    static string effect_market_outline;
    //暗淡
    static string effect_gloomy;
    //高亮
    static string effect_color_bright;
    
    static string effect_color_mainView;
    
private:
	void initShader(string shaderType);
	void linkUniformShader(SingleShader* singleShader);
    
private:
	list<SingleShader* > listProgram;
	bool resetTag;
    
};


#endif /* defined(__WhackMouse__ShaderManager__) */
