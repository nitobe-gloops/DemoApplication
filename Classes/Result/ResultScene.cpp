#include "ResultScene.h"
#include "Home/HomeScene.h"

USING_NS_CC;

CCScene* ResultScene::scene()
{
    CCScene *scene = CCScene::create();
    ResultScene *layer = ResultScene::create();
    scene->addChild(layer);

    return scene;
}


// on "init" you need to initialize your instance
bool ResultScene::init()
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
                                        menu_selector(ResultScene::menuCloseCallback));

    pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    CCMenu* pMenuClose = CCMenu::create(pCloseItem, NULL);
    pMenuClose->setPosition(CCPointZero);
    this->addChild(pMenuClose, 1);

    CCLabelTTF* pLabel = CCLabelTTF::create("ResultScene", "Arial", 24);
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
                                        menu_selector(ResultScene::buttonOnClickCallBack));
    pNextItem->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    CCMenu* pMenuNext = CCMenu::create(pNextItem, NULL);
    pMenuNext->setPosition(CCPointZero);
    this->addChild(pMenuNext, 0);

    return true;
}


void ResultScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void ResultScene::buttonOnClickCallBack(CCObject* pSender)
{
	CCLog("DEMO::ResultScene#buttonOnClickCallBack() >> ボタン押下：画面遷移を実装予定");
	CCScene* nextScene = HomeScene::scene();
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->runWithScene(nextScene);

	// 遷移に特殊な画面効果をつける場合
//	CCTransitionScene *transitionScen = CCTransitionSplitCols::create( 3.0, nextScene );
//	CCDirector::sharedDirector()->replaceScene( transitionScen );
}
