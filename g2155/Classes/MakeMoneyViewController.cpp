//
//  MakeMoneyViewController.cpp
//  2155
//
//  Created by 邱宇青 on 15/6/9.
//
//

#include "MakeMoneyViewController.h"
#include "ShareViewController.h"
#include "UnionViewController.h"

MakeMoneyViewTableCell::MakeMoneyViewTableCell()
{
    this->setAllowsSelected(false);
}

MakeMoneyViewTableCell::~MakeMoneyViewTableCell()
{
    
}

MakeMoneyViewTableCell* MakeMoneyViewTableCell::create(const std::string& identifier, const CADipRect& _rect)
{
    MakeMoneyViewTableCell* tableViewCell = new MakeMoneyViewTableCell();
    if(tableViewCell&&tableViewCell->initWithReuseIdentifier(identifier))
    {
        tableViewCell->setFrame(_rect);
        tableViewCell->autorelease();
        return tableViewCell;
    }
    CC_SAFE_DELETE(tableViewCell);
    return NULL;
}

void MakeMoneyViewTableCell::highlightedTableViewCell()
{
    this->setBackgroundView(CAView::createWithColor(CAColor_blue));
}

void MakeMoneyViewTableCell::selectedTableViewCell()
{
    this->setBackgroundView(CAView::createWithColor(CAColor_blue));
}

void MakeMoneyViewTableCell::initWithCell()
{
    CADipSize _size = this->getFrame().size;
    CALabel* test = CALabel::createWithFrame(CADipRect(120,
                                                       20,
                                                       _size.width/2+50,
                                                       40));
    test->setColor(CAColor_black);
    test->setTextAlignment(CATextAlignmentLeft);
    test->setVerticalTextAlignmet(CAVerticalTextAlignmentTop);
    test->setFontSize(_px(30));
//    test->setBold(true);
    test->setTag(100);
    this->addSubview(test);
    
    CALabel* dsc = CALabel::createWithFrame(CADipRect(120,
                                                      80,
                                                      _size.width/2,
                                                      40));
    dsc->setTextAlignment(CATextAlignmentLeft);
    dsc->setVerticalTextAlignmet(CAVerticalTextAlignmentTop);
    dsc->setFontSize(_px(24));
    dsc->setTag(102);
    dsc->setColor(ccc4(180,180,180,255));
//    dsc->setLineSpacing(10);
    this->addSubview(dsc);
    
    CALabel* addMoney = CALabel::createWithCenter(CADipRect(_size.width - 50, _size.height/2, 100, 100));
    addMoney->setColor(CAColor_red);
    addMoney->setTextAlignment(CATextAlignmentLeft);
    addMoney->setVerticalTextAlignmet(CAVerticalTextAlignmentTop);
    addMoney->setFontSize(_px(32));
    addMoney->setTag(104);
    this->addSubview(addMoney);
    
    CALabel* status = CALabel::createWithCenter(CADipRect(_size.width - 50, _size.height/5*4, 100, 100));
    status->setColor(CAColor_gray);
    status->setTextAlignment(CATextAlignmentLeft);
    status->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    status->setFontSize(_px(28));
    status->setTag(105);
    this->addSubview(status);
    

    CommonUrlImageView* temImage = CommonUrlImageView::createWithCenter(CADipRect(50,_size.height/2,74,74));
    temImage->setTag(106);
    temImage->setImageViewScaleType(CAImageViewScaleTypeFitImageCrop);
    temImage->setImage(CAImage::create("source_material/btn_right_blue.png"));
    this->addSubview(temImage);
    
    
    
}

MakeMoneyViewController::MakeMoneyViewController(int index)
:p_TableView(NULL)
{
    urlID = index;
    m_makeMoneyList.clear();

}

MakeMoneyViewController::~MakeMoneyViewController(){
    
}

void MakeMoneyViewController::viewDidLoad()
{
    winSize = this->getView()->getBounds().size;
    
    
    if (m_makeMoneyList.empty())
    {
        this->onRequest();
    }
    else
    {
        this->initTableView();
    }
}

void MakeMoneyViewController::viewDidAppear(){
   
    RootWindow::getInstance()->getRootTabBarontroller()->setNavigationBarItem(CANavigationBarItem::create("日常任务"));
//    this->onRequest();
}

void MakeMoneyViewController::onRequest(){
    std::map<std::string,std::string> key_value;
    
    cc_timeval  time;
    CCTime::gettimeofdayCrossApp(&time, NULL);
    char strTime[50];
    sprintf(strTime, "%d", time.tv_usec);
    key_value.insert(make_pair("time", strTime));
    
    char signScr[200];
    if (urlID == 1) {
        char strMid[20];
        sprintf(strMid, "%d", RootWindow::getInstance()->getMid());
        key_value.insert(make_pair("mid", strMid));
        
        sprintf(signScr, "%smid%stime%s",App_key, strMid, strTime);
        key_value.insert(make_pair("sign", MD5(signScr).md5()));
    }else{
        sprintf(signScr, "%stime%s",App_key, strTime);
        key_value.insert(make_pair("sign", MD5(signScr).md5()));
    }
    
    char temurl[200];
    sprintf(temurl, "http://android.2155.com/i/%s",MakeMoneyTag[urlID]);
    CommonHttpManager::getInstance()->send_post(temurl, key_value, this,
                                                CommonHttpJson_selector(MakeMoneyViewController::onRequestFinished),true);
    
}

