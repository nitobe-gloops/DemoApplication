#include "MapScene.h"
#include "AppPlatform.h"
#include "Game/DemoScene.h"

USING_NS_CC;

CCScene* MapScene::scene()
{
    CCScene *scene = CCScene::create();
    MapScene *layer = MapScene::create();
    scene->addChild(layer);

    return scene;
}


// on "init" you need to initialize your instance
bool MapScene::init()
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
                                        menu_selector(MapScene::menuCloseCallback));

    pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    CCMenu* pMenuClose = CCMenu::create(pCloseItem, NULL);
    pMenuClose->setPosition(CCPointZero);
    this->addChild(pMenuClose, 1);

    CCLabelTTF* pLabel = CCLabelTTF::create("MapScene", "Arial", 24);
    pLabel->setColor(ccc3((GLubyte)0,(GLubyte)0,(GLubyte)0));
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    this->addChild(pLabel, 1);

    // 線引きのガイダンスを表示
    int fontSize = CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height/320.0f * 18;
    CCLabelTTF *label = CCLabelTTF::create("指でなぞったラインを CCRenderTexture で描画します", "Helvetica",  /*fontSize*/ 24);
    label->setColor(ccc3((GLubyte)0,(GLubyte)0,(GLubyte)0));
    label->setPosition(ccp(visibleSize.width / 2, visibleSize.height - label->getContentSize().height * 4 ));
    this->addChild(label);

    this->setTouchEnabled(true);	// タッチイベントを有効化
    this->setTouchMode(kCCTouchesOneByOne);		// シングルタッチ

    pBrush = CCSprite::create("brush.png");
    pBrush->retain();

//    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
//    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//    this->addChild(pSprite, 0);

    // 次の画面へ遷移するボタン
    CCMenuItemImage *pNextItem = CCMenuItemImage::create(
                                        "HelloWorld.png",
                                        "HelloWorld_02.png",
                                        this,
                                        menu_selector(MapScene::buttonOnClickCallBack));
    pNextItem->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    CCMenu* pMenuNext = CCMenu::create(pNextItem, NULL);
    pMenuNext->setPosition(CCPointZero);
    this->addChild(pMenuNext, 0);

    return true;
}


/**
 * 背景画像を設定する
 * */
void MapScene::setBackGroundSprite() {
	// 画面サイズ取得
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	// plistを読み込み
	CCSpriteFrameCache* frameCacheBG = CCSpriteFrameCache::sharedSpriteFrameCache();
	frameCacheBG->addSpriteFramesWithFile("SpriteSheets/DummyBackground02.plist");		// plistのパスを指定

	AppPlatform::outputDebugLog("MapScene", "setBackGroundSprite", "plist Load!");

	//
	CCSprite* sprite = CCSprite::createWithSpriteFrameName("back_Ex02.png");		// plist内のkey(ファイル名)を指定
	sprite->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
	this->addChild(sprite);
}


void MapScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void MapScene::buttonOnClickCallBack(CCObject* pSender)
{
	AppPlatform::outputDebugLog("MapScene", "buttonOnClickCallBack", "call");

	CCScene* nextScene = DemoScene::scene();
//	CCDirector* pDirector = CCDirector::sharedDirector();
//	pDirector->runWithScene(nextScene);

	// 遷移に特殊な画面効果をつける場合
	CCTransitionScene *transitionScen = CCTransitionSplitCols::create( 3.0, nextScene );
	CCDirector::sharedDirector()->replaceScene( transitionScen );
}


/**
 * タッチイベント 開始
 *
 * */
bool MapScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {

    points.clear();

    CCPoint location = pTouch->getLocation();
    points.push_back(location);
    prevLocation = location;

    CCSize size = CCDirector::sharedDirector()->getVisibleSize();
    pTarget = CCRenderTexture::create(size.width, size.height, kCCTexture2DPixelFormat_RGBA8888);
    pTarget->retain();
    pTarget->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(pTarget);

    return true;

}


/**
 * タッチイベント 移動中(？)
 * */
void MapScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {
    CCPoint start = pTouch->getLocation();
    CCPoint end   = pTouch->getPreviousLocation();

    pTarget->begin();
    float distance = ccpDistance(start, end);
    for (int i=0; i<distance; i++)
    {
        float diff_x = end.x - start.x;
        float diff_y = end.y - start.y;
        float delta = (float)i / distance;
        CCPoint point = ccp(start.x + (diff_x*delta), start.y + (diff_y*delta));
        pBrush->setPosition(point);
        pBrush->visit();
    }
    pTarget->end();

    float distance2 = ccpDistance(start, prevLocation);
    if (distance2 > 15.0f)
    {
        points.push_back(start);
        prevLocation = start;
    }

}


/**
 *
 * */
void MapScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    CCSize size = CCDirector::sharedDirector()->getVisibleSize();

    if (points.size()>1)
    {
        CCRect rect = this->getTextureRect();

        CCImage* pImage = pTarget->newCCImage();
        CCTexture2D* pTexture = CCTextureCache::sharedTextureCache()->addUIImage(pImage, NULL);
        CC_SAFE_DELETE(pImage);

        CCSprite* pSprite = CCSprite::createWithTexture(pTexture, rect);
        pSprite->setPosition(ccp(rect.origin.x + rect.size.width/2,  size.height - (rect.origin.y + rect.size.height/2)));
        this->addChild(pSprite);
    }

    this->removeChild(pTarget, true);
    pTarget->release();
}


/**
 *
 * */
void MapScene::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    this->removeChild(pTarget, true);
    pTarget->release();
}


/**
 *
 * */
CCRect MapScene::getTextureRect()
{
    CCSize size = CCDirector::sharedDirector()->getVisibleSize();
    float minX = size.width;
    float maxX = 0;
    float minY = size.height;
    float maxY = 0;

    for (int i=0; i<points.size()-1; i++)
    {
        minX = MIN(minX, points[i].x);
        minX = MIN(minX, points[i+1].x);

        maxX = MAX(maxX, points[i].x);
        maxX = MAX(maxX, points[i+1].x);

        minY = MIN(minY, points[i].y);
        minY = MIN(minY, points[i+1].y);

        maxY = MAX(maxY, points[i].y);
        maxY = MAX(maxY, points[i+1].y);
    }

    float margin = pBrush->getContentSize().width * pBrush->getScale() / 2.0f;
    float width  = maxX - minX + margin * 2;
    float height = maxY - minY + margin * 2;

    float x = minX - margin;
    float y = size.height - maxY - margin;

    // 画面外に出ないように補正
    x = MAX(0.0f, x);
    y = MAX(0.0f, y);
    if (minX + width > size.width)
    {
        width = size.width - x;
    }
    if (minY + height > size.height)
    {
        height = size.height - y;
    }

    return CCRectMake(x, y, width, height);
}

