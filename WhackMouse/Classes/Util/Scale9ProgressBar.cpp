//
//  Scale9ProgressBar.cpp
//  WhackMouse
//
//  Created by xUanBing on 14-7-9.
//
//

#include "Scale9ProgressBar.h"

enum positions
{
    pCentre = 0,
    pTop,
    pLeft,
    pRight,
    pBottom,
    pTopRight,
    pTopLeft,
    pBottomRight,
    pBottomLeft
};

Scale9ProgressBar::Scale9ProgressBar()
: m_insetLeft(0)
, m_insetTop(0)
, m_insetRight(0)
, m_insetBottom(0)
, m_cOpacity(0)
, m_bSpritesGenerated(false)
, m_bSpriteFrameRotated(false)
, m_positionsAreDirty(false)
, scale9Image(NULL)
, topLeft(NULL)
, top(NULL)
, topRight(NULL)
, left(NULL)
, centre(NULL)
, right(NULL)
, bottomLeft(NULL)
, bottom(NULL)
, bottomRight(NULL)
, m_bIsOpacityModifyRGB(false)
, m_fRatio(1)
, m_bIsProgressWithHead(false)
, m_percentIsDirty(false)
{
    
}

Scale9ProgressBar::~Scale9ProgressBar()
{
    CC_SAFE_RELEASE(scale9Image);
}

bool Scale9ProgressBar::init()
{
    return this->initWithBatchNode(NULL, Rect::ZERO, Rect::ZERO);
}

bool Scale9ProgressBar::initWithBatchNode(SpriteBatchNode* batchnode, Rect rect, Rect capInsets)
{
    return this->initWithBatchNode(batchnode, rect, false, capInsets);
}

bool Scale9ProgressBar::initWithBatchNode(SpriteBatchNode* batchnode, Rect rect, bool rotated, Rect capInsets)
{
    if(batchnode) {
        this->updateWithBatchNode(batchnode, rect, rotated, capInsets);
        this->setAnchorPoint(Point(0.5f, 0.5f));
    }
    
    this->m_positionsAreDirty = true;
    
    return true;
}

ProgressTimer* Scale9ProgressBar::createProgressTimer(Sprite* sprite){
    ProgressTimer* temp = ProgressTimer::create(sprite);
    
    temp->setType(ProgressTimer::Type::BAR);
    temp->setMidpoint(Point::ZERO);
    temp->setBarChangeRate(Point(1,0));
    temp->setReverseProgress(false);
    
    return temp;
}

