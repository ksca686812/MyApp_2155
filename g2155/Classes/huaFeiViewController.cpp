//
//  huaFeiViewController.cpp
//  g2155
//
//  Created by 邱宇青 on 15/6/17.
//
//

#include "huaFeiViewController.h"


huaFeiViewController::huaFeiViewController(int money)
{
    m_money = money;
}

huaFeiViewController::~huaFeiViewController()
{

}

void huaFeiViewController::viewDidLoad()
{
    winSize = this->getView()->getBounds().size;
    this->getNavigationBarItem()->setShowGoBackButton(true);
    
    this->initView();
    
    
}

void huaFeiViewController::viewDidUnload()
{
    
}

void huaFeiViewController::onRequest(string haoma, string money){
    std::map<std::string,std::string> key_value;
    
    char strMid[20];
    sprintf(strMid, "%d", RootWindow::getInstance()->getMid());
    key_value.insert(make_pair("mid", strMid));
    
    key_value.insert(make_pair("mobile", haoma));
    
    key_value.insert(make_pair("money", money));
    
    char signScr[200];
    sprintf(signScr, "%smid%smobile%smoney%s",App_key,  strMid, haoma.c_str(),money.c_str());
    key_value.insert(make_pair("sign", MD5(signScr).md5()));
    
    
    char temurl[200];
    sprintf(temurl, "http://android.2155.com/i/%s", "exchange_huafei");
    CommonHttpManager::getInstance()->send_post(temurl, key_value, this,
                                                CommonHttpJson_selector(huaFeiViewController::onRequestFinished));
    
    
    
    //    p_pLoading = CAActivityIndicatorView::createWithCenter(CADipRect(winSize.width/2,winSize.height/2,50,50));
    //    this->getView()->insertSubview(p_pLoading, CAWindowZoderTop);
    //    p_pLoading->setLoadingMinTime(0.5f);
    //    p_pLoading->setTargetOnCancel(this, callfunc_selector(MakeMoneyViewController::initTableView));
}

void huaFeiViewController::onRequestFinished(const HttpResponseStatus &status, const CSJson::Value &json){
    if (status == HttpResponseSucceed)
    {
        
//        const CSJson::Value& code = json["code"];
        
        const CSJson::Value& value = json["msg"];
        CCLog("str = %s", value.asString().c_str());
        CAAlertView* alertView = CAAlertView::createWithText("提示", value.asString().c_str(), "close",NULL);
        alertView->show();
        
        
    }
    
    
}

void huaFeiViewController::initView(){
    if (m_View) {
        this->getView()->removeSubview(m_View);
        m_View = NULL;
    }
    
    winSize = this->getView()->getBounds().size;
    
    m_View = CAView::createWithFrame(CADipRect(0,0,winSize.width, winSize.height), ccc4(166, 166, 166, 80));
    
    CATextField* textField = CATextField::createWithCenter(CADipRect(winSize.width/2, 100, winSize.width-100, 80));
    textField->setFontSize(_px(40));
    textField->setTag(100);
    textField->setPlaceHolder("输入你的号码");
    textField->setKeyboardType(KEY_BOARD_TYPE_NUMBER);
    m_View->addSubview(textField);
    
//    CATextField* textField2 = CATextField::createWithCenter(CADipRect(winSize.width/2, 200, winSize.width-100, 80));
//    textField2->setFontSize(_px(40));
//    textField2->setTag(101);
//    textField2->setPlaceHolder("充值金额");
//    textField2->setKeyboardType(KEY_BOARD_TYPE_NUMBER);
//    m_View->addSubview(textField2);
    
    
    CAButton * but = CAButton::createWithCenter(CADipRect(winSize.width/2, 250, winSize.width -100, 80), CAButtonTypeSquareRect);
    but->setTitleForState(CAControlStateAll, "提交");
    but->addTarget(this, CAControl_selector(huaFeiViewController::buttonCallBack), CAControlEventTouchUpInSide);
    m_View->addSubview(but);
    
    this->getView()->addSubview(m_View);
}


void huaFeiViewController::showAlert(){
    
}




void huaFeiViewController::buttonCallBack(CrossApp::CAControl *btn, CrossApp::CCPoint point){
    CATextField* textField = (CATextField*)m_View->getSubviewByTag(100);
    string text = textField->getText();
    
//    CATextField* textField2 = (CATextField*)m_View->getSubviewByTag(101);
//    string text2 = textField2->getText();
    
    char money[10];
    sprintf(money, "%d",m_money);
    this->onRequest(text, money);
}



///////  PreView


huafeiPreViewController::huafeiPreViewController(){
    
}

huafeiPreViewController::~huafeiPreViewController(){
    
}


void huafeiPreViewController::viewDidLoad(){
    winSize = this->getView()->getBounds().size;
    
    if (p_TableView!=NULL) {
        this->getView()->removeSubview(p_TableView);
        p_TableView = NULL;
    }
    
    p_TableView = CATableView::createWithFrame(this->getView()->getBounds());
    p_TableView->setTableViewDataSource(this);
    p_TableView->setTableViewDelegate(this);
    p_TableView->setAllowsSelection(true);
    this->getView()->addSubview(p_TableView);
    
    //    CAView * head = CAView::createWithFrame(CADipRect(0,0,winSize.width,150), CAColor_red);
    //    CALabel * label = CALabel::createWithCenter(CADipRect(winSize.width/2, 75, winSize.width, 50));
    //    label->setColor(CAColor_white);
    //    label->setTextAlignment(CATextAlignmentCenter);
    //    label->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    //    label->setTag(100);
    //    head->addSubview(label);
    //
    //    p_TableView->setTableHeaderView(head);
    //    p_TableView->setTableHeaderHeight(150);
    //
    //    this->onRequest();
    
    
}

