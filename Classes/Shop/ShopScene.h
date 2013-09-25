#ifndef __SHOPSCENE_H__
#define __SHOPSCENE_H__

#include "cocos2d.h"

class ShopScene : public cocos2d::CCLayer
{
private:
	void buttonOnClickCallBack(CCObject* pSender);
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    void menuCloseCallback(CCObject* pSender);

    CREATE_FUNC(ShopScene);
};

#endif // __SHOPSCENE_H__
