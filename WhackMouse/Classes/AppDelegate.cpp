#include "AppDelegate.h"
#include "UiLoaddingView.h"
#include "Def/ConstantsDef.h"
#include "GameConfig.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {

    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    auto gConfig = GameConfig::getInstance();
    
    if(!glview) {
        glview = GLView::create("WhackMouse");
        director->setOpenGLView(glview);
    }
    
    director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / 60);
    
    // 计算最接近的屏幕尺寸的设计分辨率
    const Size &screenSize = glview->getFrameSize();
    const float screenRatio = screenSize.width / screenSize.height;
    const float offset_960_640 = fabsf(screenRatio - (960.0f / 640.0f));
    const float offset_1066_640 = fabsf(screenRatio - (1066.0f / 640.0f));
    const float offset_1138_640 = fabsf(screenRatio - (1138.0f / 640.0f));
    const float miniOffset = fminf(offset_1138_640, fminf(offset_960_640, offset_1066_640));
    
    // 设置屏幕缩放比例
    if (miniOffset == offset_960_640) {
        gConfig->setScreenSize(Scene_960_640);
    } else if (miniOffset == offset_1066_640) {
        gConfig->setScreenSize(Scene_1066_640);
    } else {
        gConfig->setScreenSize(Scene_1138_640);
    }
    
    glview->setDesignResolutionSize(1138, 640, ResolutionPolicy::FIXED_HEIGHT);
    
    Rect rect = glview->getViewPortRect();
    float scaleX = screenSize.width/rect.size.width;
    float scaleY = screenSize.height/rect.size.height ;
    director->setContentScaleFactor(MIN(scaleX, scaleY));
    
    //设置Resource路径
    std::vector<std::string> ccfilePath;
    
    ccfilePath.push_back("anim");
    ccfilePath.push_back("audio");
    ccfilePath.push_back("x_plist");
    ccfilePath.push_back("map");
    ccfilePath.push_back("ui_layout");
    ccfilePath.push_back("fonts");
    
    FileUtils::getInstance()->setSearchPaths(ccfilePath);
    
    auto scene = UiLoaddingView::createScene();
    director->runWithScene(scene);

    return true;
}


void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

}
