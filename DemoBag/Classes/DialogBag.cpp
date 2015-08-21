//
//  DialogBag.cpp
//  DemoBag
//
//  Created by Konvie Shaw on 15/8/19.
//
//

#include "DialogBag.h"
#include "DialogBagModel.h"
#include "cocostudio/CocoStudio.h"
using namespace ui;

DialogBag::DialogBag():
model_(NULL)
{
}

DialogBag::~DialogBag()
{
    CC_SAFE_DELETE(model_);
}

bool DialogBag::init()
{
    bool bRet = false;
    do {
        Layer::init();
        
        slider_bar_min_pos_y = 0;
        slider_bar_area = 0;
        
        auto dialog = CSLoader::createNode("dialogBag.csb");
        bindingNode(dialog);
        this->addChild(dialog);
        
        bRet = true;
    } while (0);
    
    return bRet;
}

void DialogBag::bindingNode(Node *dialog)
{
    //按钮
    btn_close = (Button*)dialog->getChildByName("btn_back2");
    btn_back = (Button*)dialog->getChildByName("btn_back");
    btn_close->addTouchEventListener(CC_CALLBACK_2(DialogBag::onBtnCallback, this));
    btn_back->addTouchEventListener(CC_CALLBACK_2(DialogBag::onBtnCallback, this));
    
    capacity_text = (Text*)dialog->getChildByName("number");
    
    //滚动层
    sv = (ScrollView*)dialog->getChildByName("ScrollView_1");
    sv->addEventListener(CC_CALLBACK_2(DialogBag::onSVCallback, this));
    sv->addTouchEventListener(CC_CALLBACK_2(DialogBag::onSVTouch, this));
    
    //滑块
    slider_base = (ImageView*)dialog->getChildByName("slider_base");
    slider_bar = (ImageView*)slider_base->getChildByName("slider_bar");
}

void DialogBag::setupDialogBag(DialogBagModel *model)
{
    CC_SAFE_DELETE(model_);
    model_ = model;

    // 设置背包容量的文字---------------------------------------------------------------
    int capacity = model_->capacity_limit;
    int size = (int)model_->item_list.size();
    capacity_text->setString(StringUtils::format("%d/%d", size, capacity));

    // 根据item的数量动态设置其在背包中的位置---------------------------
    int width = 760; // 滚动层的宽
    int height = 384; // 滚动层的高
    int padding = 9;//只是为了对坐标，并不是真正的内边距
    int count_per_row = 5;//每行的个数
    
    float row_width = 142 + padding; // 142 道具宽
    float column_heigth = height*0.5;  // 每页显示2行道具;
    
    // 空格子也要显示
    int max = (capacity > size) ? capacity : size;
    // 计算总行数
    float total_column = (max - 1) / count_per_row + 1;
    //计算内容区的高度
    int container_hight = total_column * column_heigth;
    container_hight = (container_hight > height) ? container_hight : height;
    sv->setInnerContainerSize(Size(width, container_hight));
    
    // 更新 item -------------------------------------------------------------------------
    int old_item_list_size = (int)item_list.size();//默认为0
    
    // 如果有多余的Item，删除多余的item
    if (old_item_list_size > max)
    {
        for (int idx = old_item_list_size; idx > max; idx--) // 倒着删
        {
            auto item = item_list.at(idx-1);
            item->removeFromParent();
            item_list.popBack();
        }
    }
    
    //更新或者创建item
    for (int idx = 0; idx < max; idx++)
    {
        int row = idx % count_per_row;
        int column = idx / count_per_row;
        
        BagItem* item;
        if (old_item_list_size > idx)
        {
            //复用这个item
            item = item_list.at(idx);
        }
        else{
            //不够就创建
            item = BagItem::create();
            sv->addChild(item);
            item_list.pushBack(item);
        }
        
        if (idx < size)
        {
            BagItemModel data = model_->item_list[idx];
            item->setupBagItem(data);
        }
        else if (idx < capacity) //空格子
        {
            BagItemModel data;
            data.createGridNothing();
            item->setupBagItem(data);
        }
        
        //计算并设置位置
        int x = padding/2 + row_width * row;
        int y = padding/2 + container_hight - (column + 1)*(column_heigth);
        item->setPosition(x, y);
    }
        
    // 计算滑块的大小和位置 -------------------------------------------------------------
    float slider_orign_height = slider_base->getContentSize().height;
    float slider_bar_height = slider_orign_height * (2 / total_column); // 每页2行道具
    slider_bar->setContentSize(Size(11, slider_bar_height));
    
    this->slider_bar_min_pos_y = slider_bar_height;
    this->slider_bar_area = slider_orign_height - slider_bar_height;
    
    if (slider_bar->getPositionY() < slider_bar_min_pos_y)
    {
        slider_bar->setPositionY(slider_bar_min_pos_y);
    }
    
}

#pragma mark - 回调函数
void DialogBag::onBtnCallback(Ref *object, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        if (object == btn_back || object == btn_close)
        {
            this->removeFromParent();
        }
    }
}

