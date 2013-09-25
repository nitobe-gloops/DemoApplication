/*
 * DemoScene.cpp
 *
 *  Created on: 2013/09/10
 *      Author: y.nitobe
 */

#include "DemoScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace std;
using namespace CocosDenshion;

const int DemoScene::_MyDroid = 99;
const int DemoScene::_DataCnt = 4;

/**
 * Droidくんを操作し、任意の点に存在するナニカを見つける
 * ・Droidくんは画面中央に表示
 * ・ナニカは4点（暫定）のどこか1箇所に存在する
 * ・Droidくんはタップした位置に移動する
 * ・移動した位置が任意の点と同じ場合判定を行う
 * ・ナニカを見つけるとDoroidくんの外見が変わる
 * ・ナニカ以外はハズレの表示を行う
 *
 *
 * */
CCScene* DemoScene::scene() {
	CCScene* scene = CCScene::create();
	DemoScene* layer = DemoScene::create();
	scene->addChild(layer);

	return scene;
}

bool DemoScene::init() {
	CCLOGINFO("アプリケーション開始");

	if(!CCLayer::init() ){
		return false;
	}

	_isMoving = false;
	_isGameEnd = false;
	_targetNumber = getRandomNumber();

	// 画面左下のFPSの表示を切り替える
	CCDirector::sharedDirector()->setDisplayStats(false);

	// タップイベントを取得する
	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);	// シングルタップ

	// 端末の物理キーの反応を有効にする（Android端末限定？）
	this->setKeypadEnabled(true);

	// 背景を設定する
	makeBackground();
	// 終了ボタン
	makeCloseBtn();
	// ナニカは4点を表示する
	makeDestination();
	// ドロイドくんを表示する
	makeDroid();

	makeRetryButton();

	// 画像に動きをつける
//	makeSpriteAction();
	// COCOS2d-xの標準エフェクトを表示
//	makePerticleFire();

	// BGMの設定 SimpleAudioEngine.hのincludeでエラーが出ているがBGMは確認できる
//	SimpleAudioEngine::sharedEngine()->playEffect("neko_bgm_m1_3_piano.m4a");
//	CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.2);	// 0（消音）~1（最大）
//	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("neko_bgm_m2.m4a", true);
	return true;
}


/**
 * ランダムで0～3までの数値を取得する
 * ※ナニカの個数分だけ必要
 * */
int DemoScene::getRandomNumber(){
	// 変数を初期化する
	srand((unsigned)time(NULL));

	// ランダムで値を取得する
	int index = rand() % (_DataCnt);
	CCLog("Targetは %d です", index);
	return index;
}

/**
 * 背景を設定する
 * リソースはResourcesに格納する
 * */
void DemoScene::makeBackground() {
	CCLog("背景を設定します");
	// 画面サイズを取得
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCLog("winSize = %.2f／%.2f", winSize.width, winSize.height);	// 画面サイズを知りたい
	// 背景を生成
	CCSprite* pBG = CCSprite::create("background02.png");		// 画像を指定
	pBG->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));	// 背景表示位置の指定
	this -> addChild(pBG);
}


/**
 * 終了ボタンを配置
 * */