bool Scale9ProgressBar::updateWithBatchNode(SpriteBatchNode* batchnode, Rect rect, bool rotated, Rect capInsets)
{
    GLubyte opacity = m_cOpacity;
    Color3B color = m_tColor;
    
    // Release old sprites
    this->removeAllChildrenWithCleanup(true);
    
    if(this->scale9Image != batchnode)
    {
        CC_SAFE_RELEASE(this->scale9Image);
        scale9Image = batchnode;
        CC_SAFE_RETAIN(scale9Image);
    }
    
    scale9Image->removeAllChildrenWithCleanup(true);
    
    m_capInsets = capInsets;
    
    // If there is no given rect
    if ( rect.equals(Rect::ZERO)) {
        Size textureSize = scale9Image->getTextureAtlas()->getTexture()->getContentSize();
        rect = Rect(0, 0, textureSize.width, textureSize.height);
    }
    
    // Set the given rect's size as original size
    m_spriteRect = rect;
    m_originalSize = rect.size;
    m_preferredSize = m_originalSize;
    m_capInsetsInternal = capInsets;
    
    // Get the image edges
    float l = rect.origin.x;
    float t = rect.origin.y;
    float h = rect.size.height;
    float w = rect.size.width;
    
    // If there is no specified center region
    if ( m_capInsetsInternal.equals(Rect::ZERO) )
    {
        // Apply the 3x3 grid format
        if (rotated) {
            m_capInsetsInternal = Rect(l+h/3, t+w/3, w/3, h/3);
        }else {
            m_capInsetsInternal = Rect(l+w/3, t+h/3, w/3, h/3);
        }
    }
    
    //
    // Set up the image
    //
    if (rotated)
    {
        // Sprite frame is rotated
        
        // Centre
        Sprite* tempcentre = Sprite::createWithTexture(scale9Image->getTexture(), m_capInsetsInternal, true);
        centre = CCProgressTimer::create(tempcentre);
        addChild(centre, 0, pCentre);
        
        // Bottom
        Sprite* tempbottom =  Sprite::createWithTexture(scale9Image->getTexture(),
                Rect(l, m_capInsetsInternal.origin.y, m_capInsetsInternal.size.width, m_capInsetsInternal.origin.x - l), rotated);

        bottom = createProgressTimer(tempbottom);
        addChild(bottom, 1, pBottom);
        
        // Top
        Sprite* temptop = CCSprite::createWithTexture(scale9Image->getTexture(),
                Rect(m_capInsetsInternal.origin.x + m_capInsetsInternal.size.height,
                     m_capInsetsInternal.origin.y,
                     m_capInsetsInternal.size.width,
                     h - m_capInsetsInternal.size.height - (m_capInsetsInternal.origin.x - l)),
                rotated);
        
        top = createProgressTimer(temptop);
        addChild(top, 1, pTop);
        
        // Right
        Sprite* tempRight = Sprite::createWithTexture(scale9Image->getTexture(),
                        Rect(m_capInsetsInternal.origin.x,
                            m_capInsetsInternal.origin.y+m_capInsetsInternal.size.width,
                            w - (m_capInsetsInternal.origin.y-t)-m_capInsetsInternal.size.width,
                            m_capInsetsInternal.size.height),
                        rotated);

        
        right = createProgressTimer(tempRight);
        addChild(right, 1, pRight);
        
        // Left
        Sprite* templeft = Sprite::createWithTexture(scale9Image->getTexture(),
                        Rect(m_capInsetsInternal.origin.x, t,
                             m_capInsetsInternal.origin.y - t,
                             m_capInsetsInternal.size.height),
                        rotated);
        
        left = createProgressTimer(templeft);
        addChild(left ,1, pLeft);
        
        // Top right
        Sprite* temptopRight = Sprite::createWithTexture(scale9Image->getTexture(),
                        Rect(m_capInsetsInternal.origin.x + m_capInsetsInternal.size.height,
                             m_capInsetsInternal.origin.y + m_capInsetsInternal.size.width,
                             w - (m_capInsetsInternal.origin.y-t)-m_capInsetsInternal.size.width,
                             h - m_capInsetsInternal.size.height - (m_capInsetsInternal.origin.x - l)),
                        rotated);

        topRight = createProgressTimer(temptopRight);
        addChild(topRight ,2 ,pTopRight);
        
        // Top left
        Sprite* temptopLeft = Sprite::createWithTexture(scale9Image->getTexture(),
                        Rect(m_capInsetsInternal.origin.x + m_capInsetsInternal.size.height,
                             t,
                             m_capInsetsInternal.origin.y - t,
                             h - m_capInsetsInternal.size.height - (m_capInsetsInternal.origin.x - l)),
                        rotated);
        
        topLeft = createProgressTimer(temptopLeft);
        addChild(topLeft, 2, pTopLeft);
        
        // Bottom right
        Sprite* tempbottomRight  = Sprite::createWithTexture(scale9Image->getTexture(),
                        Rect(l,
                             m_capInsetsInternal.origin.y + m_capInsetsInternal.size.width,
                             w - (m_capInsetsInternal.origin.y-t)-m_capInsetsInternal.size.width,
                             m_capInsetsInternal.origin.x - l),
                        rotated);
        
        bottomRight = createProgressTimer(tempbottomRight);
        addChild(bottomRight, 2, pBottomRight);
        
        // Bottom left
        Sprite* tempbottomLeft = Sprite::createWithTexture(scale9Image->getTexture(),
                        Rect(l,
                             t,
                             m_capInsetsInternal.origin.y - t,
                             m_capInsetsInternal.origin.x - l),
                        rotated);
        
        bottomLeft = createProgressTimer(tempbottomLeft);
        addChild(bottomLeft, 2, pBottomLeft);
    }
    else
    {
        // Sprite frame is not rotated
        // Centre
        Sprite* tempcentre = Sprite::createWithTexture(scale9Image->getTexture(), m_capInsetsInternal, rotated);
        centre = createProgressTimer(tempcentre);
        addChild(centre, 0, pCentre);
        
        // Top
        Sprite* temptop = Sprite::createWithTexture(scale9Image->getTexture(),
                            Rect(m_capInsetsInternal.origin.x,
                                 t,
                                 m_capInsetsInternal.size.width,
                                 m_capInsetsInternal.origin.y - t),
                            rotated);

        top = createProgressTimer(temptop);
        addChild(top, 1, pTop);
        
        // Bottom
        Sprite* tempbottom = Sprite::createWithTexture(scale9Image->getTexture(),
                               Rect( m_capInsetsInternal.origin.x,
                                     m_capInsetsInternal.origin.y + m_capInsetsInternal.size.height,
                                     m_capInsetsInternal.size.width,
                                     h - (m_capInsetsInternal.origin.y - t + m_capInsetsInternal.size.height)),
                               rotated);

        bottom = createProgressTimer(tempbottom);
        addChild(bottom, 1, pBottom);
        
        // Left
        Sprite* templeft = Sprite::createWithTexture(scale9Image->getTexture(),
                        Rect(l,
                             m_capInsetsInternal.origin.y,
                             m_capInsetsInternal.origin.x - l,
                             m_capInsetsInternal.size.height),
                        rotated);

        left = createProgressTimer(templeft);
        addChild(left, 1, pLeft);
        
        // Right
        Sprite* tempright = Sprite::createWithTexture(scale9Image->getTexture(),
                            Rect( m_capInsetsInternal.origin.x + m_capInsetsInternal.size.width,
                                  m_capInsetsInternal.origin.y,
                                  w - (m_capInsetsInternal.origin.x - l + m_capInsetsInternal.size.width),
                                  m_capInsetsInternal.size.height),
                            rotated);

        right = createProgressTimer(tempright);
        addChild(right, 1, pRight);
        
        // Top left
        Sprite* temptopLeft = Sprite::createWithTexture(scale9Image->getTexture(),
                               Rect( l, t,
                                     m_capInsetsInternal.origin.x - l,
                                     m_capInsetsInternal.origin.y - t),
                               rotated);

        topLeft = createProgressTimer(temptopLeft);
        addChild(topLeft, 2, pTopLeft);
        
        // Top right
        Sprite* temptopRight = Sprite::createWithTexture(scale9Image->getTexture(),
                                Rect(
                                    m_capInsetsInternal.origin.x + m_capInsetsInternal.size.width,
                                    t,
                                    w - (m_capInsetsInternal.origin.x - l + m_capInsetsInternal.size.width),
                                    m_capInsetsInternal.origin.y - t),
                                rotated);
        
        topRight = createProgressTimer(temptopRight);
        addChild(topRight, 2, pTopRight);
        
        // Bottom left
        Sprite* tempbottomLeft = Sprite::createWithTexture(scale9Image->getTexture(),
                            Rect( l,
                                  m_capInsetsInternal.origin.y + m_capInsetsInternal.size.height,
                                  m_capInsetsInternal.origin.x - l,
                                  h - (m_capInsetsInternal.origin.y - t + m_capInsetsInternal.size.height)),
                            rotated);

        bottomLeft = createProgressTimer(tempbottomLeft);
        addChild(bottomLeft, 2, pBottomLeft);
        
        // Bottom right
        Sprite* tempbottomRight = Sprite::createWithTexture(scale9Image->getTexture(),
                                    Rect(
                                        m_capInsetsInternal.origin.x + m_capInsetsInternal.size.width,
                                        m_capInsetsInternal.origin.y + m_capInsetsInternal.size.height,
                                        w - (m_capInsetsInternal.origin.x - l + m_capInsetsInternal.size.width),
                                        h - (m_capInsetsInternal.origin.y - t + m_capInsetsInternal.size.height)),
                                    rotated);

        bottomRight = createProgressTimer(tempbottomRight);
        addChild(bottomRight, 2, pBottomRight);
    }
    
    this->setContentSize(rect.size);
    this->addChild(scale9Image);
    
    if (m_bSpritesGenerated)
    {
        // Restore color and opacity
        this->setOpacity(opacity);
        this->setColor(color);
    }
    m_bSpritesGenerated = true;
    
    return true;
}

