/*
 * DemoScene.h
 *
 *  Created on: 2013/09/10
 *      Author: y.nitobe
 */

#ifndef DEMOSCENE_H_
#define DEMOSCENE_H_

#include "cocos2d.h"

using namespace cocos2d;

class DemoScene : public cocos2d::CCLayer {

private:
	static const int _MyDroid;
	static const int _DataCnt;

	CCSpriteFrameCache* _frameCacheDroid;	// ドロイドくんをキャッシュする
	CCSpriteFrameCache* _frameCacheBattery;	// Hurdleをキャッシュする

	bool _isMoving;
	bool _isGameEnd;
	int _targetNumber;

	void makeBackground();
	void makeCloseBtn();
	void makeDroid();
	void makeDestination();
	void makeRetryButton();
	void onClickRetryButton(CCNode* node);

	void showResult(bool isSuccess);

	void menuCloseCallback(CCObject* pSender);
	void spriteMoveActionFinished(CCNode* sender);

	int getRandomNumber();

	void makeSpriteAction();
	void makePerticleFire();

public:
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(DemoScene);

	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	// 戻るキー押下
	void keyBackClicked();
};

#endif /* DEMOSCENE_H_ */
