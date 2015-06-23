//
//  MyViewController.cpp
//  2155
//
//  Created by 邱宇青 on 15/6/9.
//
//

#include "MyViewController.h"



MyViewTableCell::MyViewTableCell(){
    this->setAllowsSelected(false);
}

MyViewTableCell::~MyViewTableCell(){
    
}

MyViewTableCell* MyViewTableCell::create(const std::string& identifier, const CADipRect& _rect){
    
    return NULL;
}

void MyViewTableCell::highlightedTableViewCell(){
    this->setBackgroundView(CAView::createWithColor(ccc4(0, 0, 0, 64)));
}


void MyViewTableCell::selectedTableViewCell(){
    this->setBackgroundView(CAView::createWithColor(ccc4(0, 0, 0, 64)));
}


void MyViewTableCell::initWithCell(){
    
}



MyViewController::MyViewController(){
    
}

MyViewController::~MyViewController(){
    
}


void MyViewController::viewDidLoad(){
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
    
    CAView * head = CAView::createWithFrame(CADipRect(0,0,winSize.width,150), CAColor_red);
    CALabel * label = CALabel::createWithCenter(CADipRect(winSize.width/2, 75, winSize.width, 50));
    label->setColor(CAColor_white);
    label->setTextAlignment(CATextAlignmentCenter);
    label->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    label->setTag(100);
    head->addSubview(label);
    
    p_TableView->setTableHeaderView(head);
    p_TableView->setTableHeaderHeight(150);
    
    this->onRequest();
    
    
}

void MyViewController::viewDidAppear(){
    RootWindow::getInstance()->getRootTabBarontroller()->setNavigationBarItem(CANavigationBarItem::create("我的2155"));
}

void MyViewController::viewDidUnload(){
    
}

void MyViewController::tableViewDidSelectRowAtIndexPath(CrossApp::CATableView *table, unsigned int section, unsigned int row){
    
}

void MyViewController::tableViewDidDeselectRowAtIndexPath(CrossApp::CATableView *table, unsigned int section, unsigned int row){
    
}


CAView* MyViewController::tableViewSectionViewForHeaderInSection(CrossApp::CATableView *table, const CrossApp::CCSize &viewSize, unsigned int section){
    
    CAView* view = CAView::createWithColor(ccc4(166, 166, 166, 50));
    
    return view;
}

CAView* MyViewController::tableViewSectionViewForFooterInSection(CATableView* table, const CCSize& viewSize, unsigned int section)
{
    CAView* view = CAView::createWithColor(CAColor_white);
    
    return view;
}

CATableViewCell* MyViewController::tableCellAtIndex(CATableView* table, const CCSize& cellSize, unsigned int section, unsigned int row)
{
    CCLog("row = %d , section = %d", row, section);
    CADipSize _size = cellSize;
    CATableViewCell* p_Cell = p_TableView->dequeueReusableCellWithIdentifier("2155");
    if (p_Cell == NULL && section == 0)
    {
        p_Cell = CATableViewCell::create("2155");
        p_Cell->setAllowsSelected(false);
        
        CALabel* itemText = CALabel::createWithCenter(CADipRect(_size.width/2, _size.height/2, _size.width-200,80));
        itemText->setTag(100);
        itemText->setFontSize(_px(30));
        itemText->setColor(CAColor_gray);
        itemText->setTextAlignment(CATextAlignmentCenter);
        itemText->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
        p_Cell->addSubview(itemText);
    }
    
    if (p_Cell == NULL && section == 1) {
        p_Cell = CATableViewCell::create("2155");
        p_Cell->setAllowsSelected(false);
        
        CAButton * quitBtn = CAButton::createWithCenter(CADipRect(_size.width/2,_size.height/2,_size.width - 80, _size.height - 20), CAButtonTypeRoundedRect);
        quitBtn->setTitleColorForState(CAControlStateAll, CAColor_white);
        quitBtn->setBackGroundViewForState(CAControlStateAll, CAView::createWithColor(CAColor_red));
        quitBtn->setTitleForState(CAControlStateAll, "退出账号");
        quitBtn->addTarget(this, CAControl_selector(MyViewController::onQuitBtn), CAControlEventTouchUpInSide);
        p_Cell->addSubview(quitBtn);
        
    }
    
    if (section == 0) {
        CALabel * label = (CALabel*)p_Cell->getSubviewByTag(100);
        label->setText(unicode_to_utf8(aboutMenuTag[row]));
    }
    

    return p_Cell;

}



unsigned int MyViewController::numberOfRowsInSection(CATableView *table, unsigned int section)
{
    int cellnum = 0;
    if (section==0) {
        cellnum = 5;
    }else if (section==1){
        cellnum = 1;
    }
    return cellnum;
}

unsigned int MyViewController::numberOfSections(CATableView *table)
{
    return 2;
}
unsigned int MyViewController::tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    return _px(100);
}

unsigned int MyViewController::tableViewHeightForHeaderInSection(CATableView* table, unsigned int section)
{
    return _px(20);
}

unsigned int MyViewController::tableViewHeightForFooterInSection(CATableView* table, unsigned int section)
{
    return 1;
}

void MyViewController::onQuitBtn(CrossApp::CAControl *btn, CrossApp::CCPoint point){
    
}


void MyViewController::onRequest(){
    std::map<std::string,
    std::string> key_value;
    char strMid[50];
    sprintf(strMid, "%d", RootWindow::getInstance()->getMid());
    key_value.insert(make_pair("mid", strMid));
    char signScr[200];
    sprintf(signScr, "%smid%s",App_key, strMid);
    key_value.insert(make_pair("sign", MD5(signScr).md5()));
    
    
    char temurl[200];
    sprintf(temurl, "http://android.2155.com/i/%s",basicTag[2]);
    CommonHttpManager::getInstance()->send_post(temurl, key_value, this,
                                                CommonHttpJson_selector(MyViewController::onRequestFinished));
}


void MyViewController::onRequestFinished(const HttpResponseStatus &status, const CSJson::Value &json){
    CCLog("HttpResponseStatus %d", status);
    if (status == HttpResponseSucceed) {
        const CSJson::Value& value = json["msg"];
        int length = value.size();
        
        CCLog("length = %d ", length);
        
        string myMoney = value["account"].asString();
        
        CALabel* label = (CALabel*)p_TableView->getTableHeaderView()->getSubviewByTag(100);
        label->setText("我的余额："+myMoney+"元");
        
    }
}




