#ifndef __testfighter__HoldBtn__
#define __testfighter__HoldBtn__

#include "cocos2d.h"
USING_NS_CC;

class HoldBtn : public Node
{
public:
    HoldBtn();
    static HoldBtn* create(const char* file);
    virtual bool initWithFile(const char* file);
    
    CC_SYNTHESIZE(Size, iSize, Size);
    
    bool isHolding();
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);
    
    void update(float dt);
    
private:
    EventListenerTouchOneByOne* iEvent;
    Sprite* iSprite;
    
    bool isHold;
    float holdTime;
    
    void resetTime();
    
};

#endif
