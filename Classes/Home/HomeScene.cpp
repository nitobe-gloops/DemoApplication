#include "HomeScene.h"
#include "Map/MapScene.h"

USING_NS_CC;

CCScene* HomeScene::scene()
{
    CCScene *scene = CCScene::create();
    HomeScene *layer = HomeScene::create();
    scene->addChild(layer);

    return scene;
}


// on "init" you need to initialize your instance
bool HomeScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    // 背景画像を設定する
    setBackGroundSprite();

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HomeScene::menuCloseCallback));

    pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    CCMenu* pMenuClose = CCMenu::create(pCloseItem, NULL);
    pMenuClose->setPosition(CCPointZero);
    this->addChild(pMenuClose, 1);

    CCLabelTTF* pLabel = CCLabelTTF::create("HomeScene", "Arial", 24);
    pLabel->setColor(ccc3((GLubyte)0,(GLubyte)0,(GLubyte)0));
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
                                        menu_selector(HomeScene::buttonOnClickCallBack));
    pNextItem->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    CCMenu* pMenuNext = CCMenu::create(pNextItem, NULL);
    pMenuNext->setPosition(CCPointZero);
    this->addChild(pMenuNext, 0);

    return true;
}


/**
 * 背景画像を設定する
 * */
void HomeScene::setBackGroundSprite() {
	// 画面サイズ取得
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	// plistを読み込み
	CCSpriteFrameCache* frameCacheBG = CCSpriteFrameCache::sharedSpriteFrameCache();
	frameCacheBG->addSpriteFramesWithFile("SpriteSheets/DummyBackground02.plist");		// plistのパスを指定

	CCLOG("DEMO::HomeScene#setBackGroundSprite() >> plist Load!");

	//
	CCSprite* sprite = CCSprite::createWithSpriteFrameName("back_Ex03.png");		// plist内のkey(ファイル名)を指定
	sprite->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
	this->addChild(sprite);
}


void HomeScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void HomeScene::buttonOnClickCallBack(CCObject* pSender)
{
	CCLog("DEMO::HomeScene#buttonOnClickCallBack() >> ボタン押下");
	CCScene* nextScene = MapScene::scene();
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->runWithScene(nextScene);

	// 遷移に特殊な画面効果をつける場合
//	CCTransitionScene *transitionScen = CCTransitionSplitCols::create( 3.0, nextScene );
//	CCDirector::sharedDirector()->replaceScene( transitionScen );
}
