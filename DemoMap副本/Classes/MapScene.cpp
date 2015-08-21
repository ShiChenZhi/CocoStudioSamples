//
//  MapScene.cpp
//  CocostudioUI
//
//  Created by Konvie Shaw on 15/8/10.
//


#include "MapScene.h"
#include "cocostudio/CocoStudio.h"
#include "CocosGUI.h"

#define MAP_BUTTON_TAG  1000


// 地图上建筑节点名称
const char* buildNames[3] =
{
    "red star",
    "green orb",
    "blue star",
};

void MapScene::onEnter()
{
    Scene::onEnter();
    MapInit();//初始化地图层
    MapAlertInit();//初始化提示框层
}


void MapScene::MapInit()
{
    //加载数据
    Node* map_root = CSLoader::createNode("level_map_layer.csb");
    mapLayer = (Layer*)map_root;
    ui::Helper::doLayout(map_root);
    addChild(map_root);
    
    //获取关卡建筑按钮层
    ui::Layout* button_layout = static_cast<ui::Layout*>(map_root->getChildByName("drag_panel")->getChildByName("button_panel"));
    for (int i = 0; i < button_layout->getChildren().size(); i++)
    {
        ui::Button* build_button = static_cast <ui::Button *>(button_layout->getChildren().at(i));
        build_button->setTag( MAP_BUTTON_TAG + i);
        build_button->addTouchEventListener(CC_CALLBACK_2(MapScene::buildTouchEvent, this));
    }
    
    //获取关闭游戏按钮
    ui::Button* back_button = (ui::Button*)(mapLayer->getChildByName("box_panel")->getChildByName("back_btn"));
    back_button->addTouchEventListener(CC_CALLBACK_2(MapScene::menuCloseCallback,this));
}

void MapScene ::buildTouchEvent(Ref* pSender, ui::Widget::TouchEventType type )
{
    if (type == ui::Widget::TouchEventType::ENDED)
    {
        // 被点击的关卡建筑对象
        ui::Button* build_button = dynamic_cast< ui::Button*>(pSender);
        int index = build_button->getTag() - MAP_BUTTON_TAG;
        
        //// 更新提示框层的显示
        ui::Layout* alert_panel = (ui::Layout*)mapLayer->getChildByName("alert_panel");
        alert_panel->setVisible(true);
        // 提示框层上的文本
        ui::Text* alert_text = dynamic_cast <ui::Text*>(alert_panel->getChildByName("alert_text"));
        alert_text->setColor(Color3B::BLACK);
        alert_text->setString(buildNames[index]);
    }
}

void MapScene::MapAlertInit()
{
    //获取提示框层
    ui::Layout* alert_panel = static_cast <ui::Layout *>(mapLayer->getChildByName("alert_panel"));
    //获取提示框层关闭按钮
    ui::Button* close_button = static_cast <ui::Button *>(alert_panel->getChildByName("close_btn"));
    //添加关闭按钮点击事件绑定
    close_button->addTouchEventListener(CC_CALLBACK_2(MapScene::MapAlertClose,this));
                                       
}

//当点击了提示框关闭按钮
void MapScene::MapAlertClose(cocos2d::Ref *pSender, ui::Widget::TouchEventType type)
{
    if (type == ui::Widget::TouchEventType::ENDED) //点击结束时
    {
        //获取提示框层
        ui::Layout* map_alert_root = static_cast <ui::Layout *>(mapLayer->getChildByName("alert_panel"));
        map_alert_root->setVisible( false);
    }
}

//游戏关闭按钮回调
void MapScene::menuCloseCallback(cocos2d::Ref *pSender, ui::Widget::TouchEventType type)
{
    if (type == ui::Widget::TouchEventType::ENDED)
    {
        Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
        exit(0);
#endif
    }
}

