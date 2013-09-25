#include "TopScene.h"
#include "Home/HomeScene.h"
#include "platform/CCCommon.h"

USING_NS_CC;

CCScene* TopScene::scene()
{
    CCScene *scene = CCScene::create();
    TopScene *layer = TopScene::create();
    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool TopScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    // 背景画像を設定する
    setBackGroundSprite();

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    // ボタン
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "platlogo.png",
                                        "platlogo.png",
                                        this,
                                        menu_selector(TopScene::onClickStartButton));
    
	pCloseItem->setPosition(ccp(visibleSize.width * 0.5,visibleSize.height * 0.5));

    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);


    // テキストラベル
    CCLabelTTF* pLabel = CCLabelTTF::create("Press the Jelly Bean", "Arial", 24);
    pLabel->setColor(ccc3((GLubyte)0,(GLubyte)0,(GLubyte)0));
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // ローカライズ（多言語対応）
    pLabel->setString(LocalizedString("App_Comment", "Hello"));
    this->addChild(pLabel, 1);


    makeCloseBtn();

    return true;
}


/**
 * 背景画像を設定する
 * */
void TopScene::setBackGroundSprite() {
	// 画面サイズ取得
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	// plistを読み込み
	CCSpriteFrameCache* frameCacheBG = CCSpriteFrameCache::sharedSpriteFrameCache();
	frameCacheBG->addSpriteFramesWithFile("SpriteSheets/DummyBackground02.plist");		// plistのパスを指定

	CCLOG("DEMO::HomeScene#setBackGroundSprite() >> plist Load!");

	//
	CCSprite* sprite = CCSprite::createWithSpriteFrameName("back_Ex02.png");		// plist内のkey(ファイル名)を指定
	sprite->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
	this->addChild(sprite);
}


void TopScene::onClickStartButton(CCObject* pSender)
{
	CCLog("DEMO::TopScene#buttonOnClickCallBack() >> ボタン押下");
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCScene* nextScene = HomeScene::scene();
	pDirector->runWithScene(nextScene);

	// 遷移に特殊な画面効果をつける場合
//	CCTransitionScene *transitionScen = CCTransitionSplitCols::create( 3.0, nextScene );
//	CCDirector::sharedDirector()->replaceScene( transitionScen );

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
   // NOP
#endif
}

/**
 * 終了ボタンを配置
 * */
void TopScene::makeCloseBtn() {
	// 画面サイズを取得
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(TopScene::menuCloseCallback));

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
void TopScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


/**
 * 第一引数に指定されたKeyと一致する文字列を言語ファイルから読み込む
 * 指定されたkeyが無い場合は、第二引数に渡された文字列が返る
 *
 * 今回の実装では、英語と日本語にのみ対応させる
 * */
const char* TopScene::LocalizedString(const char* searchKey, const char* comment)
{
    using namespace std;
    const char* ret = comment;

    static map<string, string> localizable;
    if(localizable.empty()){
    	// 現在の言語設定を取得する
        ccLanguageType lang = CCApplication::sharedApplication()->getCurrentLanguage();

        // 言語ディレクトリを検索対象にする
        CCFileUtils* fileUtils = CCFileUtils::sharedFileUtils();
        if (lang == kLanguageEnglish)
        {
            fileUtils->addSearchPath("en.lproj");		// フォルダ名
        }
        else if (lang == kLanguageJapanese)
        {
            fileUtils->addSearchPath("ja.lproj");		// フォルダ名
        }
        // 言語ファイルを開く
        unsigned long size;
        string fullpath = fileUtils->fullPathForFilename("Localizable.strings");		// 言語設定ファイル名
        unsigned char* data = fileUtils->getFileData(fullpath.c_str(), "rb", &size);
        if (data == NULL)
        {
            return ret;
        }
        // Localizable.string のパース
        istringstream is((char*)data);
        delete [] data;
        string line;
        while (std::getline(is, line))
        {
            string::size_type sep = line.find('=');
            if (sep != string::npos)
            {
                string key = line.substr(0,sep-1);
                string val = line.substr(sep+1);
                // スペース、セミコロンなどをトリミングする
                key.erase(0, key.find_first_not_of(" \""));
                key.erase(key.find_last_not_of(" \"")+1);
                val.erase(0, val.find_first_not_of(" \""));
                val.erase(val.find_last_not_of(" \";")+1);
                localizable.insert(pair<string, string>(key,val));
            }
        }
    }

    // キー値の検索
    map<string,string>::iterator ite = localizable.find(searchKey);
    if (ite != localizable.end())
    {
        ret = CCString::create((ite->second).c_str())->getCString();
    }
    return ret;
}
