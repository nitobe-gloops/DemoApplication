#ifndef __FRIENDSCENE_H__
#define __FRIENDSCENE_H__

#include "cocos2d.h"

class FriendScene : public cocos2d::CCLayer
{
private:
	void buttonOnClickCallBack(CCObject* pSender);
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    void menuCloseCallback(CCObject* pSender);

    CREATE_FUNC(FriendScene);
};

#endif // __FRIENDSCENE_H__
