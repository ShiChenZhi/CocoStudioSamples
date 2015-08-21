//
//  DialogBag.h
//  DemoBag
//
//  Created by Konvie Shaw on 15/8/19.
//
//

#ifndef __DemoBag__DialogBag__
#define __DemoBag__DialogBag__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "BagItem.h"
#include "DialogBagModel.h"
USING_NS_CC;


class DialogBag : public Layer
{
public:
    CREATE_FUNC(DialogBag);
    DialogBag();
    virtual ~DialogBag();
    // 界面初始化
    virtual bool init();
    //virtual void onEnter();
    //virtual void onExit();
    
    // 设置界面显示内容
    void setupDialogBag(DialogBagModel* model);
    // 绑定 cocos ui 到程序控件
    void bindingNode(Node* dialog);
    
    void onBtnCallback(Ref *object, ui::Widget::TouchEventType type);
    
    //ScrollView滚动事件的回调
    void onSVCallback(Ref*, ui::ScrollView::EventType type);
    //ScrollView触摸事件的回调
    void onSVTouch(Ref *object, ui::Widget::TouchEventType type);
    
    //背包中某一个item被点击
    void onItemClick(int sno, int id);
    
    //该函数响应背包内容更新的事件
    void doUpdateViewEvent(EventCustom* event);
    
    
private: // UI
    ui::Button* btn_close; // 关闭按钮
    ui::Button* btn_back; // 返回按钮
    
    ui::ScrollView* sv; // 滚动层
    ui::ImageView* slider_base; // 滑块底部
    ui::ImageView* slider_bar; // 滑块
    
    ui::Text* capacity_text; // 显示背包容量的文字
    
private:
    float slider_bar_min_pos_y; // 滑块最小y坐标 （滑块锚点 0.5, 1）
    float slider_bar_area; // 滑块y轴可移动的距离的范围
    
    DialogBagModel* model_;
    Vector<BagItem*> item_list; // 背包item的列表
    EventListenerCustom* bag_updateEventListener;//用于监听背包内容更新
};
#endif /* defined(__DemoBag__DialogBag__) */