void DemoScene::makeCloseBtn() {
	// 画面サイズを取得
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(DemoScene::menuCloseCallback));

	pCloseItem->setPosition(ccp(origin.x + winSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

}


/**
 * ボタン押下時の処理
 * ->アプリ終了
 * */
void DemoScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


/**
 *
 * */
void DemoScene::makeDroid() {
	CCLog("Droidくんを読み込みます");
	// 画面サイズ取得
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	// plistを読み込み
	_frameCacheDroid = CCSpriteFrameCache::sharedSpriteFrameCache();
	_frameCacheDroid->addSpriteFramesWithFile("emo_images02.plist");

	//
	CCSprite* sprite = CCSprite::createWithSpriteFrameName("emo_im_happy.png");
	sprite->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
	sprite->setTag(_MyDroid);
	this->addChild(sprite);

	// ここからアニメーション
	CCArray* array = CCArray::createWithCapacity(2);
	array->addObject(_frameCacheDroid->spriteFrameByName("emo_im_happy.png"));
	array->addObject(_frameCacheDroid->spriteFrameByName("emo_im_surprised.png"));

	CCAnimation* animation = CCAnimation::createWithSpriteFrames(array, 0.4f);
	CCAnimate* animate = CCAnimate::create(animation);

	sprite->runAction(CCRepeatForever::create(animate));
}


/**
 *
 * */
void DemoScene::makeDestination() {
	CCLog("目的地を読み込みます");
	// 画面サイズ取得
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	// 座標を定義
	int position[2][_DataCnt] = {{winSize.width * 0.2, winSize.width * 0.2, winSize.width * 0.8, winSize.width * 0.8},
								{winSize.height * 0.2, winSize.height  * 0.8, winSize.height  * 0.2, winSize.height * 0.8}};

	for(int n = 0; n < _DataCnt; n++) {

		CCSprite* dSprite = CCSprite::create("ic_coins_l.png");

//		CCLog("position[0][n] = %d／position[1][n] = %d", position[0][n], position[1][n]);

		dSprite->setPosition(ccp(position[0][n], position[1][n]));
		dSprite->setTag(n);

		this->addChild(dSprite);
	}

}


/**
 * ナニカに衝突した時にゲームを終了する
 * */
void DemoScene::showResult(bool isSuccess) {
	// 画面サイズ取得
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    // テキストラベル
    CCLabelTTF* pLabel = CCLabelTTF::create("Success", "Arial", 64);

    // 文字色の変更方法(1)
//    ccColor3B fontColor = {255,0,0};	//ccColor3Bを先に宣言してからsetする
//    pLabel->setColor(fontColor);

	if(isSuccess == true) {
	    pLabel->setString("Success");
	    pLabel->setColor(ccc3((GLubyte)255,(GLubyte)0,(GLubyte)0));		// 文字色の変更方法(2)

	}else {
	    pLabel->setString("Failure");
	    pLabel->setColor(ccc3((GLubyte)0,(GLubyte)0,(GLubyte)0));		// 文字色の変更方法(2)
	}
    pLabel->setPosition(ccp(winSize.width * 0.5 ,winSize.height * 0.5));
    this->addChild(pLabel, 1);

    //
    _isGameEnd = true;
}


/**
 * タッチイベント開始
 * */
bool DemoScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {

	return true;
}


/**
 * タッチイベント終了
 *
 * */
void DemoScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
	if(_isMoving == false && _isGameEnd == false) {
		// 画面サイズを取得
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		// ポイント（座標）取得
		CCDirector* pDirector = CCDirector::sharedDirector();
		CCPoint touchPoint = pDirector->convertToGL(pTouch->getLocationInView());

		CCNode* spriteDroid = this->getChildByTag(_MyDroid);	// 指定したTagが設定されたSpriteのインスタンスを取得する
		CCMoveTo* droidAction = CCMoveTo::create(1, ccp(touchPoint.x, touchPoint.y));

		// spriteMoveActionFinished()を呼び出すCCCallFuncNアクションを作成
		CCCallFuncN* actionDone = CCCallFuncN::create(this, callfuncN_selector(DemoScene::spriteMoveActionFinished));

		// droidAction（移動アニメーション）の後にCCCallFuncNを実行させる
//		spriteDroid->runAction(droidAction);
		spriteDroid->runAction(CCSequence::create(droidAction, actionDone, NULL));

		_isMoving = true;
	}else {
		CCLog("タップ無効中");
	}
}


/**
 *
 * */
void DemoScene::keyBackClicked() {
    //バックキー処理
	menuCloseCallback(NULL);
}


/**
 * かなり無理やりだが、一応の衝突判定を行っている
 * */