void Scale9ProgressBar::setContentSize(const Size &size)
{
    Node::setContentSize(size);
    this->m_positionsAreDirty = true;
}

void Scale9ProgressBar::setIsProgressWithHead(bool var){
    m_bIsProgressWithHead = var;
}

bool Scale9ProgressBar::getIsProgressWithHead(){
    return m_bIsProgressWithHead;
}

void Scale9ProgressBar::setVisibleRatio(float ratio){
    if(ratio < 0){
        ratio = 0;
    }else if(ratio > 1){
        ratio = 1;
    }
    m_fRatio = ratio;
    
    this->updateVisiblePercent();
    this->updatePositions();
    
    m_percentIsDirty = true;
}

float Scale9ProgressBar::getVisibleRatio(){
    return m_fRatio;
}

void Scale9ProgressBar::setLeftPercent(int percent){
    left->setPercentage(percent);
    topLeft->setPercentage(percent);
    bottomLeft->setPercentage(percent);
}

void Scale9ProgressBar::setCenterPercent(int percent){
    centre->setPercentage(percent);
    top->setPercentage(percent);
    bottom->setPercentage(percent);
}

void Scale9ProgressBar::setRightPercent(int percent){
    right->setPercentage(percent);
    topRight->setPercentage(percent);
    bottomRight->setPercentage(percent);
}

