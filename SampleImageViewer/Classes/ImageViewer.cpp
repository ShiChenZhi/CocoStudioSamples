//
//  ImageViewer.cpp
//  SampleImageViewer
//
//  Created by Konvie Shaw on 15/8/14.
//
//

#include "ImageViewer.h"
#include "cocostudio/CocoStudio.h"
using namespace ui;


//图片路径
const char * page_image_textures[4] =
{
    "CocoStudio_AnimationEditor.png" ,
    "CocoStudio_DataEditor.png" ,
    "CocoStudio_SceneEditor.png" ,
    "CocoStudio_UIEditor.png" ,
};

void ImageViewer::onEnter()
{
    Scene::onEnter();
    
    lastPage = currentPage = 1;
    
    //Size visize = Director::getInstance()->getVisibleSize();
    root = CSLoader::createNode("MainScene.csb");
    //root->setContentSize(visize);
    Helper::doLayout(root);
    addChild(root);
    
    pageInit(); //初始化页面
    
}

void ImageViewer::pageInit()
{
    //获取page_panel对象
    Layout* page_layout = dynamic_cast <Layout *>(root->getChildByName( "page_panel"));
    Size pageSize = page_layout->getLayoutSize();
    
    //创建一个PageView对象
    PageView* pageView =  PageView::create();
    pageView->setTouchEnabled(true);
    pageView->setSize(pageSize);
    
    //添加4个page
    for ( int i = 0; i < 4; ++i)
    {
        Layout * layout = Layout ::create();
        layout->setSize(pageSize);
        
        ImageView * imageView = ImageView ::create(); //在每个page下添加一张图片.
        imageView->setTouchEnabled( true );
        imageView->loadTexture(page_image_textures[i]);
        imageView->setPosition( Vec2(pageSize.width * 0.5, pageSize.height * 0.5));
        layout->addChild(imageView);
        
        pageView->addPage(layout);
    }
    
    //绑定页面切换事件监听
    pageView->addEventListener(CC_CALLBACK_2(ImageViewer::pageViewEvent, this));
    page_layout->addChild(pageView);
}

// 页面切换监听事件
void ImageViewer::pageViewEvent(Ref *pSender, PageView::EventType type)
{
    PageView* pageView = dynamic_cast <PageView *>( pSender);
    int page = (int)pageView->getCurPageIndex() + 1; //获取当前页数

    Text* page_txt = dynamic_cast <Text *>(root->getChildByName("page_text" ));
    page_txt->setString("page " + Value(page).asString());
    
    
    // 设置下面换页指示器
    currentPage = page;
    Node* bottom_layout = root->getChildByName("bottom_panel");
    bottom_layout->getChildByTag(lastPage)->setVisible(false);
    bottom_layout->getChildByTag(currentPage)->setVisible(true);
    lastPage = currentPage;
}

