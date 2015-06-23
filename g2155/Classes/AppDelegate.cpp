#include "AppDelegate.h"
#include "RootWindow.h"

USING_NS_CC;


AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate() 
{
    
}

bool AppDelegate::applicationDidFinishLaunching()
{
//    C2DXShareSDK::open(CCString::create(""), false);
//    CCDictionary * sinaConfigDict = CCDictionary::create();
//    sinaConfigDict->setObject(CCString::create(""), "app_key");
//    sinaConfigDict->setObject(CCString::create(""), "app_secret");
//    sinaConfigDict->setObject(CCString::create(""), "redirect_url");
//    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeSinaWeibo, sinaConfigDict);
//    
//    
//    
////    KEY	 描述
////    content	 要分享的内容，注意在文档中content对应的是text字段
////    image	 要分享的图片，可以是本地路径imagePath（如：/sdcard/a.jpg）或是一个网址imageUrl
////    title	 要分享的标题
////    description	 内容简要
////    url	 网页分享，仅需要图文分享时，不要传这个字段
////    type	 内容类型，具体参考enum C2DXContentType
////    site	 内容来源的站点名称
////    siteUrl	 内容来源的站点链接
////    musicUrl	 音乐分享，音乐文件的网址
////    extInfo	 微信分享应用时传给应用的附加信息，参考微信API文档
//    CCDictionary *content = CCDictionary::create();
//    content -> setObject(CCString::create("这是一条测试内容"), "content");
//    content -> setObject(CCString::create("http://img0.bdstatic.com/img/image/shouye/systsy-11927417755.jpg"), "image");
//    content -> setObject(CCString::create("测试标题"), "title");
//    content -> setObject(CCString::create("测试描述"), "description");
//    content -> setObject(CCString::create("http://sharesdk.cn"), "url");
//    content -> setObject(CCString::createWithFormat("%d", C2DXContentTypeNews), "type");
//    content -> setObject(CCString::create("http://sharesdk.cn"), "siteUrl");
//    content -> setObject(CCString::create("ShareSDK"), "site");
//    content -> setObject(CCString::create("http://mp3.mwap8.com/destdir/Music/2009/20090601/ZuiXuanMinZuFeng20090601119.mp3"), "musicUrl");
//    content -> setObject(CCString::create("extInfo"), "extInfo");
//    
//    
//    C2DXShareSDK::showShareMenu(NULL, content, CCPointMake(100, 100), C2DXMenuArrowDirectionLeft, shareResultHandler);
    
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //初始化ShareSDK

    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    

    
#endif
    
    //初始化社交平台信息
    this -> initPlatformConfig();
    
    
    // initialize director
    CAApplication* pDirector = CAApplication::getApplication();
    
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);

    
    CCLog("RootWindow Begin");
    // run
    pDirector->runWindow(RootWindow::getInstance());

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CAApplication::getApplication()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CAApplication::getApplication()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}


void AppDelegate::initPlatformConfig()
{
//    //新浪微博
//    CCDictionary *sinaConfigDict = CCDictionary::create();
//    sinaConfigDict -> setObject(CCString::create("568898243"), "app_key");
//    sinaConfigDict -> setObject(CCString::create("38a4f8204cc784f81f9f0daaf31e02e3"), "app_secret");
//    sinaConfigDict -> setObject(CCString::create("http://www.sharesdk.cn"), "redirect_uri");
//    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeSinaWeibo, sinaConfigDict);

}