void MakeMoneyViewController::showAlert()
{
    p_alertView = CAView::createWithFrame(this->getView()->getBounds());
    this->getView()->addSubview(p_alertView);
    
    
    CAButton* btn5 = CAButton::create(CAButtonTypeSquareRect);
    btn5->setTag(100);
    btn5->setCenter(CADipRect(winSize.width/2, winSize.height/2, winSize.width, winSize.height));
    btn5->setTitleColorForState(CAControlStateNormal,CAColor_white);
    btn5->addTarget(this, CAControl_selector(MakeMoneyViewController::buttonCallBack), CAControlEventTouchUpInSide);
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

void MakeMoneyViewController::buttonCallBack(CAControl* btn,CCPoint point)
{
    this->getView()->removeSubview(p_alertView);
    p_alertView = NULL;

    this->onRequest();
    
}

void MakeMoneyViewController::onRequestFinished(const HttpResponseStatus& status, const CSJson::Value& json)
{
    if (status == HttpResponseSucceed)
    {
        const CSJson::Value& value = json["msg"];
        int length = value.size();

        m_makeMoneyList.clear();
        for (int index = 0; index < length; index++)
        {
            MakeMoneyMsg temp_msg;
            temp_msg.m_id = value[index]["id"].asString();
            temp_msg.m_title =   value[index]["title"].asString();
            CCLog("title==%s",value[index]["title"].asString().c_str());
            temp_msg.m_imageUrl = value[index]["icon"].asString();
            temp_msg.m_short_desc = value[index]["short_desc"].asString();
            temp_msg.m_add_money = value[index]["add_money"].asString();
            
            if (urlID == 1) {
                temp_msg.m_status = value[index]["status"].asString();
            }
            
            m_makeMoneyList.push_back(temp_msg);
            
        }
        
        this->initTableView();
        
    }
    

    
}



void MakeMoneyViewController::initTableView()
{
    if (m_makeMoneyList.empty())
    {
        showAlert();
        return;
    }
    if (p_TableView!=NULL)
    {
        this->getView()->removeSubview(p_TableView);
        p_TableView = NULL;
    }
    
    p_TableView= CATableView::createWithFrame(CADipRect(0, 0, winSize.width, winSize.height));
    p_TableView->setTableViewDataSource(this);
    p_TableView->setTableViewDelegate(this);
    p_TableView->setAllowsSelection(true);
    this->getView()->addSubview(p_TableView);
    
    CAView* headview = CAView::create();
    headview->setColor(ccc4(166, 166, 166, 80));
    
    CALabel* label = CALabel::createWithFrame(CADipRect(0,0,winSize.width,100));
    label->setText("     "+unicode_to_utf8(MakeMoneyTitile[urlID]));
    label->setFontSize(_px(20));
    label->setTextAlignment(CATextAlignmentLeft);
    label->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    headview->addSubview(label);
    
    p_TableView->setTableHeaderView(headview);
    p_TableView->setTableHeaderHeight(_px(100));
}



void MakeMoneyViewController::viewDidUnload()
{
    
}

void MakeMoneyViewController::tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    
    if (urlID == 0) {
        UnionViewController * unionViewController = new UnionViewController(m_makeMoneyList[row].m_id);
        unionViewController->setTitle("赚钱");
        unionViewController->autorelease();
        
        RootWindow::getInstance()->getRootNavigationController()->pushViewController(unionViewController, true);
        
    }else if (urlID == 1){
        ShareViewController * shareViewController = new ShareViewController(m_makeMoneyList[row].m_id);
        shareViewController->init();
        shareViewController->setTitle("微信分享");
        shareViewController->autorelease();
        
        RootWindow::getInstance()->getRootNavigationController()->pushViewController(shareViewController, true);
    }
    
}

void MakeMoneyViewController::tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    
}

CATableViewCell* MakeMoneyViewController::tableCellAtIndex(CATableView* table, const CCSize& cellSize, unsigned int section, unsigned int row)
{
    CADipSize _size = cellSize;
    MakeMoneyViewTableCell* cell = dynamic_cast<MakeMoneyViewTableCell*>(table->dequeueReusableCellWithIdentifier("2155"));
    if (cell == NULL)
    {
        cell = MakeMoneyViewTableCell::create("2155", CADipRect(0, 0, _size.width, _size.height));
        cell->initWithCell();
    }
    CCLog("section==%d,row===%d",section,row);
    
    CALabel* cellText = (CALabel*)cell->getSubviewByTag(100);
    cellText->setText(m_makeMoneyList[row].m_title);
    
    CALabel* cellTextdsc = (CALabel*)cell->getSubviewByTag(102);
    cellTextdsc->setText(m_makeMoneyList[row].m_short_desc);
    
    CALabel* cellTextAddMoney = (CALabel*)cell->getSubviewByTag(104);
    cellTextAddMoney->setText("+" + m_makeMoneyList[row].m_add_money + "元");
    
    if (urlID == 1) {
        CALabel* cellTextStatus = (CALabel*)cell->getSubviewByTag(105);
        CCString *str =  CCString::create(m_makeMoneyList[row].m_status);
        cellTextStatus->setText(unicode_to_utf8(ShareStatusTitile[str->intValue()]));
    }
    
    CommonUrlImageView* temImage = (CommonUrlImageView*)cell->getSubviewByTag(106);
    temImage->setImageViewScaleType(CAImageViewScaleTypeFitImageCrop);
    temImage->setImage(CAImage::create("source_material/btn_right_blue.png"));
    temImage->setUrl(m_makeMoneyList[row].m_imageUrl);
    
    CCLog("cur Url = %s", m_makeMoneyList[row].m_imageUrl.c_str());
    
    return cell;
    
}

unsigned int MakeMoneyViewController::numberOfSections(CATableView *table)
{
    return 1;
}

unsigned int MakeMoneyViewController::numberOfRowsInSection(CATableView *table, unsigned int section)
{
    return m_makeMoneyList.size();
}

unsigned int MakeMoneyViewController::tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    return _px(150);
}

