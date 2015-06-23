//
//  UnionViewController.cpp
//  2155
//
//  Created by 邱宇青 on 15/6/12.
//
//

#include "UnionViewController.h"


UnionViewController::UnionViewController(string uid)
{
    m_uid = uid;
    CCLog("id =  %s", m_uid.c_str());
}

UnionViewController::~UnionViewController()
{
   
}

void UnionViewController::viewDidLoad()
{
    winSize = this->getView()->getBounds().size;
    this->getNavigationBarItem()->setShowGoBackButton(true);
    
    this->onRequest();
    
}

void UnionViewController::viewDidUnload()
{
    
}

void UnionViewController::onRequest(){
    std::map<std::string,std::string> key_value;
    

    key_value.insert(make_pair("id", m_uid));
    
    char signScr[200];
    sprintf(signScr, "%sid%s",App_key, m_uid.c_str());
    key_value.insert(make_pair("sign", MD5(signScr).md5()));
    
    
    char temurl[200];
    sprintf(temurl, "http://android.2155.com/i/%s",MakeMoneyTag[2]);
    CommonHttpManager::getInstance()->send_post(temurl, key_value, this,
                                                CommonHttpJson_selector(UnionViewController::onRequestFinished));
    

}

void UnionViewController::onRequestFinished(const HttpResponseStatus &status, const CSJson::Value &json){
    if (status == HttpResponseSucceed)
    {
        const CSJson::Value& value = json["msg"];

        m_detailMsg.m_id = value["id"].asString();
        m_detailMsg.m_title =   value["title"].asString();
        CCLog("title==%s",value["title"].asString().c_str());
        m_detailMsg.m_imageUrl = value["icon"].asString();
        m_detailMsg.m_add_money = value["add_money"].asString();
        m_detailMsg.m_desc = value["desc"].asString();
        
        this->initShareView();
        
    }
    
    
}

void UnionViewController::initShareView(){
    if (m_UnionView) {
        this->getView()->removeSubview(m_UnionView);
        m_UnionView = NULL;
    }
    
    winSize = this->getView()->getBounds().size;
    
    m_UnionView = CAView::createWithFrame(CADipRect(0,0,winSize.width, winSize.height), CAColor_white);
    
    
    CALabel* test = CALabel::createWithFrame(CADipRect(150,
                                                       20,
                                                       winSize.width,
                                                       100));
    test->setColor(CAColor_black);
    test->setTextAlignment(CATextAlignmentLeft);
    test->setVerticalTextAlignmet(CAVerticalTextAlignmentTop);
    test->setFontSize(_px(32));
    test->setBold(true);
    test->setTag(100);
    //    CCLog("title = %s", m_detailMsg.m_title.c_str());
    test->setText(m_detailMsg.m_title);
    m_UnionView->addSubview(test);
    
    
    CALabel* money = CALabel::createWithFrame(CADipRect(150,
                                                       80,
                                                       winSize.width,
                                                       100));
    money->setColor(CAColor_red);
    money->setTextAlignment(CATextAlignmentLeft);
    money->setVerticalTextAlignmet(CAVerticalTextAlignmentTop);
    money->setFontSize(_px(40));
//    test->setBold(true);
    money->setTag(101);
    //    CCLog("title = %s", m_detailMsg.m_title.c_str());
    money->setText("+" + m_detailMsg.m_add_money + "元");
    m_UnionView->addSubview(money);
    
    CALabel* dsc = CALabel::createWithFrame(CADipRect(10,
                                                      150,
                                                      winSize.width-10,
                                                      winSize.height/2));
    dsc->setTextAlignment(CATextAlignmentLeft);
    dsc->setVerticalTextAlignmet(CAVerticalTextAlignmentTop);
    dsc->setFontSize(_px(40));
    dsc->setTag(102);
    dsc->setText(m_detailMsg.m_desc );
    m_UnionView->addSubview(dsc);
    

    CAButton* listBut = CAButton::createWithCenter(CADipRect(winSize.width/2, winSize.height/2 + 150, winSize.width/2, 100), CAButtonTypeRoundedRect);
    listBut->setTitleForState(CAControlStateAll, "应用列表");
    listBut->addTarget(this, CAControl_selector(UnionViewController::buttonCallBack), CAControlEventTouchUpInSide);
    m_UnionView->addSubview(listBut);
    
    
    CommonUrlImageView* temImage = CommonUrlImageView::createWithFrame(CADipRect(20,20,100,100));
    temImage->setTag(108);
    temImage->setImageViewScaleType(CAImageViewScaleTypeFitImageCrop);
    temImage->setImage(CAImage::create("source_material/btn_right_blue.png"));
    temImage->setUrl(m_detailMsg.m_imageUrl);
    
    CCLog("cur Url = %s", m_detailMsg.m_imageUrl.c_str());
    m_UnionView->addSubview(temImage);
    
    
    this->getView()->addSubview(m_UnionView);
}


void UnionViewController::showAlert(){
    
}


void UnionViewController::buttonCallBack(CrossApp::CAControl *btn, CrossApp::CCPoint point){
    CCLog("list click");
   
    char strMid[20];
    sprintf(strMid, "%d", RootWindow::getInstance()->getMid());
    CADevice::openUnion(m_uid.c_str(), strMid);
    
}


