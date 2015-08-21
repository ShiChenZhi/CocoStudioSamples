//
//  BagItemGrid.h
//  DemoBag
//
//  Created by Konvie Shaw on 15/8/19.
//
//

#ifndef __DemoBag__BagItemGrid__
#define __DemoBag__BagItemGrid__

#include "cocos2d.h"
#include "CocosGUI.h"
USING_NS_CC;

struct BagItemGridModel
{
    enum ItemType
    {
        EQUIP, //装备，需要显示等级，
        OTHER, //包括道具、宝箱和钥匙，需要显示数量
    };
    
    ItemType type; //物品的类型
    int icon_id;   //道具的id，id和图片资源一一对应
    
    int level;     //如果是装备，显示等级
    int grid_bg_color; //装备的稀有度通过框框的背景色表示
    bool is_max_level; //装备有等级上限，满级会显示max标志
    
    int num;           //其他类型的物品需要显示数量
};

// 物品节点（道具上正方形的格子），对应一件道具或装备
class BagItemGrid : public Node{
public:
    CREATE_FUNC(BagItemGrid);
    virtual bool init();
    void setupBagItemGrid(BagItemGridModel model);
    
protected:
    ui::ImageView* btn;
    Sprite* equip_icon;
    Sprite* lv_flag;
    Sprite* lv_max_flag;
    ui::TextAtlas* lable_level;
};


#endif /* defined(__DemoBag__BagItemGrid__) */
