
#include "TestJsonScene.h"
USING_NS_CC;

#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

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
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithSystemFont("Read Json", "", 24);
    
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
    
    
    readJson();
    writeJson();
  
    return true;
}

void TestJsonScene::readJson()
{
    rapidjson::Document doc;
    
    do {
        // Fetch data from file.
        Data  filedata = FileUtils::getInstance()->getDataFromFile("stock.json");
        std::string load_str((const char*)filedata.getBytes(), filedata.getSize());
        CCLOG("读取的 json 文件内容(验证前)：\n%s", load_str.c_str());
    
        // Generate json document object.
        doc.Parse<0>(load_str.c_str());
        CC_BREAK_IF(doc.HasParseError());
        CC_BREAK_IF(!doc.IsObject());
        
        
        // Get ‘object’ or ‘value’ via [].
        if(!doc.HasMember("stock"))
            return;
        
        const rapidjson::Value &pArray = doc["stock"];
        if(!pArray.IsArray())
            return;
        
        for (rapidjson::SizeType i = 0; i<pArray.Size(); i++)
        {
            const rapidjson::Value& p = pArray[i];
            if (p.HasMember("product")) {
                const rapidjson::Value& obj = p["product"];
                if (obj.HasMember("sn") && obj.HasMember("price")) {
                    const rapidjson::Value& innerSn = obj["sn"];
                    const rapidjson::Value& innerPrice = obj["price"];

                    std::string sn = innerSn.GetString();
                    float price = innerPrice.GetDouble();
                    CCLOG("sn = '%s', price = %f", sn.c_str(), price);
                }
            }
     
        }
        
    } while (0);
  
    
}

void TestJsonScene::writeJson()
{
    std::string path = FileUtils::getInstance()->fullPathForFilename("/Users/Konvie/cocos/cocos/JsonParser/Resources/sale.json");
    
    rapidjson::Document doc;
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    
    // Generate the json objec's infomation.
    rapidjson::Value array(rapidjson::kArrayType);
    rapidjson::Value obj1(rapidjson::kObjectType);
    rapidjson::Value obj2(rapidjson::kObjectType);
    
    obj1.AddMember("name", "Hans", allocator);
    obj1.AddMember("age", 26, allocator);
    obj2.AddMember("name", "LiLi", allocator);
    obj2.AddMember("age", 38, allocator);
    
    array.PushBack(obj1, allocator);
    array.PushBack(obj2, allocator);
    
    doc.AddMember("sale", array, allocator);
    
    
    // Write to file.
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    
    std::string str = buffer.GetString();
    FILE* file = std::fopen(path.c_str(), "w");
    if (file) {
        fwrite(str.c_str(), str.length(), 1, file);
    }
    fclose(file);
    
    CCLOG("Writer stringbuffer: \n%s", buffer.GetString());
}