void Scale9ProgressBar::updatePercent(){
    float width = m_fRatio * this->getContentSize().width;
    if (width >= 0 && width < leftWidth) {
        int percent = 100.0 * (width)/leftWidth;
        setLeftPercent(percent);
        setCenterPercent(0);
        setRightPercent(0);
    }else if (width >= leftWidth && width < leftWidth + centerWidth) {
        int percent = 100.0 * (width - leftWidth)/centerWidth;
        setLeftPercent(100);
        setCenterPercent(percent);
        setRightPercent(0);
    }else if (width >= leftWidth + centerWidth) {
        int percent = 100.0 * (width - leftWidth - centerWidth)/rightWidth;
        setLeftPercent(100);
        setCenterPercent(100);
        setRightPercent(percent);
    }
}

void Scale9ProgressBar::updatePercentWithHead(){
    setLeftPercent(100);
    setCenterPercent(100);
    setRightPercent(100);
    float width = (m_preferredSize.width - m_originalSize.width)*m_fRatio + m_originalSize.width;
    //    CCLOG("new width %.2f", width);
    setContentSize(Size(width, m_preferredSize.height));
}

void Scale9ProgressBar::updateVisiblePercent(){
    if(m_bIsProgressWithHead){
        updatePercentWithHead();
    }else{
        this->updatePositions();
        updatePercent();
    }
}

