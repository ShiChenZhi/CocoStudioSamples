//
//  MapScene.h
//  CocostudioUI
//
//  Created by Konvie Shaw on 15/8/10.
//
//

#ifndef __CocostudioUI__MapScene__
#define __CocostudioUI__MapScene__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;

class MapScene : public Scene
{
public :
    virtual void onEnter();
    
protected :
    Layer* mapLayer;

    // 地图层
    void MapInit();
    void buildTouchEvent(Ref* pSender, ui::Widget::TouchEventType type);
    // 提示框层
    void MapAlertInit();
    void MapAlertClose(Ref* pSender, ui::Widget::TouchEventType type);
    
    //游戏关闭按钮回调
    void menuCloseCallback(Ref* pSender, ui::Widget::TouchEventType type);
};

#endif /* defined(__CocostudioUI__MapScene__) */
