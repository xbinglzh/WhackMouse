//
//  Scale9ProgressBar.h
//  WhackMouse
//
//  Created by xUanBing on 14-7-9.
//
//

#ifndef __WhackMouse__Scale9ProgressBar__
#define __WhackMouse__Scale9ProgressBar__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class Scale9ProgressBar : public __NodeRGBA {
    
public:
    Scale9ProgressBar();
    virtual ~Scale9ProgressBar();
    
public:
    
    CC_SYNTHESIZE_READONLY(Size, m_originalSize, OriginalSize);
    
    CC_PROPERTY(Size, m_preferredSize, PreferredSize);
    CC_PROPERTY(Rect, m_capInsets, CapInsets);
    CC_PROPERTY(float, m_insetLeft, InsetLeft);
    CC_PROPERTY(float, m_insetTop, InsetTop);
    CC_PROPERTY(float, m_insetRight, InsetRight);
    CC_PROPERTY(float, m_insetBottom, InsetBottom);
    CC_PROPERTY(bool, m_bIsProgressWithHead, IsProgressWithHead);
    CC_PROPERTY(float, ratio, VisibleRatio);
    CC_PROPERTY(GLubyte, m_cOpacity, Opacity);
    
    CC_PROPERTY_PASS_BY_REF(Color3B, m_tColor, Color);
    
protected:
    bool m_bSpritesGenerated;
    Rect m_spriteRect;
    bool   m_bSpriteFrameRotated;
    Rect m_capInsetsInternal;
    bool m_positionsAreDirty;
    bool m_percentIsDirty;
    
    void setLeftPercent(int per);
    void setCenterPercent(int per);
    void setRightPercent(int per);
    
    SpriteBatchNode* scale9Image;
    
    ProgressTimer* createProgressTimer(Sprite* sprite);
    
    float leftWidth, centerWidth, rightWidth;
    
    ProgressTimer* top;
    ProgressTimer* bottom;
    ProgressTimer* centre;
    
    ProgressTimer* topLeft;
    ProgressTimer* bottomLeft;
    ProgressTimer* left;
    
    ProgressTimer* topRight;
    ProgressTimer* bottomRight;
    ProgressTimer* right;
    
    /** Conforms to CocosNodeRGBA protocol. */
    Color3B m_sColorUnmodified;
    bool m_bIsOpacityModifyRGB;
    
    void updateCapInset();
    void updatePositions();
    
    void updateVisiblePercent();
    
    void updatePercentWithHead();
    
    void updatePercent();
    
    // add by wenlong
    float m_fRatio;
    
public:
    
    virtual void setContentSize(const Size & size);
//    virtual void visit();
    
    virtual bool init();
    
    virtual bool initWithBatchNode(SpriteBatchNode* batchnode, Rect rect, bool rotated, Rect capInsets);
    virtual bool initWithBatchNode(SpriteBatchNode* batchnode, Rect rect, Rect capInsets);
    
    virtual bool initWithFile(const char* file, Rect rect,  Rect capInsets);
    
    CC_DEPRECATED_ATTRIBUTE static Scale9ProgressBar* spriteWithFile(const char* file, Rect rect, Rect capInsets);
    
    static Scale9ProgressBar* create(const char* file, Rect rect, Rect capInsets);
    
    virtual bool initWithFile(const char* file, Rect rect);
    
    CC_DEPRECATED_ATTRIBUTE static Scale9ProgressBar* spriteWithFile(const char* file, Rect rect);
    
    static Scale9ProgressBar* create(const char* file, Rect rect);
    
    virtual bool initWithFile(Rect capInsets, const char* file);
    
    CC_DEPRECATED_ATTRIBUTE static Scale9ProgressBar* spriteWithFile(Rect capInsets, const char* file);
    
    static Scale9ProgressBar* create(Rect capInsets, const char* file);
    
    virtual bool initWithFile(const char* file);
    
    CC_DEPRECATED_ATTRIBUTE static Scale9ProgressBar* spriteWithFile(const char* file);
    
    static Scale9ProgressBar* create(const char* file);
    
    virtual bool initWithSpriteFrame(SpriteFrame* spriteFrame, Rect capInsets);
    
    CC_DEPRECATED_ATTRIBUTE static Scale9ProgressBar* spriteWithSpriteFrame(SpriteFrame* spriteFrame, Rect capInsets);
    
    static Scale9ProgressBar* createWithSpriteFrame(SpriteFrame* spriteFrame, Rect capInsets);
    
    virtual bool initWithSpriteFrame(SpriteFrame* spriteFrame);
    
    CC_DEPRECATED_ATTRIBUTE static Scale9ProgressBar* spriteWithSpriteFrame(SpriteFrame* spriteFrame);
    
    static Scale9ProgressBar* createWithSpriteFrame(SpriteFrame* spriteFrame);
    
    virtual bool initWithSpriteFrameName(const char*spriteFrameName, Rect capInsets);
    
    CC_DEPRECATED_ATTRIBUTE static Scale9ProgressBar* spriteWithSpriteFrameName(const char*spriteFrameName, Rect capInsets);
    
    static Scale9ProgressBar* createWithSpriteFrameName(const char*spriteFrameName, Rect capInsets);
    
    virtual bool initWithSpriteFrameName(const char*spriteFrameName);
    
    CC_DEPRECATED_ATTRIBUTE static Scale9ProgressBar* spriteWithSpriteFrameName(const char*spriteFrameName);
    
    static Scale9ProgressBar* createWithSpriteFrameName(const char*spriteFrameName);
    
    Scale9ProgressBar* resizableSpriteWithCapInsets(Rect capInsets);
    
    //@deprecated: This interface will be deprecated sooner or later.
    CC_DEPRECATED_ATTRIBUTE static Scale9ProgressBar* node();
    
    static Scale9ProgressBar* create();
    
    virtual void setOpacityModifyRGB(bool bValue);
    
    virtual bool isOpacityModifyRGB(void);
    
    virtual bool updateWithBatchNode(SpriteBatchNode* batchnode, Rect rect, bool rotated, Rect capInsets);
    
    virtual void setSpriteFrame(SpriteFrame * spriteFrame);
    
    virtual const Color3B& getColor(void);
    
    virtual void visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags);
};


#endif /* defined(__WhackMouse__Scale9ProgressBar__) */
