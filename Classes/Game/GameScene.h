#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"

class GameScene : public cocos2d::CCLayer
{
private:
	void buttonOnClickCallBack(CCObject* pSender);

	void setBackGroundSprite();
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    void menuCloseCallback(CCObject* pSender);

    CREATE_FUNC(GameScene);

    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
};

#endif // __GAMESCENE_H__
