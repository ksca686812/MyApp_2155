//
//  TeacherAndPupilViewController.cpp
//  2155
//
//  Created by 邱宇青 on 15/6/9.
//
//

#include "TeacherAndPupilViewController.h"



TeacherAndPupilViewTableCell::TeacherAndPupilViewTableCell(){
    this->setAllowsSelected(false);
}

TeacherAndPupilViewTableCell::~TeacherAndPupilViewTableCell(){
    
}

TeacherAndPupilViewTableCell* TeacherAndPupilViewTableCell::create(const std::string& identifier, const CADipRect& _rect){
    
    return NULL;
}

void TeacherAndPupilViewTableCell::highlightedTableViewCell(){
    this->setBackgroundView(CAView::createWithColor(ccc4(0, 0, 0, 64)));
}


void TeacherAndPupilViewTableCell::selectedTableViewCell(){
    this->setBackgroundView(CAView::createWithColor(ccc4(0, 0, 0, 64)));
}


void TeacherAndPupilViewTableCell::initWithCell(){
    
}



TeacherAndPupilViewController::TeacherAndPupilViewController(){

}

TeacherAndPupilViewController::~TeacherAndPupilViewController(){
    
}



void TeacherAndPupilViewController::viewDidLoad(){
    winSize = this->getView()->getBounds().size;
    
    this->onRequest();

}

void TeacherAndPupilViewController::onRequest(){
    std::map<std::string,std::string> key_value;
    
    char strMid[50];
    sprintf(strMid, "%d", RootWindow::getInstance()->getMid());
    key_value.insert(make_pair("mid", strMid));
    char signScr[200];
    sprintf(signScr, "%smid%s",App_key, strMid);
    key_value.insert(make_pair("sign", MD5(signScr).md5()));
    
    char temurl[200];
    sprintf(temurl, "http://android.2155.com/i/%s",basicTag[3]);
    CommonHttpManager::getInstance()->send_post(temurl, key_value, this,
                                                CommonHttpJson_selector(TeacherAndPupilViewController::onRequestFinished),true);


}

void TeacherAndPupilViewController::onRequestFinished(const HttpResponseStatus &status, const CSJson::Value &json){
    if (status == HttpResponseSucceed) {
        const CSJson::Value& value = json["msg"];
        
        m_shareMsg.m_title = value["title"].asString();
        m_shareMsg.m_desc =   value["desc"].asString();
//        CCLog("title==%s",value["title"].asString().c_str());
        m_shareMsg.m_img = value["img"].asString();
        m_shareMsg.m_share_url = value["share_url"].asString();
        
        
        m_pageMsg.tudi_amount = value["tudi_amount"].asString();
        m_pageMsg.tudi_count = value["tudi_count"].asString();
        m_pageMsg.tudi_reward = value["tudi_reward"].asString();
        m_pageMsg.tusun_count = value["tusun_count"].asString();
        m_pageMsg.tusun_reward = value["tusun_reward"].asString();
        
        const CSJson::Value& tudis = value["my_tudi"];
        int length = tudis.size();
        CCLog("tudis==%d",length);
        
      
        
         this->initTableView();
    }
    

    
}


