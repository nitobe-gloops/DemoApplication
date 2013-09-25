#include "GameScene.h"
#include "Result/ResultScene.h"

USING_NS_CC;

#define MOTION_STREAK_TAG 10

CCScene* GameScene::scene()
{
    CCScene *scene = CCScene::create();
    GameScene *layer = GameScene::create();
    scene->addChild(layer);

    return scene;
}


// on "init" you need to initialize your instance
bool GameScene::init()
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
                                        menu_selector(GameScene::menuCloseCallback));

    pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    CCMenu* pMenuClose = CCMenu::create(pCloseItem, NULL);
    pMenuClose->setPosition(CCPointZero);
    this->addChild(pMenuClose, 1);

    CCLabelTTF* pLabel = CCLabelTTF::create("GameScene", "Arial", 24);
    pLabel->setColor(ccc3((GLubyte)0,(GLubyte)0,(GLubyte)0));
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    this->addChild(pLabel, 1);

    // 線引きのガイダンスを表示
    int fontSize = CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height/320.0f * 18;
    CCLabelTTF *label = CCLabelTTF::create("指でなぞったラインを CCMotionStreak で描画します", "Helvetica", /*fontSize*/ 24);
    label->setColor(ccc3((GLubyte)0,(GLubyte)0,(GLubyte)0));
    label->setPosition(ccp(visibleSize.width / 2, visibleSize.height - label->getContentSize().height * 4));
    this->addChild(label);

    this->setTouchEnabled(true);	// タッチイベントを有効化
    this->setTouchMode(kCCTouchesOneByOne);		// シングルタッチ

//    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
//    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//    this->addChild(pSprite, 0);

    // 次の画面へ遷移するボタン
    CCMenuItemImage *pNextItem = CCMenuItemImage::create(
                                        "HelloWorld.png",
                                        "HelloWorld_02.png",
                                        this,
                                        menu_selector(GameScene::buttonOnClickCallBack));
    pNextItem->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    CCMenu* pMenuNext = CCMenu::create(pNextItem, NULL);
    pMenuNext->setPosition(CCPointZero);
    this->addChild(pMenuNext, 0);

    return true;
}


/**
 * 背景画像を設定する
 * */
void GameScene::setBackGroundSprite() {
	// 画面サイズ取得
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	// plistを読み込み
	CCSpriteFrameCache* frameCacheBG = CCSpriteFrameCache::sharedSpriteFrameCache();
	frameCacheBG->addSpriteFramesWithFile("SpriteSheets/DummyBackground02.plist");		// plistのパスを指定

	CCLOG("DEMO::GameScene#setBackGroundSprite() >> plist Load!");

	//
	CCSprite* sprite = CCSprite::createWithSpriteFrameName("back_Ex03.png");		// plist内のkey(ファイル名)を指定
	sprite->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
	this->addChild(sprite);
}

void GameScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void GameScene::buttonOnClickCallBack(CCObject* pSender)
{
	CCLog("DEMO::GameScene#buttonOnClickCallBack() >> ボタン押下：画面遷移を実装予定");
	CCScene* nextScene = ResultScene::scene();
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->runWithScene(nextScene);

	// 遷移に特殊な画面効果をつける場合
//	CCTransitionScene *transitionScen = CCTransitionSplitCols::create( 3.0, nextScene );
//	CCDirector::sharedDirector()->replaceScene( transitionScen );
}


/**
 * タッチイベント 開始
 * CCMotionStreak：
 *   ・指定した画像を、ポイントの集合で示すパス上に連ねて表示する
 *   ・各ポイントのパスに沿って画像を回転して配置する(ポイントが充分に密であれば、なめらかな曲線に見える)
 *   ・時間経過とともに画像がフェードアウトする
 *
 * */
bool GameScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {

	this->removeChildByTag(MOTION_STREAK_TAG, true);	// …？

	CCPoint point = this->convertTouchToNodeSpace(pTouch);		// 座標を取得

	//CCMotionStreak::create(フェードアウトSec, ???, ???, 色, 画像)
	CCMotionStreak* pStreak = CCMotionStreak::create(5.0f, 1.0f, 10.0f, ccc3(255, 255, 0), "line.png");
	pStreak->setPosition(point);
	this->addChild(pStreak, 5, MOTION_STREAK_TAG);	// Tgaに固定値(MOTION_STREAK_TAG=10)を指定

	return true;
}

/**
 * タッチイベント 移動中(？)
 * */
void GameScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {
	CCPoint point = this->convertTouchToNodeSpace(pTouch);		// 座標を取得
	// Tag番号から対象のオブジェクト取得
	CCMotionStreak* pStreak = (CCMotionStreak*)this->getChildByTag(MOTION_STREAK_TAG);
	// 移動先にオブジェクトを表示させる
	pStreak->setPosition(point);
}
