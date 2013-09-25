#ifndef __RESULTSCENE_H__
#define __RESULTSCENE_H__

#include "cocos2d.h"

class ResultScene : public cocos2d::CCLayer
{
private:
	void buttonOnClickCallBack(CCObject* pSender);
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    void menuCloseCallback(CCObject* pSender);

    CREATE_FUNC(ResultScene);
};

#endif // __RESULTSCENE_H__