void TeacherAndPupilViewController::initTableView(){
    if (p_TableView!=NULL) {
        this->getView()->removeSubview(p_TableView);
        p_TableView = NULL;
    }
    
    p_TableView = CATableView::createWithFrame(this->getView()->getBounds());
    p_TableView->setTableViewDataSource(this);
    p_TableView->setTableViewDelegate(this);
    p_TableView->setAllowsSelection(true);
    this->getView()->addSubview(p_TableView);
    
    CAView* headview = CAView::create();
    headview->setColor(CAColor_red);
    
    CALabel* label = CALabel::createWithFrame(CADipRect(0,0,winSize.width,100));
    label->setText("累计师徒奖励：");
    label->setFontSize(_px(25));
    label->setColor(CAColor_white);
    label->setTextAlignment(CATextAlignmentLeft);
    label->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    headview->addSubview(label);
    
    CALabel* label2 = CALabel::createWithFrame(CADipRect(winSize.width - 100,0,winSize.width,100));
    label2->setText(m_pageMsg.tudi_amount);
    label2->setFontSize(_px(25));
    label2->setColor(CAColor_white);
    label2->setTextAlignment(CATextAlignmentLeft);
    label2->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    headview->addSubview(label2);
    
    //////////
    CALabel* label3 = CALabel::createWithFrame(CADipRect(0, 80,winSize.width,100));
    label3->setText("徒弟个数");
    label3->setFontSize(_px(25));
    label3->setColor(CAColor_white);
    label3->setTextAlignment(CATextAlignmentLeft);
    label3->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    headview->addSubview(label3);
    
    CALabel* label4 = CALabel::createWithFrame(CADipRect(winSize.width/2 - 50,80,winSize.width,100));
    label4->setText(m_pageMsg.tudi_count);
    label4->setFontSize(_px(25));
    label4->setColor(CAColor_white);
    label4->setTextAlignment(CATextAlignmentLeft);
    label4->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    headview->addSubview(label4);
    
    ///////////
    CALabel* label5 = CALabel::createWithFrame(CADipRect(0,200,winSize.width,100));
    label5->setText("徒弟奖励：");
    label5->setFontSize(_px(25));
    label5->setColor(CAColor_white);
    label5->setTextAlignment(CATextAlignmentLeft);
    label5->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    headview->addSubview(label5);
    
    CALabel* label6 = CALabel::createWithFrame(CADipRect(winSize.width/2 - 50,200,winSize.width,100));
    label6->setText(m_pageMsg.tudi_reward);
    label6->setFontSize(_px(25));
    label6->setColor(CAColor_white);
    label6->setTextAlignment(CATextAlignmentLeft);
    label6->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    headview->addSubview(label6);
    
    ///////////
    CALabel* label7 = CALabel::createWithFrame(CADipRect(winSize.width/2 + 50,80,winSize.width,100));
    label7->setText("徒孙个数：");
    label7->setFontSize(_px(25));
    label7->setColor(CAColor_white);
    label7->setTextAlignment(CATextAlignmentLeft);
    label7->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    headview->addSubview(label7);
    
    CALabel* label8 = CALabel::createWithFrame(CADipRect(winSize.width - 50,80,winSize.width,100));
    label8->setText(m_pageMsg.tusun_count);
    label8->setFontSize(_px(25));
    label8->setColor(CAColor_white);
    label8->setTextAlignment(CATextAlignmentLeft);
    label8->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    headview->addSubview(label8);
    
    ///////////
    CALabel* label9 = CALabel::createWithFrame(CADipRect(winSize.width/2 + 50,200,winSize.width,100));
    label9->setText("徒孙奖励：");
    label9->setFontSize(_px(25));
    label9->setColor(CAColor_white);
    label9->setTextAlignment(CATextAlignmentLeft);
    label9->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    headview->addSubview(label9);
    
    CALabel* label10 = CALabel::createWithFrame(CADipRect(winSize.width - 50,200,winSize.width,100));
    label10->setText(m_pageMsg.tusun_reward);
    label10->setFontSize(_px(25));
    label10->setColor(CAColor_white);
    label10->setTextAlignment(CATextAlignmentLeft);
    label10->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    headview->addSubview(label10);
    
    
    p_TableView->setTableHeaderView(headview);
    p_TableView->setTableHeaderHeight(_px(300));
    
    
    
}

void TeacherAndPupilViewController::showAlert()
{
    p_alertView = CAView::createWithFrame(this->getView()->getBounds());
    this->getView()->addSubview(p_alertView);
    
    
    CAButton* btn5 = CAButton::create(CAButtonTypeSquareRect);
    btn5->setTag(100);
    btn5->setCenter(CADipRect(winSize.width/2, winSize.height/2, winSize.width, winSize.height));
    btn5->setTitleColorForState(CAControlStateNormal,CAColor_white);
    btn5->addTarget(this, CAControl_selector(TeacherAndPupilViewController::buttonCallBack), CAControlEventTouchUpInSide);
    p_alertView->addSubview(btn5);
    
    CALabel* test = CALabel::createWithCenter(CADipRect(winSize.width/2,
                                                        winSize.height-100,
                                                        winSize.width,
                                                        40));
    test->setColor(CAColor_gray);
    test->setTextAlignment(CATextAlignmentCenter);
    test->setVerticalTextAlignmet(CAVerticalTextAlignmentTop);
    test->setFontSize(_px(24));
    test->setText("网络不给力，请点击屏幕重新加载～");
    p_alertView->addSubview(test);
    
}

void TeacherAndPupilViewController::buttonCallBack(CAControl* btn,CCPoint point)
{
    this->getView()->removeSubview(p_alertView);
    p_alertView = NULL;
    
    this->onRequest();
}

void TeacherAndPupilViewController::onShareBtn(CAControl* btn,CCPoint point)
{
    CCLog("onShareBtn");
    CADevice::onShare(false, m_shareMsg.m_img, m_shareMsg.m_share_url, m_shareMsg.m_title, m_shareMsg.m_desc, "");
}


void TeacherAndPupilViewController::viewDidAppear(){
    RootWindow::getInstance()->getRootTabBarontroller()->setNavigationBarItem(CANavigationBarItem::create("师徒"));
    
    this->onRequest();
}

