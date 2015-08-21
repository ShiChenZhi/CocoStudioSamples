#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "CocosGUI.h"
#include "DialogBag.h"
USING_NS_CC;


Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
//    // 'layer' is an autorelease object
//    auto layer = HelloWorld::create();
//
//    // add layer as a child to scene
//    scene->addChild(layer);

    auto t = DialogBag::create();
    DialogBagModel* mode = new struct DialogBagModel;
    mode->createTestData();
    t->setupDialogBag(mode);
    scene->addChild(t);

    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);

    return true;
}