void huafeiPreViewController::viewDidAppear(){
    
}

void huafeiPreViewController::viewDidUnload(){
    
}

void huafeiPreViewController::tableViewDidSelectRowAtIndexPath(CrossApp::CATableView *table, unsigned int section, unsigned int row){
    if (section == 0 ) {
        int money = 0;
        if (row == 0) {
            money = 10;
        }else if (row == 1){
            money = 28;
        }else if (row == 2){
            money = 46;
        }else if (row == 3){
            money = 90;
        }
        
        huaFeiViewController * huaFeiViewController = new class huaFeiViewController(money);
        huaFeiViewController->setTitle("话费充值");
        huaFeiViewController->autorelease();
        RootWindow::getInstance()->getRootNavigationController()->pushViewController(huaFeiViewController, true);
    }
}

void huafeiPreViewController::tableViewDidDeselectRowAtIndexPath(CrossApp::CATableView *table, unsigned int section, unsigned int row){
    
}


CAView* huafeiPreViewController::tableViewSectionViewForHeaderInSection(CrossApp::CATableView *table, const CrossApp::CCSize &viewSize, unsigned int section){
    
    CAView* view = CAView::createWithColor(ccc4(166, 166, 166, 50));
    
    return view;
}

CAView* huafeiPreViewController::tableViewSectionViewForFooterInSection(CATableView* table, const CCSize& viewSize, unsigned int section)
{
    CAView* view = CAView::createWithColor(CAColor_red);
    
    return view;
}

CATableViewCell* huafeiPreViewController::tableCellAtIndex(CATableView* table, const CCSize& cellSize, unsigned int section, unsigned int row)
{
    CCLog("row = %d , section = %d", row, section);
    CADipSize _size = cellSize;
    CATableViewCell* p_Cell = p_TableView->dequeueReusableCellWithIdentifier("2155");
    if (p_Cell == NULL)
    {
        p_Cell = CATableViewCell::create("2155");
        p_Cell->setAllowsSelected(false);
        
        CALabel* itemText = CALabel::createWithCenter(CADipRect(_size.width/2, _size.height/2, _size.width-200,80));
        itemText->setTag(100);
        itemText->setFontSize(_px(30));
        itemText->setTextAlignment(CATextAlignmentCenter);
        itemText->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
        p_Cell->addSubview(itemText);
        
        CALabel* itemText2 = CALabel::createWithCenter(CADipRect(_size.width - 80, _size.height/2, _size.width-200,80));
        itemText2->setTag(101);
        itemText2->setFontSize(_px(25));
        itemText2->setTextAlignment(CATextAlignmentCenter);
        itemText2->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
        p_Cell->addSubview(itemText2);
    }
    
    
    CALabel * label = (CALabel*)p_Cell->getSubviewByTag(100);
    label->setText(unicode_to_utf8(huafeiMenu[row]));
    label->setColor(CAColor_black);
    
    CALabel * label1 = (CALabel*)p_Cell->getSubviewByTag(101);
    label1->setText(unicode_to_utf8(huafeiMenu[row+4]));
    label1->setColor(CAColor_red);
    
    return p_Cell;
    
}



unsigned int huafeiPreViewController::numberOfRowsInSection(CATableView *table, unsigned int section)
{
    int cellnum = 0;
    if (section==0) {
        cellnum = 4;
    }else if (section==1){
        cellnum = 1;
    }
    return cellnum;
}

unsigned int huafeiPreViewController::numberOfSections(CATableView *table)
{
    return 1;
}
unsigned int huafeiPreViewController::tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    return _px(100);
}

unsigned int huafeiPreViewController::tableViewHeightForHeaderInSection(CATableView* table, unsigned int section)
{
    return _px(20);
}

unsigned int huafeiPreViewController::tableViewHeightForFooterInSection(CATableView* table, unsigned int section)
{
    return 1;
}

void huafeiPreViewController::onQuitBtn(CrossApp::CAControl *btn, CrossApp::CCPoint point){
    
}


void huafeiPreViewController::onRequest(){
    //    std::map<std::string,
    //    std::string> key_value;
    //    char strMid[50];
    //    sprintf(strMid, "%d", RootWindow::getInstance()->getMid());
    //    key_value.insert(make_pair("mid", strMid));
    //    char signScr[200];
    //    sprintf(signScr, "%smid%s",App_key, strMid);
    //    key_value.insert(make_pair("sign", MD5(signScr).md5()));
    //
    //
    //    char temurl[200];
    //    sprintf(temurl, "http://android.2155.com/i/%s",basicTag[2]);
    //    CommonHttpManager::getInstance()->send_post(temurl, key_value, this,
    //                                                CommonHttpJson_selector(MyViewController::onRequestFinished));
}


void huafeiPreViewController::onRequestFinished(const HttpResponseStatus &status, const CSJson::Value &json){
    //    CCLog("HttpResponseStatus %d", status);
    //    if (status == HttpResponseSucceed) {
    //        const CSJson::Value& value = json["msg"];
    //        int length = value.size();
    //
    //        CCLog("length = %d ", length);
    //
    //        string myMoney = value["account"].asString();
    //
    //        CALabel* label = (CALabel*)p_TableView->getTableHeaderView()->getSubviewByTag(100);
    //        label->setText("我的余额："+myMoney+"元");
    //        
    //    }
}