void TeacherAndPupilViewController::viewDidUnload(){
    
}

void TeacherAndPupilViewController::tableViewDidSelectRowAtIndexPath(CrossApp::CATableView *table, unsigned int section, unsigned int row){
    CCLog("didSelect row = %d , section = %d", row, section);
}

void TeacherAndPupilViewController::tableViewDidDeselectRowAtIndexPath(CrossApp::CATableView *table, unsigned int section, unsigned int row){
    
}


CAView* TeacherAndPupilViewController::tableViewSectionViewForHeaderInSection(CrossApp::CATableView *table, const CrossApp::CCSize &viewSize, unsigned int section){
    
    CAView* view = CAView::createWithColor(CAColor_gray);
    
    return view;
}

CAView* TeacherAndPupilViewController::tableViewSectionViewForFooterInSection(CATableView* table, const CCSize& viewSize, unsigned int section)
{
    CAView* view = CAView::createWithColor(CAColor_white);

    return view;
}

CATableViewCell* TeacherAndPupilViewController::tableCellAtIndex(CATableView* table, const CCSize& cellSize, unsigned int section, unsigned int row)
{
    CCLog("row = %d , section = %d", row, section);
    CADipSize _size = cellSize;
    CATableViewCell* p_Cell = p_TableView->dequeueReusableCellWithIdentifier("2155");
    if (p_Cell == NULL && section == 0)
    {
        p_Cell = CATableViewCell::create("2155");
        p_Cell->setAllowsSelected(false);
        
        CAButton * shareBtn = CAButton::createWithCenter(CADipRect(_size.width/2,_size.height/2,_size.width - 80, _size.height - 20), CAButtonTypeRoundedRect);
        shareBtn->setTitleColorForState(CAControlStateAll, CAColor_white);
        shareBtn->setBackGroundViewForState(CAControlStateAll, CAView::createWithColor(CAColor_red));
        shareBtn->setTitleForState(CAControlStateAll, "分享给好友");
        shareBtn->addTarget(this, CAControl_selector(TeacherAndPupilViewController::onShareBtn), CAControlEventTouchUpInSide);
        p_Cell->addSubview(shareBtn);
    }
    
    if (p_Cell == NULL && section == 1) {
        p_Cell = CATableViewCell::create("2155");
        p_Cell->setAllowsSelected(false);

        CALabel* itemText = CALabel::createWithCenter(CADipRect(_size.width/2, _size.height/2, _size.width-200,80));
        itemText->setTag(100);
        itemText->setFontSize(_px(30));
        itemText->setText("躺着赚钱全靠徒弟，赶紧收徒吧！");
        itemText->setColor(CAColor_gray);
        itemText->setTextAlignment(CATextAlignmentCenter);
        itemText->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
        p_Cell->addSubview(itemText);
        
    }
    
    if (p_Cell == NULL && section == 2) {
        p_Cell = CATableViewCell::create("2155");
        p_Cell->setAllowsSelected(false);
        
        CALabel* itemText = CALabel::createWithCenter(CADipRect(_size.width/2, _size.height/2, _size.width-200,80));
        itemText->setTag(100);
        itemText->setFontSize(_px(25));
        itemText->setTag(120);
        itemText->setColor(CAColor_black);
        itemText->setTextAlignment(CATextAlignmentLeft);
        itemText->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
        p_Cell->addSubview(itemText);
    }
    
    if (section == 2) {
        CALabel * label = (CALabel*)p_Cell->getSubviewByTag(120);
        label->setText(unicode_to_utf8(shouTuTip[row]));
        
    }
    
    
    
    
    return p_Cell;
}



unsigned int TeacherAndPupilViewController::numberOfRowsInSection(CATableView *table, unsigned int section)
{
    int cellnum = 0;
    if (section==0) {
        cellnum = 1;
    }else if (section==1){
        cellnum = 1;
    }
    else if (section==2){
        cellnum = 2;
    }
    return cellnum;
}

unsigned int TeacherAndPupilViewController::numberOfSections(CATableView *table)
{
    return 3;
}
unsigned int TeacherAndPupilViewController::tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    if (section==0) {
        return _px(100);
    }else if (section==1){
        return _px(150);
    }
    else if (section==2){
        return _px(80);
    }
    
    return _px(200);
}

unsigned int TeacherAndPupilViewController::tableViewHeightForHeaderInSection(CATableView* table, unsigned int section)
{
    int h = 40;
    if (section==1) {
        h=80;
    }
    return _px(h);
}

unsigned int TeacherAndPupilViewController::tableViewHeightForFooterInSection(CATableView* table, unsigned int section)
{
    return 1;
}