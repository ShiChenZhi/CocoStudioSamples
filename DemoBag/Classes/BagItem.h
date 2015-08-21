//
//  BagItem.h
//  DemoBag
//
//  Created by Konvie Shaw on 15/8/19.
//
//

#ifndef __DemoBag__BagItem__
#define __DemoBag__BagItem__

#include "cocos2d.h"
#include "BagItemModel.h"
USING_NS_CC;

//背包中的物品item（长方形），包含BagItemGrid以及一些额外信息(名字，是否已装备等)
class BagItem : public Node
{
public:
    CREATE_FUNC(BagItem);
    virtual bool init();
    void setupBagItem(BagItemModel model);
    
    void setSelected(bool isSelected);
    bool isSelected(){ return isSelected_; }
    
    ui::ImageView* getBtn(){ return btn; }
    
    int64_t get_sno();
    int get_id();
    
private:
    ui::ImageView* btn; // Itself can be clicket.
    ui::Text* name_label;
    bool isSelected_;
    Sprite* isSelected_sp;
    
    Sprite* sp_debris;
    Sprite* already_use;
    
private:
    BagItemModel view_model;
    BagItemGrid* grid;
    
};

#endif /* defined(__DemoBag__BagItem__) */
