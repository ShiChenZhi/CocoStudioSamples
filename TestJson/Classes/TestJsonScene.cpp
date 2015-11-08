
#include "TestJsonScene.h"
USING_NS_CC;

Scene* TestJsonScene::createScene()
{
    auto scene = Scene::create();
    auto layer = TestJsonScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool TestJsonScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(TestJsonScene::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Read Json", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    
    
  
    return true;
}
#include "cocostudio/CocoStudio.h"

void TestJsonScene::readJson()
{
    bool bRet = false;
    rapidjson::Document doc;
    
    do {
        // Fetch data from file.
        ssize_t size = 0;
        unsigned char* pBytes = NULL;
        
        pBytes = FileUtils::getInstance()->getFileData("ball.json", "r", &size);
        CC_BREAK_IF(pBytes == NULL || strcmp((char*)pBytes, "") == 0);
       
        std::string load_str((const char*)pBytes, size);
        CC_SAFE_DELETE_ARRAY(pBytes);
    
        // 生成 json 文档对象
        doc.Parse<0>(load_str.c_str());
        CC_BREAK_IF(doc.HasParseError());
        
        if (!doc.IsObject()) {
            CCLOG("文档格式不对~~~~~~~~~~~~~~");
            return;
        }
        
        
    } while (0);
  
    
}

void TestJsonScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
