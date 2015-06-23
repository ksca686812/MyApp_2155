

#include "RootWindow.h"
#include "MainViewController.h"
#include "MakeMoneyViewController.h"
#include "ExchangeViewController.h"
#include "TeacherAndPupilViewController.h"
#include "MyViewController.h"

static RootWindow* _window = NULL;


RootWindow* RootWindow::getInstance()
{
    if (_window == NULL)
    {
        _window = new RootWindow();
        _window->init();
        _window->autorelease();
    }
    return _window;
    
}

RootWindow::RootWindow():m_pRootNavigationController(NULL),m_mid(0)
{

}

RootWindow::~RootWindow()
{

}



bool RootWindow::init()
{
    if (!CAWindow::init())
    {
        return false;
    }
    
//    FirstViewController* _viewController = new FirstViewController();
//    _viewController->init();
//    this->setRootViewController(_viewController);
//    _viewController->release();
    
    
    
    std::map<std::string,
    std::string> key_value;
//    key_value.insert(make_pair("", App_key));
    key_value.insert(make_pair("app_version", "1.0"));
    key_value.insert(make_pair("idfa", CADevice::getUdid()));
    
    CCLog("CADevice ID= %s",  CADevice::getUdid().c_str());
    char signScr[200];
    sprintf(signScr, "%sapp_version%sidfa%s",App_key, "1.0", CADevice::getUdid().c_str());
    key_value.insert(make_pair("sign", MD5(signScr).md5()));
    
    
    char temurl[200];
    sprintf(temurl, "http://android.2155.com/i/%s",basicTag[0]);
    CommonHttpManager::getInstance()->send_post(temurl, key_value, this,
                                                CommonHttpJson_selector(RootWindow::onRequestFinished));

    
    return true;
}


void RootWindow::onRequestFinished(const HttpResponseStatus &status, const CSJson::Value &json){
    CCLog("HttpResponseStatus %d", status);
    
    if (status == HttpResponseSucceed) {
        const CSJson::Value& value = json["msg"];
        int length = value.size();
        
        CCLog("length = %d , mid = %d", length, value["mid"].asInt());
        m_mid = value["mid"].asInt();
        
        if (m_mid > 0 ) {
            this->initMainView();
        }
        

        
        
    }else{
        
        
    }
    
    
}

void RootWindow::onSave_forward_logRequest(const HttpResponseStatus &status, const CSJson::Value &json){
    CCLog("onSave_forward_logRequest %d", status);
    
    if (status == HttpResponseSucceed) {
        
        
        
    }else{
        
        
    }
}


void RootWindow::initMainView(){
    CCSize winSize = this->getBounds().size;
    
    CAVector<CAViewController*> vec;
    
    MainViewController * mainController = MainViewController::create();
    mainController->setTabBarItem(CATabBarItem::create("首页", CAImage::create(""),CAImage::create("")));
    vec.pushBack(mainController);
    
    ExchangeViewController * exchangeController = ExchangeViewController::create();
    exchangeController->setTabBarItem(CATabBarItem::create("兑换", CAImage::create(""),CAImage::create("")));
    vec.pushBack(exchangeController);
    
    CAVector<CAViewController*> vec_makeMoney;
    MakeMoneyViewController* controller1 = new MakeMoneyViewController(0);
    controller1->setTabBarItem(CATabBarItem::create("快速赚钱", CAImage::create(""),CAImage::create("")));
    vec_makeMoney.pushBack(controller1);
    MakeMoneyViewController* controller2 = new MakeMoneyViewController(1);
    controller2->setTabBarItem(CATabBarItem::create("分享赚钱", CAImage::create(""),CAImage::create("")));
    vec_makeMoney.pushBack(controller2);
    CATabBarController * makeMoneyController = new CATabBarController();
    makeMoneyController->initWithViewControllers(vec_makeMoney,CABarVerticalAlignmentTop);
    makeMoneyController->setTabBarItem(CATabBarItem::create("赚钱", CAImage::create(""),CAImage::create("")));
    makeMoneyController->setTabBarSelectedBackGroundColor(CAColor_red);
    makeMoneyController->setTabBarTitleColorForNormal(CAColor_white);
    makeMoneyController->setTabBarTitleColorForSelected(CAColor_orange);
    makeMoneyController->setScrollEnabled(true);
    makeMoneyController->autorelease();
    vec.pushBack(makeMoneyController);
    
    TeacherAndPupilViewController* teacherAndPupilController = TeacherAndPupilViewController::create();
    teacherAndPupilController->setTabBarItem(CATabBarItem::create("师徒", CAImage::create(""),CAImage::create("")));
    vec.pushBack(teacherAndPupilController);
    
    MyViewController* myController = MyViewController::create();
    myController->setTabBarItem(CATabBarItem::create("我的", CAImage::create(""),CAImage::create("")));
    vec.pushBack(myController);
    
    CATabBarController* tabBarController = new CATabBarController();
    tabBarController->initWithViewControllers(vec);
    tabBarController->setTabBarSelectedBackGroundColor(CAColor_gray);
    tabBarController->setTabBarTitleColorForNormal(CAColor_white);
    tabBarController->setTabBarTitleColorForSelected(CAColor_red);

    
    
    CANavigationController *nav = new CANavigationController();
    nav->initWithRootViewController(tabBarController);
    //    nav->setNavigationBarBackGroundImage(CAImage::create("image/navbg.jpg"));
    nav->setNavigationBarBackGroundColor(CAColor_gray);
    
    
    

    m_pRootTabBarontroller = tabBarController;
    m_pRootNavigationController = nav;
    
    this->setRootViewController(nav);
    
    tabBarController->release();
    nav->release();
   
}


