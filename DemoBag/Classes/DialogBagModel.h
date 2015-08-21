//
//  DialogBagModel.h
//  DemoBag
//
//  Created by Konvie Shaw on 15/8/19.
//
//

#ifndef __DemoBag__DialogBagModel__
#define __DemoBag__DialogBagModel__

#include <vector>
#include "BagItemModel.h"


struct DialogBagModel
{
    //背包列表
    std::vector<BagItemModel> item_list;
    //背包上限
    int capacity_limit;
    
    //创建测试数据
    void createTestData(){
        
        capacity_limit = 24;// 初始背包上限至少需要6以满足2行，不然滚屏的滑块有bug
        
        // 装备测试数据
        for (int i = 0; i < 6; i++)
        {
            BagItemModel a;
            a.gridModel.type = BagItemGridModel::EQUIP;
            a.gridModel.icon_id = 100 + i;
            a.gridModel.grid_bg_color = i % 5 + 1;
            a.gridModel.level = i+1;
            a.gridModel.is_max_level = false;
            
            a.name = "equipment";
            a.isDebris = false;
            
            if(i ==4){ // 测试脆片
                a.isDebris = true;
                a.name = "装备碎片";
            }
            
            if(i == 5){ // 测试满级
                a.gridModel.is_max_level = true;
                a.name = "悯生剑";
            }
            
            item_list.push_back(a);
        }
        
        // 物品测试数据
        for (int i = 0; i < 6; i++)
        {
            BagItemModel a;
            a.gridModel.type = BagItemGridModel::OTHER;
            a.gridModel.icon_id = 1 + i;
            a.gridModel.grid_bg_color = 1;
            a.gridModel.num = 13 + i/2;
            a.gridModel.level = -1;
            a.gridModel.is_max_level = false;
            
            a.name = "item";
            a.isDebris = false;
            
            item_list.push_back(a);
        }
    }
    
    //从模型层获取数据
    void createFromModel();
};


#endif /* defined(__DemoBag__DialogBagModel__) */
