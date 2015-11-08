#ifndef __TestJsonScene__
#define __TestJsonScene__

#include "cocos2d.h"

class TestJsonScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(TestJsonScene);
    
    void readJson();
};

#endif // __HELLOWORLD_SCENE_H__