void Scale9ProgressBar::updatePositions()
{
    Size size = this->getContentSize();
    
    float sizableWidth = size.width - topLeft->getContentSize().width - topRight->getContentSize().width;
    centerWidth = sizableWidth;
    float sizableHeight = size.height - topLeft->getContentSize().height - bottomRight->getContentSize().height;
    
    float horizontalScale = sizableWidth/centre->getContentSize().width;
    float verticalScale = sizableHeight/centre->getContentSize().height;
    centre->setScaleX(horizontalScale);
    centre->setScaleY(verticalScale);
    
    float rescaledWidth = centre->getContentSize().width * horizontalScale;
    float rescaledHeight = centre->getContentSize().height * verticalScale;
    
    leftWidth = bottomLeft->getContentSize().width;
    rightWidth = right->getContentSize().width;
    float bottomHeight = bottomLeft->getContentSize().height;
    
    bottomLeft->setAnchorPoint(Point::ZERO);
    bottomRight->setAnchorPoint(Point::ZERO);
    topLeft->setAnchorPoint(Point::ZERO);
    topRight->setAnchorPoint(Point::ZERO);
    left->setAnchorPoint(Point::ZERO);
    right->setAnchorPoint(Point::ZERO);
    top->setAnchorPoint(Point::ZERO);
    bottom->setAnchorPoint(Point::ZERO);
    centre->setAnchorPoint(Point::ZERO);
    
    // Position corners
    bottomLeft->setPosition(Point::ZERO);
    bottomRight->setPosition(Point(leftWidth+rescaledWidth,0));
    topLeft->setPosition(Point(0, bottomHeight+rescaledHeight));
    topRight->setPosition(Point(leftWidth+rescaledWidth, bottomHeight+rescaledHeight));
    
    // Scale and position borders
    left->setPosition(Point(0, bottomHeight));
    left->setScaleY(verticalScale);
    right->setPosition(Point(leftWidth+rescaledWidth,bottomHeight));
    right->setScaleY(verticalScale);
    bottom->setPosition(Point(leftWidth,0));
    bottom->setScaleX(horizontalScale);
    top->setPosition(Point(leftWidth,bottomHeight+rescaledHeight));
    top->setScaleX(horizontalScale);
    
    // Position centre
    centre->setPosition(Point(leftWidth, bottomHeight));
    
}

bool Scale9ProgressBar::initWithFile(const char* file, Rect rect, Rect capInsets)
{
    CCAssert(file != NULL, "Invalid file for sprite");
    
    SpriteBatchNode *batchnode = SpriteBatchNode::create(file, 9);
    bool pReturn = this->initWithBatchNode(batchnode, rect, capInsets);
    return pReturn;
}

Scale9ProgressBar* Scale9ProgressBar::spriteWithFile(const char* file, Rect rect,  Rect capInsets)
{
    return Scale9ProgressBar::create(file, rect, capInsets);
}

Scale9ProgressBar* Scale9ProgressBar::create(const char* file, Rect rect,  Rect capInsets)
{
    Scale9ProgressBar* pReturn = new Scale9ProgressBar();
    if ( pReturn && pReturn->initWithFile(file, rect, capInsets) )
    {
        pReturn->autorelease();
        return pReturn;
    }
    CC_SAFE_DELETE(pReturn);
    return NULL;
}

Scale9ProgressBar* Scale9ProgressBar::create(Rect capInsets, const char* file)
{
    Scale9ProgressBar* pReturn = new Scale9ProgressBar();
    if ( pReturn && pReturn->initWithFile(file, Rect::ZERO, capInsets) )
    {
        pReturn->autorelease();
        return pReturn;
    }
    CC_SAFE_DELETE(pReturn);
    return NULL;
}

bool Scale9ProgressBar::initWithFile(const char* file, Rect rect)
{
    CCAssert(file != NULL, "Invalid file for sprite");
    bool pReturn = this->initWithFile(file, rect, Rect::ZERO);
    return pReturn;
}

Scale9ProgressBar* Scale9ProgressBar::spriteWithFile(const char* file, Rect rect)
{
    return Scale9ProgressBar::create(file, rect);
}

Scale9ProgressBar* Scale9ProgressBar::create(const char* file, Rect rect)
{
    Scale9ProgressBar* pReturn = new Scale9ProgressBar();
    if ( pReturn && pReturn->initWithFile(file, rect) )
    {
        pReturn->autorelease();
        return pReturn;
    }
    CC_SAFE_DELETE(pReturn);
    return NULL;
}


