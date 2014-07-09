//
//  ShaderManager.cpp
//  WhackMouse
//
//  Created by xUanBing on 14-7-9.
//
//

#include "ShaderManager.h"

string ShaderManager::effect_null = "null";
string ShaderManager::effect_color_dusk = "colorDusk";
string ShaderManager::effect_color_gray = "(0.299, 0.587, 0.114)";
string ShaderManager::effect_color_grayAlpha = "(0.1, 0.1, 0.1)";
string ShaderManager::effect_color_gray_light = "(0.588, 0.588, 0.588)";
string ShaderManager::effect_color_black = "(0, 0, 0)";
string ShaderManager::effect_color_white = "(1,1,1)";

string ShaderManager::effect_market_outline = "0.522* col.a, 0.416* col.a, 0.298* col.a";
string ShaderManager::effect_Sephia = "effect Sephia";
string ShaderManager::effect_gaussian = "effect_gaussian";
string ShaderManager::effect_color_brownWhite ="1.0 * col.a,0.95 * col.a,0.82 * col.a";

string ShaderManager::effect_gloomy = "effect_gloomy";
string ShaderManager::effect_color_bright = "effect_color_bright";

string ShaderManager::effect_color_mainView = "";

void ShaderManager::init(){
    
    reloadShaderTexture();
    
//    NotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(ShaderManager::reloadShaderTexture),EVNET_COME_TO_FOREGROUND, NULL);
    
    
}

void ShaderManager::reloadShaderTexture() {
    
    if(listProgram.empty()){
		initShader(effect_null);
		initShader(effect_color_dusk);
		initShader(effect_color_black);
        initShader(effect_color_white);
		initShader(effect_color_gray);
		initShader(effect_color_grayAlpha);
		initShader(effect_color_gray_light);
        initShader(effect_color_brownWhite);
        initShader(effect_market_outline);
		initShader(effect_Sephia);
        initShader(effect_gloomy);
        initShader(effect_color_bright);
        initShader(effect_color_mainView);
        
	}else {
		list<SingleShader*>::iterator itr= listProgram.begin();
		while(itr!=listProgram.end()) {
			if((*itr)->shaderType!=effect_null){
				linkUniformShader((*itr));
			}
			itr++;
		}
	}
    
}

void ShaderManager::initShader(string shaderType){
	
	stringstream ss;
    
	if(shaderType == effect_null) {
        
		listProgram.push_back(new SingleShader(shaderType,
                    GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR),
                    ""));
        
		return;
	}else if(shaderType == effect_color_dusk) {
		ss<<"#ifdef GL_ES \n \
        precision mediump float; \n \
        #endif \n \
        uniform sampler2D u_texture; \n \
        varying vec2 v_texCoord; \n \
        varying vec4 v_fragmentColor; \n \
        void main(void) \n \
        { \n \
        // Convert to greyscale using NTSC weightings \n \
        vec4 col = texture2D(u_texture, v_texCoord); \n \
        float grey = dot(col.rgb, vec3(0.3, 0.3, 0.3)); \n \
        gl_FragColor = vec4(col.r*0.7,col.g*0.7,col.b*0.7 , col.a); \n \
        }";
	}else if(shaderType == effect_color_gray || shaderType == effect_color_grayAlpha
             || shaderType == effect_color_black || shaderType == effect_color_white
             || shaderType == effect_color_gray_light){
        
		std::string alphaPara = shaderType == effect_color_grayAlpha ? "*0.3" : "";
        
		//灰白
		ss<<"#ifdef GL_ES \n \
        precision mediump float; \n \
        #endif \n \
        uniform sampler2D u_texture; \n \
        varying vec2 v_texCoord; \n \
        varying vec4 v_fragmentColor; \n \
        void main(void) \n \
        { \n \
        // Convert to greyscale using NTSC weightings \n \
        vec4 col = texture2D(u_texture, v_texCoord); \n \
        float grey = dot(col.rgb, vec3"<<shaderType<<"); \n \
        gl_FragColor = vec4(grey, grey, grey, col.a"<<alphaPara<<"); \n \
        }";
	}else if(shaderType == effect_color_brownWhite || shaderType == effect_market_outline){
        ss<<"#ifdef GL_ES \n \
        precision mediump float; \n \
        #endif \n \
        uniform sampler2D u_texture; \n \
        varying vec2 v_texCoord; \n \
        varying vec4 v_fragmentColor; \n \
        void main(void) \n \
        { \n \
        // Convert to greyscale using NTSC weightings \n \
        vec4 col = texture2D(u_texture, v_texCoord); \n \
        gl_FragColor = vec4(" << shaderType << ", col.a); \n \
        }";
    }else if(shaderType == effect_Sephia){
		//黄昏化
		ss << "#ifdef GL_ES \n \
        precision mediump float; \n \
        #endif \n \
        uniform sampler2D u_texture; \n \
        varying vec2 v_texCoord; \n \
        varying vec4 v_fragmentColor; \n \
        void main(void) \n \
        { \n \
        vec4 col = texture2D(u_texture, v_texCoord); \n \
        float grey = dot(col.rgb, vec3(0.299, 0.587, 0.114)); \n \
        gl_FragColor = vec4(grey * vec3(1.2, 1.0, 0.8), col.a); \n \
        }";
    }else if(shaderType == effect_gaussian){
		//////高斯模糊
		ss << "#ifdef GL_ES \n \
        precision mediump float; \n \
        #endif \n \
        uniform sampler2D u_texture; \n \
        uniform vec2 tcOffset[25];\n \
        varying vec2 v_texCoord; \n \
        varying vec4 v_fragmentColor; \n \
        void main(void) \n \
        { \n \
        vec4 sample[25]; \n \
        for (int i = 0; i < 25; i++) \n \
        { \n \
        sample[i] = texture(u_texture, v_texCoord + tcOffset[i]); \n \
        } \n \
        gl_FragColor = ( \n \
        (1.0  * (sample[0] + sample[4]  + sample[20] + sample[24])) + \n \
        (4.0  * (sample[1] + sample[3]  + sample[5]  + sample[9] + sample[15] + sample[19] + sample[21] + sample[23])) + \n \
        (7.0  * (sample[2] + sample[10] + sample[14] + sample[22])) + \n \
        (16.0 * (sample[6] + sample[8]  + sample[16] + sample[18])) + \n \
        (26.0 * (sample[7] + sample[11] + sample[13] + sample[17])) + \n \
        (41.0 * sample[12]) \n \
        ) / 273.0; \n \
        }";
    }else if (shaderType == effect_gloomy){
        //暗淡
        ss << "#ifdef GL_ES \n \
        precision mediump float; \n \
        #endif \n \
        uniform sampler2D u_texture; \n \
        varying vec2 v_texCoord; \n \
        varying vec4 v_fragmentColor; \n \
        void main(void) \n \
        { \n \
        vec4 col = texture2D(u_texture, v_texCoord); \n \
        float grey = dot(col.rgb, vec3(0.0, 0.587, 0.114)); \n \
        gl_FragColor = vec4(grey * vec3(1.2, 1.0, 0.8), col.a); \n \
        }";
        
    }else if (shaderType == effect_color_bright) {
        //高亮
        ss << "#ifdef GL_ES \n \
        precision mediump float; \n \
        #endif \n \
        uniform sampler2D u_texture; \n \
        varying vec2 v_texCoord; \n \
        varying vec4 v_fragmentColor; \n \
        void main(void) \n \
        { \n \
        // Convert to greyscale using NTSC weightings \n \
        vec4 col = texture2D(u_texture, v_texCoord); \n \
        gl_FragColor = vec4(col.r*1.5,col.g*1.5,col.b*1.5 , col.a); \n \
        }";
        
    }else if (shaderType == effect_color_mainView) {
        
        ss << "#ifdef GL_ES \n \
        precision mediump float; \n \
        #endif \n \
        uniform sampler2D u_texture; \n \
        varying vec2 v_texCoord; \n \
        varying vec4 v_fragmentColor; \n \
        void main(void) \n \
        { \n \
        // Convert to greyscale using NTSC weightings \n \
        vec4 col = texture2D(u_texture, v_texCoord); \n \
        float grey = dot(col.rgb, vec3(0.3, 0.3, 0.3)); \n \
        gl_FragColor = vec4(col.r*0.4,col.g*0.4,col.b*0.7, col.a ); \n \
        }";
        
    }
    
    string str=ss.str();
    //        const GLchar* pszFragSource =str.c_str();
    
    GLProgram* pProgram = new GLProgram();
    
    SingleShader* singleShader = new SingleShader(shaderType, pProgram, str);
    linkUniformShader(singleShader);
    
    listProgram.push_back(singleShader);
}

