#ifndef __TestJsonScene__
#define __TestJsonScene__

#include "cocos2d.h"

class TestJsonScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(TestJsonScene);
    
    void readJson();
    void writeJson();
};

#endif // __HELLOWORLD_SCENE_H__