bool Scale9ProgressBar::initWithFile(Rect capInsets, const char* file)
{
    bool pReturn = this->initWithFile(file, Rect::ZERO, capInsets);
    return pReturn;
}

Scale9ProgressBar* Scale9ProgressBar::spriteWithFile(Rect capInsets, const char* file)
{
    return Scale9ProgressBar::create(capInsets, file);
}

bool Scale9ProgressBar::initWithFile(const char* file)
{
    bool pReturn = this->initWithFile(file, Rect::ZERO);
    return pReturn;
    
}

Scale9ProgressBar* Scale9ProgressBar::spriteWithFile(const char* file)
{
    return Scale9ProgressBar::create(file);
}

Scale9ProgressBar* Scale9ProgressBar::create(const char* file)
{
    Scale9ProgressBar* pReturn = new Scale9ProgressBar();
    if ( pReturn && pReturn->initWithFile(file) )
    {
        pReturn->autorelease();
        return pReturn;
    }
    CC_SAFE_DELETE(pReturn);
    return NULL;
}

bool Scale9ProgressBar::initWithSpriteFrame(SpriteFrame* spriteFrame, Rect capInsets)
{
    CCAssert(spriteFrame != NULL, "Sprite frame must be not nil");
    
    SpriteBatchNode *batchnode = SpriteBatchNode::createWithTexture(spriteFrame->getTexture(), 9);
    bool pReturn = this->initWithBatchNode(batchnode, spriteFrame->getRect(), spriteFrame->isRotated(), capInsets);
    return pReturn;
}

Scale9ProgressBar* Scale9ProgressBar::spriteWithSpriteFrame(SpriteFrame* spriteFrame, Rect capInsets)
{
    return Scale9ProgressBar::createWithSpriteFrame(spriteFrame, capInsets);
}

Scale9ProgressBar* Scale9ProgressBar::createWithSpriteFrame(SpriteFrame* spriteFrame, Rect capInsets)
{
    Scale9ProgressBar* pReturn = new Scale9ProgressBar();
    if ( pReturn && pReturn->initWithSpriteFrame(spriteFrame, capInsets) )
    {
        pReturn->autorelease();
        return pReturn;
    }
    CC_SAFE_DELETE(pReturn);
    return NULL;
}
bool Scale9ProgressBar::initWithSpriteFrame(SpriteFrame* spriteFrame)
{
    CCAssert(spriteFrame != NULL, "Invalid spriteFrame for sprite");
    bool pReturn = this->initWithSpriteFrame(spriteFrame, Rect::ZERO);
    return pReturn;
}


Scale9ProgressBar* Scale9ProgressBar::spriteWithSpriteFrame(SpriteFrame* spriteFrame)
{
    return Scale9ProgressBar::createWithSpriteFrame(spriteFrame);
}

Scale9ProgressBar* Scale9ProgressBar::createWithSpriteFrame(SpriteFrame* spriteFrame)
{
    Scale9ProgressBar* pReturn = new Scale9ProgressBar();
    if ( pReturn && pReturn->initWithSpriteFrame(spriteFrame) )
    {
        pReturn->autorelease();
        return pReturn;
    }
    CC_SAFE_DELETE(pReturn);
    return NULL;
}

bool Scale9ProgressBar::initWithSpriteFrameName(const char* spriteFrameName, Rect capInsets)
{
    CCAssert(spriteFrameName != NULL, "Invalid spriteFrameName for sprite");
    
    SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
    bool pReturn = this->initWithSpriteFrame(frame, capInsets);
    return pReturn;
}

Scale9ProgressBar* Scale9ProgressBar::spriteWithSpriteFrameName(const char* spriteFrameName, Rect capInsets)
{
    return Scale9ProgressBar::createWithSpriteFrameName(spriteFrameName, capInsets);
}