void ShaderManager::linkUniformShader(SingleShader* singleShader){
    
    GLProgram* pProgram = singleShader->pProgram;
    
    pProgram->reset();
    pProgram->initWithByteArrays(ccPositionTextureColor_vert, singleShader->pszFragSource.c_str());
    
    pProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
    pProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
    pProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
    
    pProgram->link();
    
    pProgram->updateUniforms();
    CHECK_GL_ERROR_DEBUG();
    
}

void ShaderManager::reset(){
    resetTag = true;
}

GLProgram* ShaderManager::getShaderProgram(string shaderType){
    
    if(resetTag || listProgram.size() == 0){
        init();
        resetTag = false;
    }
    
    list<SingleShader* >::iterator itr = listProgram.begin();
    
    while(itr!=listProgram.end()){
        
        if((*itr)->shaderType == shaderType){
            return (*itr)->pProgram;
        }
        
        itr++;
    }
    
    return NULL;
}

GLProgram *ShaderManager::getColorShaderProgramOrCompile(const Color4F& color) {
    char key[20];
    sprintf(key, "%.3f%.3f%.3f", color.r, color.g, color.b);
    
    cocos2d::GLProgram* program = GLProgramCache::getInstance()->getGLProgram(key);
    
    if (!program) {
        char value[30];
        sprintf(value, "vec4(%.3f,%.3f,%.3f,%.3f)", color.r, color.g, color.b, color.a);
        
        char alpha[6];
        sprintf(alpha, "%.3f", color.a);
        
        stringstream ss;
        
        ss <<
        "											\n\
        #ifdef GL_ES								\n\
        precision lowp float;						\n\
        #endif										\n\
        \n\
        varying vec4 v_fragmentColor;				\n\
        varying vec2 v_texCoord;					\n\
        uniform sampler2D CC_Texture0;				\n\
        \n\
        void main()									\n\
        {											\n\
        gl_FragColor = v_fragmentColor * texture2D(CC_Texture0, v_texCoord) * " << value << ";			\n\
        }											\n\
        ";
        
        program = new cocos2d::GLProgram();
        
        program->initWithByteArrays(ccPositionTextureColor_vert, ss.str().c_str());
        program->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
        program->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
        program->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
        
        program->link();
        program->updateUniforms();
        
        GLProgramCache::getInstance()->addGLProgram(program, key);
        
        program->release();
    }
    
    return program;
}