void DialogBag::onSVCallback(Ref *, ScrollView::EventType type)
{
    if (type == ScrollView::EventType::SCROLLING)
    {
        // 根据InnerContainer的滚动更新滑块的位置
        float current_pos = -sv->getInnerContainer()->getPositionY();
        float pos_area = sv->getInnerContainerSize().height - sv->getContentSize().height;
        
        //由于ScrollView开启了回弹效果，所以他的位置会超出范围，所以需要修正
        if (current_pos < 0)
            current_pos = 0;
        else if (current_pos > pos_area)
            current_pos = pos_area;
        
        
        float percent = current_pos / pos_area;
        
        //设置滑块的位置
        if (slider_bar_area != 0)
        {
            slider_bar->setPositionY(slider_bar_min_pos_y + slider_bar_area*percent);
        }
    }
}

void DialogBag::onSVTouch(Ref *object, Widget::TouchEventType type)
{
    // 由于按钮的点击事件会屏蔽ScrollView的滚动事件。即点击在按钮上的时候是不能拖动滚动层的。
    // 所以背包中的item并不是button。而是自己实现的点击判定
    // 处理背包中item的点击，模拟按钮的点击效果。
    
    float dis_limit = 10; // 判断是否点击的允许范围
    
    if (type == Widget::TouchEventType::ENDED)
    {
        auto pos = sv->getTouchEndPosition();
        //CCLOG("ended x = %f , y = %f", pos.x, pos.y);
        auto pos_began = sv->getTouchBeganPosition();
        float dis = pos.distance(pos_began);
        
        for (auto item : item_list)
        {
            auto btn = item->getBtn();
            btn->loadTexture("img/item_common_bg.png"); //设置所有item为非选中状态
            
            if (dis < dis_limit && btn->hitTest(pos)){//如果移动距离小于10，判断为1次点击操作
                log("on click item : sno = %lld , id = %d", item->get_sno(), item->get_id());
                onItemClick(item->get_sno(), item->get_id());
            }
        }
    }
    
    if (type == Widget::TouchEventType::BEGAN)
    {
        auto pos = sv->getTouchBeganPosition();
        //CCLOG("began x = %f , y = %f", pos.x, pos.y);
        for (auto item : item_list)
        {
            auto btn = item->getBtn();
            if (btn->hitTest(pos))
            {
                //设置点中的item为点中状态
                btn->loadTexture("img/item_common_click.png");
            }
        }
    }
    
    if (type==Widget::TouchEventType::MOVED)
    {
        auto pos = sv->getTouchMovePosition();
        auto pos_began = sv->getTouchBeganPosition();
        float dis = pos.distance(pos_began);
        //CCLOG("moved x = %f , y = %f", pos.x, pos.y);
        
        // WARNING! 触屏的 ENDED 事件并非肯定会执行，比如抬起时位置超出了滚屏监听范围。
        // 所以move中也需要循环遍历，恢复原始图片。
        if (dis > dis_limit) {
            for (auto item : item_list)
            {
                auto btn = item->getBtn();
                btn->loadTexture("img/item_common_bg.png"); //设置所有item为非选中状态
            }
        }
    }
}

void DialogBag::onItemClick(int sno, int id)
{
    if (sno <= 0 && id <= 0) //肮脏的代码，约定(sno<=0 && id<=0)为空格子
    {
        CCLOG("空格子");
        return;
    }
    
    if (sno<=0 && id>0)//肮脏的代码，约定sno<=0即为道具
    {
        //打开道具详情界面
        CCLOG("打开道具详情界面");
        {
            /*
            auto map = ModelPlayer::getInstance()->getPropMap();
            auto prop = map[id];
            int type = prop->getType();
            
            if (type == ModelProp::EQUIPMENT_DEBRIS){
                //点击装备碎片
                CCLOG("ModelProp::EQUIPMENT_DEBRIS");
            }
            
            else if (type == ModelProp::KEY)
            {
                //点击钥匙
                CCLOG("ModelProp::KEY");
            }
            
            else if (type == ModelProp::BOX)
            {
                //点击箱子
                CCLOG("ModelProp::BOX");
            }
            
            else if (type == ModelProp::EVOLVE_PULIIC)
            {
                //点击通用强化角色道具
                CCLOG("ModelProp::EVOLVE_PULIIC");
            }
            else if (type == ModelProp::EVOLVE_PRIVATE)
            {
                //点击私有强化角色道具
                CCLOG("ModelProp::EVOLVE_PRIVATE");
            }
            else{
                //其他
            }
            */
        }
    }
    
    if (sno > 0 && id > 0)//装备
    {
        //打开装备详情界面
        CCLOG("打开装备详情界面");
        /*
        DialogEquipDetail* dialog = DialogEquipDetail::create();
        
        DialogEquipDetailModel* model=new DialogEquipDetailModel();
        model->createFromModel(sno);
        dialog->setupDialogEquipDetail(model);
        this->addChild(dialog, 50);
         */
    }
}