Scale9ProgressBar* Scale9ProgressBar::createWithSpriteFrameName(const char* spriteFrameName, Rect capInsets)
{
    Scale9ProgressBar* pReturn = new Scale9ProgressBar();
    if ( pReturn && pReturn->initWithSpriteFrameName(spriteFrameName, capInsets) )
    {
        pReturn->autorelease();
        return pReturn;
    }
    CC_SAFE_DELETE(pReturn);
    return NULL;
}

bool Scale9ProgressBar::initWithSpriteFrameName(const char* spriteFrameName)
{
    bool pReturn = this->initWithSpriteFrameName(spriteFrameName, Rect::ZERO);
    return pReturn;
}

Scale9ProgressBar* Scale9ProgressBar::spriteWithSpriteFrameName(const char* spriteFrameName)
{
    return Scale9ProgressBar::createWithSpriteFrameName(spriteFrameName);
}

Scale9ProgressBar* Scale9ProgressBar::createWithSpriteFrameName(const char* spriteFrameName)
{
    Scale9ProgressBar* pReturn = new Scale9ProgressBar();
    if ( pReturn && pReturn->initWithSpriteFrameName(spriteFrameName) )
    {
        pReturn->autorelease();
        return pReturn;
    }
    CC_SAFE_DELETE(pReturn);
    return NULL;
    
}

Scale9ProgressBar* Scale9ProgressBar::resizableSpriteWithCapInsets(Rect capInsets)
{
    Scale9ProgressBar* pReturn = new Scale9ProgressBar();
    if ( pReturn && pReturn->initWithBatchNode(scale9Image, m_spriteRect, capInsets) )
    {
        pReturn->autorelease();
        return pReturn;
    }
    CC_SAFE_DELETE(pReturn);
    return NULL;
}

Scale9ProgressBar* Scale9ProgressBar::node()
{
    return Scale9ProgressBar::create();
}

Scale9ProgressBar* Scale9ProgressBar::create()
{
    Scale9ProgressBar *pReturn = new Scale9ProgressBar();
    if (pReturn)
    {
        pReturn->autorelease();
        return pReturn;
    }
    CC_SAFE_DELETE(pReturn);
    return NULL;
}


//LabelBMFont - CCRGBAProtocol protocol
void Scale9ProgressBar::setColor(const Color3B& color3)
{
    m_tColor = color3;
    
    if (scale9Image->getChildren().size() != 0)
    {
        
        for (const auto& child : scale9Image->getChildren())
        {
            __RGBAProtocol* pNode = dynamic_cast<__RGBAProtocol*>(child);
            if (pNode)
            {
                pNode->setColor(m_tColor);
            }
        }
    }
}

const Color3B& Scale9ProgressBar::getColor(void) const {
    return m_tColor;
}

void Scale9ProgressBar::setOpacity(GLubyte var)
{
    m_cOpacity = var;
    
    if (scale9Image->getChildren().size() != 0)
    {
        
        for (const auto& child : scale9Image->getChildren())
        {
            __RGBAProtocol* pNode = dynamic_cast<__RGBAProtocol*>(child);
            if (pNode)
            {
                pNode->setOpacity(m_cOpacity);
            }
        }
    }
}

/** sets the opacity.
 @warning If the the texture has premultiplied alpha then, the R, G and B channels will be modifed.
 Values goes from 0 to 255, where 255 means fully opaque.
 */
GLubyte Scale9ProgressBar::getOpacity()
{
    return m_cOpacity;
}

void Scale9ProgressBar::setPreferredSize(Size preferedSize)
{
    this->setContentSize(preferedSize);
    this->m_preferredSize = preferedSize;
}

Size Scale9ProgressBar::getPreferredSize()
{
    return this->m_preferredSize;
}

void Scale9ProgressBar::setCapInsets(Rect capInsets)
{
    Size contentSize = this->getContentSize();
    this->updateWithBatchNode(this->scale9Image, this->m_spriteRect, m_bSpriteFrameRotated, capInsets);
    this->setContentSize(contentSize);
}

