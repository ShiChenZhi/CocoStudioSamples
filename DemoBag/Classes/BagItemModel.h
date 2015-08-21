//
//  BagItemModel.h
//  DemoBag
//
//  Created by Konvie Shaw on 15/8/19.
//
//

#ifndef __DemoBag__BagItemModel__
#define __DemoBag__BagItemModel__

#include "BagItemGrid.h"

class ModelEquipment;
class ModelProp;

struct BagItemModel
{
    int64_t sno; //装备有唯一序列号，道具为0
    std::string name;
    bool isDebris;
    
    bool isEquiped;
    bool isSelected; //用于装备选择界面,理论上应该移到子类中去。
    
    BagItemGridModel gridModel;
    //创建一个空的item
    void createGridNothing();
    //根据装备的相关数据创建界面model，从数据model填充界面model
    void createFromEquipModel(ModelEquipment* item);
    //根据道具的相关数据创建界面model，从数据model填充界面model
    void createFromPropModel(ModelProp* item);
    
    //肮脏的代码，由于装备碎片的icon_id是合成后的装备的icon_id，再在左上角加一个碎片的碎。
    //所以添加了一个多余的字段，用于获取其原始id
    int debris_id;
};

#endif /* defined(__DemoBag__BagItemModel__) */
