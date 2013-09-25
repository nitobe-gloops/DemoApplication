#ifndef __MAPSCENE_H__
#define __MAPSCENE_H__

#include "cocos2d.h"

class MapScene : public cocos2d::CCLayer
{
private:
	void buttonOnClickCallBack(CCObject* pSender);
	void setBackGroundSprite();

    std::vector<cocos2d::CCPoint> points;
    cocos2d::CCPoint prevLocation;
    cocos2d::CCRenderTexture *pTarget;
    cocos2d::CCSprite *pBrush;

    cocos2d::CCRect getTextureRect();

public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    void menuCloseCallback(CCObject* pSender);

    CREATE_FUNC(MapScene);

    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
};

#endif // __MAPSCENE_H__
