#ifndef __HOMESCENE_H__
#define __HOMESCENE_H__

#include "cocos2d.h"

class HomeScene : public cocos2d::CCLayer
{
private:
	void buttonOnClickCallBack(CCObject* pSender);

	void setBackGroundSprite();
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    void menuCloseCallback(CCObject* pSender);

    CREATE_FUNC(HomeScene);
};

#endif // __HOMESCENE_H__