Rect Scale9ProgressBar::getCapInsets()
{
    return m_capInsets;
}

void Scale9ProgressBar::updateCapInset()
{
    Rect insets;
    if (this->m_insetLeft == 0 && this->m_insetTop == 0 && this->m_insetRight == 0 && this->m_insetBottom == 0)
    {
        insets = Rect::ZERO;
    }
    else
    {
        if (m_bSpriteFrameRotated)
        {
            insets = Rect(m_spriteRect.origin.x + m_insetBottom,
                                m_spriteRect.origin.y + m_insetLeft,
                                m_spriteRect.size.width-m_insetRight-m_insetLeft,
                                m_spriteRect.size.height-m_insetTop-m_insetBottom);
        }
        else
        {
            insets = Rect(m_spriteRect.origin.x + m_insetLeft,
                                m_spriteRect.origin.y + m_insetTop,
                                m_spriteRect.size.width-m_insetLeft-m_insetRight,
                                m_spriteRect.size.height-m_insetTop-m_insetBottom);
        }
    }
    this->setCapInsets(insets);
}

void Scale9ProgressBar::setOpacityModifyRGB(bool var)
{
    m_bIsOpacityModifyRGB = var;
    if (scale9Image->getChildren().size() != 0)
    {
        
        for (const auto& child : scale9Image->getChildren())
        {
            __RGBAProtocol* pNode = dynamic_cast<__RGBAProtocol*>(child);
            if (pNode)
            {
                pNode->setOpacityModifyRGB(m_bIsOpacityModifyRGB);
            }
        }
    }
}
bool Scale9ProgressBar::isOpacityModifyRGB()
{
    return m_bIsOpacityModifyRGB;
}

void Scale9ProgressBar::setSpriteFrame(SpriteFrame * spriteFrame)
{
    SpriteBatchNode * batchnode = SpriteBatchNode::createWithTexture(spriteFrame->getTexture(), 9);
    this->updateWithBatchNode(batchnode, spriteFrame->getRect(), spriteFrame->isRotated(), Rect::ZERO);
    
    // Reset insets
    this->m_insetLeft = 0;
    this->m_insetTop = 0;
    this->m_insetRight = 0;
    this->m_insetBottom = 0;
}

float Scale9ProgressBar::getInsetLeft()
{
    return this->m_insetLeft;
}

float Scale9ProgressBar::getInsetTop()
{
    return this->m_insetTop;
}

float Scale9ProgressBar::getInsetRight()
{
    return this->m_insetRight;
}

float Scale9ProgressBar::getInsetBottom()
{
    return this->m_insetBottom;
}

void Scale9ProgressBar::setInsetLeft(float insetLeft)
{
    this->m_insetLeft = insetLeft;
    this->updateCapInset();
}

void Scale9ProgressBar::setInsetTop(float insetTop)
{
    this->m_insetTop = insetTop;
    this->updateCapInset();
}

void Scale9ProgressBar::setInsetRight(float insetRight)
{
    this->m_insetRight = insetRight;
    this->updateCapInset();
}

void Scale9ProgressBar::setInsetBottom(float insetBottom)
{
    this->m_insetBottom = insetBottom;
    this->updateCapInset();
}

void Scale9ProgressBar::visit(cocos2d::Renderer *renderer, const cocos2d::Mat4 &parentTransform, uint32_t parentFlags) {
//    auto renderer = Director::getInstance()->getRenderer();
//    Mat4 parentTransform = Director::getInstance()->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
//    visit(renderer, parentTransform, true);
    
    if(this->m_percentIsDirty) {
        this->updateVisiblePercent();
        this->m_percentIsDirty = false;
    }

    if(this->m_positionsAreDirty) {
        this->updatePositions();
        this->m_positionsAreDirty = false;
    }
    
    CCNode::visit(renderer, parentTransform, parentFlags);
}
