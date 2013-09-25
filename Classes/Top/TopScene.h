#ifndef __TOP_SCENE_H__
#define __TOP_SCENE_H__

#include "cocos2d.h"

class TopScene : public cocos2d::CCLayer
{
private:
	void makeCloseBtn();
    void onClickStartButton(CCObject* pSender);
	void menuCloseCallback(CCObject* pSender);

	void setBackGroundSprite();

	const char* LocalizedString(const char* searchKey, const char* comment);
public:
    virtual bool init();  
    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(TopScene);
};

#endif // __TOP_SCENE_H__
