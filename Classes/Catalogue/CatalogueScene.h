#ifndef __CATALOGUESCENE_H__
#define __CATALOGUESCENE_H__

#include "cocos2d.h"

class CatalogueScene : public cocos2d::CCLayer
{
private:
	void buttonOnClickCallBack(CCObject* pSender);
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    void menuCloseCallback(CCObject* pSender);

    CREATE_FUNC(CatalogueScene);
};

#endif // __CATALOGUESCENE_H__
