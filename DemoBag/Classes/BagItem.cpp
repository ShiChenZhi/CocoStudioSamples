//
//  BagItem.cpp
//  DemoBag
//
//  Created by Konvie Shaw on 15/8/19.
//
//

#include "BagItem.h"
#include "cocostudio/CocoStudio.h"
using namespace ui;

static const std::string TEXT_KONG = "\xE7\xA9\xBA";//空

bool BagItem::init()
{
    bool bRet = false;
    do {
        Node::init();
        Node* node = CSLoader::createNode("res/bagItem.csb");
        this->addChild(node);
        
        btn = (ImageView*) node->getChildByName("backgroud");
        auto center_x = btn->getContentSize().width / 2;
        auto center_y = btn->getContentSize().height / 2;
        
        grid = BagItemGrid::create();
        grid->setPosition(Vec2(center_x, center_y + 20));
        btn->addChild(grid);
        
        name_label = (Text*)node->getChildByName("name");
        
        isSelected_sp = Sprite::create("img/img_xuanzhong.png");
        isSelected_sp->setPosition(center_x, center_y);
        this->addChild(isSelected_sp);
        setSelected(false);
        
        sp_debris = (Sprite*)node->getChildByName("flag_debris");
        already_use = (Sprite*)node->getChildByName("flag_beEquiped");

    
        bRet = true;
    } while (0);
    
    return bRet;
}

void BagItem::setupBagItem(BagItemModel model)
{
    view_model = model;
    
    grid->setupBagItemGrid(model.gridModel);
    if (model.name != "")
        name_label->setString(model.name);
    else
        name_label->setString(TEXT_KONG);
    
    sp_debris->setVisible(model.isDebris);
    already_use->setVisible(model.isEquiped);
   
}

void BagItem::setSelected(bool isSelected)
{
    this->isSelected_ = isSelected;
    isSelected_sp->setVisible(isSelected);
}

int64_t BagItem::get_sno()
{
    return view_model.sno;
}

int BagItem::get_id()
{
    int id = view_model.gridModel.icon_id;
    
    // 肮脏的代码，由于碎片的icon_id是合成后的装备的icon_id。
    // 所以添加了一个多余的字段，用于获取其原始id
    if (view_model.isDebris == true)
    {
        id = view_model.debris_id;
    }
    
    return id;
}



