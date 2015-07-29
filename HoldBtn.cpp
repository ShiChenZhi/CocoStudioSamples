#include "HoldBtn.h"

HoldBtn::HoldBtn():
iEvent(nullptr),
iSprite(nullptr),
isHold(false),
holdTime(0),
iSize(0,0)
{}

HoldBtn* HoldBtn::create(const char *file)
{
    auto t = new HoldBtn;
    if (t && t->initWithFile(file)) {
        t->autorelease();
        return t;
    }
    
    CC_SAFE_DELETE(t);
    return NULL;
}

bool HoldBtn::initWithFile(const char *file)
{
    bool bRet = false;
    do {
        CC_BREAK_IF(!Node::init());
        
        iSprite = Sprite::create(file);
        addChild(iSprite);
        setSize(iSprite->getContentSize());
        
        iEvent = EventListenerTouchOneByOne::create();
        iEvent->onTouchBegan = CC_CALLBACK_2(HoldBtn::onTouchBegan, this);
        iEvent->onTouchEnded = CC_CALLBACK_2(HoldBtn::onTouchEnded, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(iEvent, this);
        iEvent->setSwallowTouches(true);
        
        bRet = true;
    } while (0);
    
    return bRet;
}

bool HoldBtn::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    bool bRet = false;
    
    Vec2 point = convertTouchToNodeSpace(touch);
    if (iSprite->getBoundingBox().containsPoint(point) ) {
        resetTime();
        isHold = true;
        bRet = true;
        scheduleUpdate();
    }
    else {
        isHold = false;
    }
    
    return true;
}

void HoldBtn::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    isHold = false;
    unscheduleUpdate();
}

void HoldBtn::resetTime()
{
    holdTime = 0;
}

bool HoldBtn::isHolding()
{
    return isHold;
}

void HoldBtn::update(float dt)
{
    holdTime += dt;
    log("holdtime = %f", holdTime);
}