void DemoScene::spriteMoveActionFinished(CCNode* sender) {
	CCLog("アニメーション終了");
	// 呼び出し元のSprite取得
	CCSprite* sprite = (CCSprite*)sender;
	CCRect spriteRect = sprite->boundingBox();	// 位置とサイズを取得する

	// ナニカの地点
	CCSprite* targetSprite = (CCSprite*)(this->getChildByTag(_targetNumber));
	CCRect targetRect = targetSprite->boundingBox();	// 位置とサイズを取得する

	// すべてのナニカの座標をArrayListに登録
	CCPointArray* array = CCPointArray::create(4);
	for(int m= 0; m < _DataCnt; m++) {
		CCNode* tmpSprite = this->getChildByTag(m);
		CCRect tmpRect = tmpSprite->boundingBox();
		array->addControlPoint(tmpRect.origin);
	}
	// 正解の座標だけ削除
	array->removeControlPointAtIndex(_targetNumber);


	for(int n = 0; n < array->count(); n++) {
		// ArrayListの中身の数だけダミーのCCRectと判定
		CCRect dummyRect(array->getControlPointAtIndex(n).x, array->getControlPointAtIndex(n).y, targetRect.size.width, targetRect.size.height);

		if(targetRect.intersectsRect(spriteRect)) {
			CCLog("正解");
			sprite->stopAllActions();	// アニメーションの停止

//			sprite->setTexture(CCTextureCache::sharedTextureCache()->addImage("emo_im_money_mouth.png"));
			// スプライトシートを使った（CCSprite::spriteWithSpriteFrameName）場合は以下の手順が必要
			CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("emo_im_money_mouth.png");
			sprite->setTexture(frame->getTexture());
			sprite->setTextureRect(frame->getRect());
			sprite->setDisplayFrame(frame);

			targetSprite->setTexture(CCTextureCache::sharedTextureCache()->addImage("platlogo.png"));

			showResult(true);
			break;

//		}else if(targetRect.containsPoint(array->getControlPointAtIndex(n))){
		}else if(dummyRect.intersectsRect(spriteRect)){
			CCLog("ハズレ");
			sprite->stopAllActions();	// アニメーションの停止

//			sprite->setTexture(CCTextureCache::sharedTextureCache()->addImage("emo_im_crying.png"));
			// スプライトシートを使った（CCSprite::spriteWithSpriteFrameName）場合は以下の手順が必要
			CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("emo_im_crying.png");
			sprite->setTexture(frame->getTexture());
			sprite->setTextureRect(frame->getRect());
			sprite->setDisplayFrame(frame);

			targetSprite->setTexture(CCTextureCache::sharedTextureCache()->addImage("platlogo.png"));
			showResult(false);
		}
	}
	_isMoving = false;
}


/**
 * リトライボタンの作成
 * */
void DemoScene::makeRetryButton() {
	// 画面サイズを取得する
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	// リトライボタンを作成する
	CCLabelTTF* retryLabel = CCLabelTTF::create("Retry", "Arial", 36.0);
	retryLabel->setColor(ccc3((GLubyte)0,(GLubyte)0,(GLubyte)255));
	CCMenuItemLabel* retryItem = CCMenuItemLabel::create(retryLabel, this, menu_selector(DemoScene::onClickRetryButton));
	retryItem->setPosition(ccp(winSize.width *0.9, winSize.height *0.2));

	// メニューを作成する（ボタンとしての機能を付加する）
	CCMenu* menu = CCMenu::create(retryItem, NULL);
	menu->setPosition(CCPointZero);		// retryItemのPositionを設定している為、CCPointZeroを使用する必要がある
	this->addChild(menu);
}


/**
 * リトライボタン押下処理
 * */
void DemoScene::onClickRetryButton(CCNode* node) {
	// ゲームのシーンを新しく用意する
	CCScene* gameScene = (CCScene*)DemoScene::create();
	CCDirector::sharedDirector()->replaceScene(gameScene);
}

