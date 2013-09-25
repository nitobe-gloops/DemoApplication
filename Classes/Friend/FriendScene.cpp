#include "FriendScene.h"

USING_NS_CC;

CCScene* FriendScene::scene()
{
    CCScene *scene = CCScene::create();
    FriendScene *layer = FriendScene::create();
    scene->addChild(layer);

    return scene;
}


// on "init" you need to initialize your instance
bool FriendScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(FriendScene::menuCloseCallback));

    pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    CCMenu* pMenuClose = CCMenu::create(pCloseItem, NULL);
    pMenuClose->setPosition(CCPointZero);
    this->addChild(pMenuClose, 1);

    CCLabelTTF* pLabel = CCLabelTTF::create("FriendScene", "Arial", 24);
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    this->addChild(pLabel, 1);

//    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
//    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//    this->addChild(pSprite, 0);

    // 次の画面へ遷移するボタン
    CCMenuItemImage *pNextItem = CCMenuItemImage::create(
                                        "HelloWorld.png",
                                        "HelloWorld_02.png",
                                        this,
                                        menu_selector(FriendScene::buttonOnClickCallBack));
    pNextItem->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    CCMenu* pMenuNext = CCMenu::create(pNextItem, NULL);
    pMenuNext->setPosition(CCPointZero);
    this->addChild(pMenuNext, 0);

    return true;
}


void FriendScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void FriendScene::buttonOnClickCallBack(CCObject* pSender)
{
	CCLog("FriendScene::buttonOnClickCallBack >> ボタン押下：画面遷移を実装予定");
//	// TODO:次の画面のScene
//	CCScene* nextScene = FriendScene::scene();
//	// 画面遷移のアニメーション
//	CCTransitionScene *transitionScen = CCTransitionSplitCols::create( 3.0, nextScene );
//
//	CCDirector::sharedDirector()->replaceScene( transitionScen );
}
