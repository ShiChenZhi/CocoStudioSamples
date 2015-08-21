//
//  ImageViewer.h
//  SampleImageViewer
//
//  Created by Konvie Shaw on 15/8/14.
//
//

#ifndef __SampleImageViewer__ImageViewer__
#define __SampleImageViewer__ImageViewer__

#include "cocos2d.h"
#include "CocosGUI.h"
USING_NS_CC;

class ImageViewer : public Scene
{
public:
    virtual void onEnter();
    
protected:
    Node* root;
    
    int currentPage;
    int lastPage;
    
    void pageInit();
     //页面切换回调事件
    void pageViewEvent(Ref* pSender, ui::PageView::EventType type);
    
};

#endif /* defined(__SampleImageViewer__ImageViewer__) */
