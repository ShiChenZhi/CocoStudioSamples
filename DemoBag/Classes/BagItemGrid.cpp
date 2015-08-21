//
//  BagItemGrid.cpp
//  DemoBag
//
//  Created by Konvie Shaw on 15/8/19.
//
//

#include "BagItemGrid.h"
using namespace ui;

bool BagItemGrid::init()
{
    bool bRet = false;
    do {
        Node::init();
        
        btn = ImageView::create("img/item_bg_default.png");
        addChild(btn);
        
        equip_icon = Sprite::create();
        equip_icon->setPosition(Vec2(btn->getContentSize().width / 2, btn->getContentSize().height / 2));
        btn->addChild(equip_icon);
        
        lv_flag = Sprite::create("img/img_text_lv.png");
        lv_flag->setPosition(88 + 15, 10 + 5);
        btn->addChild(lv_flag);
        
        lable_level = TextAtlas::create("0123456789", "img/atlas_digit.png", 131/10, 18, "0");
        lable_level->setPosition(Vec2(88 + 15, 10 + 5));
        lable_level->setAnchorPoint(Vec2(1, 0.5));
        btn->addChild(lable_level);
        
        lv_max_flag = Sprite::create("img/img_text_lv_max.png");
        lv_max_flag->setPosition(lable_level->getPosition());
        lv_max_flag->setAnchorPoint(Vec2(1, 0.5));
        btn->addChild(lv_max_flag);
        
        bRet = true;
    } while (0);

    return bRet;
}

void BagItemGrid::setupBagItemGrid(BagItemGridModel model)
{
    // 如果是装备，装备的品质通过底板背景表示
    switch (model.grid_bg_color)
    {
        case 1:
            btn->loadTexture("img/item_bg_default.png");
            break;
        case 2:
            btn->loadTexture("img/item_bg_yellow.png");
            break;
        case 3:
            btn->loadTexture("img/item_bg_lv.png");  // what's this???
            break;
        case 4:
            btn->loadTexture("img/item_bg_green.png");
            break;
        case 5:
            btn->loadTexture("img/item_bg_purple.png");
            break;
        default:
            break;
    }
    
    //默认不显示满级标识
    lv_max_flag->setVisible(false);
    
    if (model.icon_id != -1) { //有id说明不是空格子
        //设置图标icon
        auto equip_icon_path = StringUtils::format("img/icon/%d.png", model.icon_id);
        equip_icon->setTexture(equip_icon_path);
        
        if (model.type == BagItemGridModel::EQUIP) {
            // 设置等级或者满级标识
            lable_level->setString(StringUtils::format("%d", model.level));
            lv_flag->setPosition(lable_level->getPositionX() - lable_level->getContentSize().width - 15, lable_level->getPositionY());
            
            if (model.is_max_level)//注意：满级会设置等级文字为不可见，装备id为-1也会设置为不可见
            {
                lv_max_flag->setVisible(true);
                lv_flag->setVisible(false);
                lable_level->setVisible(false);
            }
            else{
                lv_flag->setVisible(true);
                lable_level->setVisible(true);
            }
        }
        else { // 道具需要显示数量
            lv_flag->setVisible(false);
            lable_level->setVisible(true);
            lable_level->setString(StringUtils::format("%d", model.num));
        }
        
    }
    else {
        equip_icon->setTexture(nullptr);
        //equip_icon->setTextureRect(Rect::ZERO);
        
        lv_flag->setVisible(false);
        lable_level->setVisible(false);
    }
}




