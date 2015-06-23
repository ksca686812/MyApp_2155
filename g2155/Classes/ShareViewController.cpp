//
//  ShareViewController.cpp
//  2155
//
//  Created by 邱宇青 on 15/6/11.
//
//

#include "ShareViewController.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"

extern "C"
{
    JNIEXPORT void JNICALL Java_com_ggod2155_g2155_shareStatusNative
    ( JNIEnv* env,jobject thiz ,jint sender)
    {
        int type = sender;
        
        CCLog("type ====  %d", type);
        
        if (type == 1) {
            std::map<std::string,std::string> key_value;
            
            char strMid[20];
            sprintf(strMid, "%d", RootWindow::getInstance()->getMid());
            key_value.insert(make_pair("mid", strMid));
            
            key_value.insert(make_pair("task_id", ShareUid));
            
            char signScr[200];
            sprintf(signScr, "%smid%stask_id%s",App_key, strMid, ShareUid.c_str());
            key_value.insert(make_pair("sign", MD5(signScr).md5()));
            
            
            char temurl[200];
            sprintf(temurl, "http://android.2155.com/i/%s","save_forward_log");
            CommonHttpManager::getInstance()->send_post(temurl, key_value, RootWindow::getInstance(),
                                                        CommonHttpJson_selector(RootWindow::onSave_forward_logRequest));
        }
    }

    
}

#endif








ShareViewController::ShareViewController(string uid)
{
    m_uid = uid;
    CCLog("id =  %s", m_uid.c_str());
}

ShareViewController::~ShareViewController()
{
    this->getView()->removeSubview(p_webView);
    p_webView = NULL;
}

void ShareViewController::viewDidLoad()
{
    winSize = this->getView()->getBounds().size;
    this->getNavigationBarItem()->setShowGoBackButton(true);
    
    this->onRequest();
    
    
}

void ShareViewController::viewDidUnload()
{
    
}

void ShareViewController::onRequest(){
    std::map<std::string,std::string> key_value;
    
    cc_timeval  time;
    CCTime::gettimeofdayCrossApp(&time, NULL);
    char strTime[50];
    sprintf(strTime, "%d", time.tv_usec);
    key_value.insert(make_pair("time", strTime));

    key_value.insert(make_pair("did", m_uid));
    
    char strMid[20];
    sprintf(strMid, "%d", RootWindow::getInstance()->getMid());
    key_value.insert(make_pair("mid", strMid));
    
    
    char signScr[200];
    sprintf(signScr, "%sdid%smid%stime%s",App_key, m_uid.c_str(), strMid,strTime );
    key_value.insert(make_pair("sign", MD5(signScr).md5()));

    
    char temurl[200];
    sprintf(temurl, "http://android.2155.com/i/%s",MakeMoneyTag[3]);
    CommonHttpManager::getInstance()->send_post(temurl, key_value, this,
                                                CommonHttpJson_selector(ShareViewController::onRequestFinished));
    
    
    
//    p_pLoading = CAActivityIndicatorView::createWithCenter(CADipRect(winSize.width/2,winSize.height/2,50,50));
//    this->getView()->insertSubview(p_pLoading, CAWindowZoderTop);
//    p_pLoading->setLoadingMinTime(0.5f);
//    p_pLoading->setTargetOnCancel(this, callfunc_selector(MakeMoneyViewController::initTableView));
}

void ShareViewController::onRequestFinished(const HttpResponseStatus &status, const CSJson::Value &json){
    if (status == HttpResponseSucceed)
    {
        const CSJson::Value& value = json["msg"];

        m_detailMsg.m_id = value["id"].asString();
        m_detailMsg.m_title =   value["title"].asString();
        CCLog("title==%s",value["title"].asString().c_str());
        m_detailMsg.m_imageUrl = value["icon"].asString();
        m_detailMsg.m_add_money = value["add_money"].asString();
        m_detailMsg.m_money_get = value["money_get"].asString();
        m_detailMsg.m_read_num = value["read_num"].asString();
        m_detailMsg.m_demo_url = value["demo_url"].asString();
        m_detailMsg.m_preview_url = value["preview_url"].asString();
    
        
        this->initShareView();
        
    }
    

}

void ShareViewController::initShareView(){
    if (m_ShardView) {
        this->getView()->removeSubview(m_ShardView);
        m_ShardView = NULL;
    }
    
    winSize = this->getView()->getBounds().size;
    
    m_ShardView = CAView::createWithFrame(CADipRect(0,0,winSize.width, 250), ccc4(166, 166, 166, 80));
    
    
    CALabel* test = CALabel::createWithFrame(CADipRect(100,
                                                       20,
                                                       winSize.width,
                                                       40));
    test->setColor(CAColor_black);
    test->setTextAlignment(CATextAlignmentLeft);
    test->setVerticalTextAlignmet(CAVerticalTextAlignmentTop);
    test->setFontSize(_px(32));
    test->setBold(true);
    test->setTag(100);
//    CCLog("title = %s", m_detailMsg.m_title.c_str());
    test->setText(m_detailMsg.m_title);
    m_ShardView->addSubview(test);
    
    CALabel* dsc = CALabel::createWithFrame(CADipRect(100,
                                                      60,
                                                      winSize.width,
                                                      40));
    dsc->setTextAlignment(CATextAlignmentLeft);
    dsc->setVerticalTextAlignmet(CAVerticalTextAlignmentTop);
    dsc->setFontSize(_px(24));
    dsc->setTag(102);
    dsc->setColor(ccc4(180,180,180,255));
    //    dsc->setLineSpacing(10);
//    CCLog("m_add_money = %s", m_detailMsg.m_add_money.c_str());
    dsc->setText("分享内容被好友点击阅读，总奖励" + m_detailMsg.m_add_money + "元");
    m_ShardView->addSubview(dsc);
    
    CALabel* readNum = CALabel::createWithCenter(CADipRect(80, 150, 150, 100));
     readNum->setColor(ccc4(180,180,180,255));
    readNum->setTextAlignment(CATextAlignmentLeft);
    readNum->setVerticalTextAlignmet(CAVerticalTextAlignmentTop);
    readNum->setFontSize(_px(24));
    readNum->setTag(104);
    readNum->setText("阅读次数: "+ m_detailMsg.m_read_num);
    m_ShardView->addSubview(readNum);
    
    CALabel* getNum = CALabel::createWithCenter(CADipRect(winSize.width-140, 150, 150, 100));
    getNum->setColor(ccc4(180,180,180,255));
    getNum->setTextAlignment(CATextAlignmentLeft);
    getNum->setVerticalTextAlignmet(CAVerticalTextAlignmentTop);
    getNum->setFontSize(_px(24));
    getNum->setTag(106);
    getNum->setText("已得奖励: "+ m_detailMsg.m_money_get);
    m_ShardView->addSubview(getNum);
    
    CAButton* shareBut = CAButton::createWithCenter(CADipRect(winSize.width/2, 200, winSize.width - 50, 50), CAButtonTypeRoundedRect);
    shareBut->setTitleForState(CAControlStateAll, "立即分享到朋友圈");
    shareBut->addTarget(this, CAControl_selector(ShareViewController::buttonCallBack), CAControlEventTouchUpInSide);
    m_ShardView->addSubview(shareBut);
    
    
    CommonUrlImageView* temImage = CommonUrlImageView::createWithFrame(CADipRect(0,0,74,74));
    temImage->setTag(108);
    temImage->setImageViewScaleType(CAImageViewScaleTypeFitImageCrop);
    temImage->setImage(CAImage::create("source_material/btn_right_blue.png"));
    temImage->setUrl(m_detailMsg.m_imageUrl);
    m_ShardView->addSubview(temImage);
    
    
    p_webView = CAWebView::createWithFrame(CADipRect(0, 250, winSize.width, winSize.height-250));
    p_webView->loadURL(m_detailMsg.m_preview_url);
    this->getView()->addSubview(p_webView);
    
    
    this->getView()->addSubview(m_ShardView);
}


void ShareViewController::showAlert(){
    
}




void ShareViewController::buttonCallBack(CrossApp::CAControl *btn, CrossApp::CCPoint point){
    CCLog("weixin share click");
    
    ShareUid = m_detailMsg.m_id;
    CADevice::onShare(false, m_detailMsg.m_imageUrl, m_detailMsg.m_demo_url, m_detailMsg.m_title, "WechatMoments", "WechatMoments");
    
}


