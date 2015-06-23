//
//  MainViewController.cpp
//  2155
//
//  Created by 邱宇青 on 15/6/9.
//
//

#include "MainViewController.h"


MainViewController::MainViewController(){
    
}

MainViewController::~MainViewController(){
    
}


void MainViewController::onNaviBarRightButClick(CrossApp::CAControl *, CrossApp::CCPoint){
    CCLog("click");
}


void MainViewController::viewDidLoad(){
    winSize = this->getView()->getBounds().size;
    
    CCLog("win Size w == %f, h = %f", winSize.width, winSize.height);
}

void MainViewController::viewDidAppear(){
    CANavigationBarItem * barItem = CANavigationBarItem::create("2155");
//    CABarButtonItem * rightBtn = CABarButtonItem::create("", CAImage::create("source_material/btn_left_white.png"), CAImage::create("source_material/btn_left_white.png"));
//    rightBtn->setTarget(this, CAControl_selector(MainViewController::onNaviBarRightButClick));
//    barItem->addRightButtonItem(rightBtn);

    RootWindow::getInstance()->getRootTabBarontroller()->setNavigationBarItem(barItem);
    
    
    this->onRequest();
}




void MainViewController::viewDidUnload(){
    
}

void MainViewController::collectionViewDidSelectCellAtIndexPath(CACollectionView *collectionView, unsigned int section, unsigned int row, unsigned int item){
    if (section == 1 && row == 0) {
        RootWindow::getInstance()->getRootTabBarontroller()->showSelectedViewControllerAtIndex(2);
    }
    
    
}

void MainViewController::collectionViewDidDeselectCellAtIndexPath(CACollectionView *collectionView, unsigned int section, unsigned int row, unsigned int item){
    
}


CAView* MainViewController::collectionViewSectionViewForHeaderInSection(CACollectionView *collectionView, const CCSize& viewSize, unsigned int section){
    
    CAView* view = CAView::createWithColor(ccc4(160, 160, 160, 20));
    
    return view;
}



CACollectionViewCell* MainViewController::collectionCellAtIndex(CACollectionView *collectionView, const CCSize& cellSize, unsigned int section, unsigned int row, unsigned int item)
{
    CCLog("row = %d , item = %d", row, item);
    CADipSize _size = cellSize;
    CACollectionViewCell* p_Cell = collectionView->dequeueReusableCellWithIdentifier("2155");
    if (p_Cell == NULL && section == 0)
    {
        p_Cell = CACollectionViewCell::create("2155");
        p_Cell->setAllowsSelected(false);
        
        CADipRect rect = CADipRect(_size.width/2,_size.height/2, _size.width+collectionView->getHoriInterval()*2, _size.height + collectionView->getVertInterval()*2);
        CAView* itembg = CAView::createWithCenter(rect);
        itembg->setColor(CAColor_gray);
        itembg->setTag(98);
        p_Cell->addSubview(itembg);
        
        CAView* itemImage = CAView::createWithFrame(CADipRect(0, 0, _size.width, _size.height));
        itemImage->setColor(ccc4(244, 243, 243, 255));
        itemImage->setTag(99);
        p_Cell->addSubview(itemImage);
        
        CADipSize itemSize = itemImage->getBounds().size;
        CALabel* itemText = CALabel::createWithCenter(CADipRect(itemSize.width/4, itemSize.height/2, itemSize.width,40));
        itemText->setTag(100);
        itemText->setFontSize(_px(35));
        itemText->setText("钱购");
        itemText->setTextAlignment(CATextAlignmentCenter);
        itemText->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
        p_Cell->addSubview(itemText);
        
        CAScale9ImageView* iv = CAScale9ImageView::createWithCenter(CADipRect(itemSize.width-50,itemSize.height/2,50,50));
        iv->setImage(CAImage::create("source_material/cell_btn_right.png"));
        iv->setTag(101);
        p_Cell->addSubview(iv);
        
        CAImageView* icon = CAImageView::createWithCenter(CADipRect(50,itemSize.height/2,64,64));
        icon->setTag(101);
        icon->setScale(0.6f);
        icon->setImage(CAImage::create("source_material/btn_right_blue.png"));
        p_Cell->addSubview(icon);
    }
    
    if (p_Cell == NULL && section == 1) {
        p_Cell = CACollectionViewCell::create("2155");
        p_Cell->setAllowsSelected(false);
        
        CADipRect rect = CADipRect(_size.width/2,_size.height/2, _size.width+collectionView->getHoriInterval()*2, _size.height + collectionView->getVertInterval()*2);
        CAView* itembg = CAView::createWithCenter(rect);
        itembg->setColor(CAColor_gray);
        itembg->setTag(98);
        p_Cell->addSubview(itembg);
        
        CAView* itemImage = CAView::createWithFrame(CADipRect(0, 0, _size.width, _size.height));
        itemImage->setColor(ccc4(244, 243, 243, 255));
        itemImage->setTag(99);
        p_Cell->addSubview(itemImage);
        
        CADipSize itemSize = itemImage->getBounds().size;
        CALabel* itemText = CALabel::createWithCenter(CADipRect(itemSize.width/5*4, itemSize.height/5*2, itemSize.width,40));
        itemText->setTag(100);
        itemText->setFontSize(_px(35));
        itemText->setTextAlignment(CATextAlignmentLeft);
        itemText->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
        p_Cell->addSubview(itemText);
        
        CALabel* itemText2 = CALabel::createWithCenter(CADipRect(itemSize.width/5*4, itemSize.height/5*4, itemSize.width,40));
        itemText2->setTag(101);
        itemText2->setFontSize(_px(25));
        itemText2->setTextAlignment(CATextAlignmentLeft);
        itemText2->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
        p_Cell->addSubview(itemText2);
        
        
        CAImageView* icon = CAImageView::createWithCenter(CADipRect(50,itemSize.height/2,64,64));
        icon->setTag(102);
        icon->setScale(0.6f);
        icon->setImage(CAImage::create("source_material/btn_right_blue.png"));
        p_Cell->addSubview(icon);
        
    }
    
    
    if (section == 1) {
        CALabel* itemText = (CALabel*)p_Cell->getSubviewByTag(100);
        int index = row * 2 + item;
        itemText->setText(unicode_to_utf8(mainMenuTag[index]));
        itemText->setColor(CAColor_black);
        
        CALabel* itemText2 = (CALabel*)p_Cell->getSubviewByTag(101);
        itemText2->setText(unicode_to_utf8(mainMenuTag2[index]));
        itemText2->setColor(CAColor_gray);
        
        
    }
    
    
    return p_Cell;
}





//view 中 Section数量
unsigned int MainViewController::numberOfSections(CACollectionView *collectionView)
{
    return 2;
}

//每个section包括几个cell
unsigned int MainViewController::numberOfRowsInSection(CACollectionView *collectionView, unsigned int section)
{
    int cellnum = 0;
    if (section==0) {
        cellnum = 1;
    }else if (section==1){
        cellnum = 2;
    }
    CCLog("cellnum = %d", cellnum);
    return cellnum;
}

//每个cell里的item数量
unsigned int MainViewController::numberOfItemsInRowsInSection(CrossApp::CACollectionView *collectionView, unsigned int section, unsigned int row)
{
    int itemnum = 0;
    if (section==0) {
        itemnum = 1;
    }else if (section==1){
        itemnum = 2;
    }
    CCLog("itemnum = %d", itemnum);
    return itemnum;
}

//cell的高度
unsigned int MainViewController::collectionViewHeightForRowAtIndexPath(CACollectionView* collectionView, unsigned int section, unsigned int row)
{
    return _px(150);
}

//每个section的headerView 高度
unsigned int MainViewController::collectionViewHeightForHeaderInSection(CACollectionView *collectionView, unsigned int section)
{
    int h = 20;
    if (section==0) {
        h=30;
    }
    return _px(h);
}

void MainViewController::initView(){
    if (p_Conllection!=NULL) {
        this->getView()->removeSubview(p_Conllection);
        p_Conllection = NULL;
    }
    
    p_Conllection = CACollectionView::createWithFrame(this->getView()->getBounds());
    p_Conllection->setAllowsSelection(true);
    p_Conllection->setCollectionViewDelegate(this);
    p_Conllection->setCollectionViewDataSource(this);
    p_Conllection->setHoriInterval(_px(3));
    p_Conllection->setVertInterval(_px(3));
    p_Conllection->setCollectionHeaderHeight(_px(400));
    
    this->getView()->addSubview(p_Conllection);
    
    
    
    CAView* view = CAView::createWithColor(CAColor_red);
    view->setFrame(CCRect(0, 0, winSize.width, 400));
    
    CALabel* label = CALabel::createWithCenter(CADipRect(150, 25, 300, 60));
    label->setText("我的余额（元）");
    label->setColor(CAColor_white);
    label->setFontSize((_px(36)));
    label->setBold(true);
    label->setTag(100);
    label->setTextAlignment(CATextAlignmentCenter);
    label->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    view->addSubview(label);
    
    CALabel* label1 = CALabel::createWithCenter(CADipRect(winSize.width-150, 25, 300, 60));
    char strLabel[50];
    sprintf(strLabel, "ID:%d", RootWindow::getInstance()->getMid());
    label1->setText(strLabel);
    label1->setColor(CAColor_white);
    label1->setFontSize((_px(36)));
    label1->setBold(true);
    label1->setTextAlignment(CATextAlignmentCenter);
    label1->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    view->addSubview(label1);
    
    CALabel* label2 = CALabel::createWithCenter(CADipRect(winSize.width/2, 400/2-25, 300, 60));
    label2->setText(m_userInfo.m_account);
    label2->setColor(CAColor_white);
    label2->setFontSize((_px(50)));
    label2->setBold(true);
    label2->setTextAlignment(CATextAlignmentCenter);
    label2->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    view->addSubview(label2);
    
    CAButton* but1 = CAButton::create(CAButtonTypeSquareRect);
    CAView * butBg = CAView::createWithColor(ccc4(0, 0, 0, 60));
    but1->setBackGroundViewForState(CAControlStateAll, butBg);
    
    but1->setCenter(CADipRect(winSize.width/4, 350, winSize.width/2-1, 100));
    but1->setTitleForState(CAControlStateAll, "今日收入 "+ m_userInfo.m_today_income +"元");
    view->addSubview(but1);
    
    CAButton* but2 = CAButton::createWithCenter(CADipRect(winSize.width/4*3, 350, winSize.width/2-1, 100), CAButtonTypeSquareRect);
    CAView * but2Bg = CAView::createWithColor(ccc4(0, 0, 0, 60));
    but2->setBackGroundViewForState(CAControlStateAll, but2Bg);
    
    but2->setTitleForState(CAControlStateAll, "今日收徒" + m_userInfo.m_today_tu +"个");
    view->addSubview(but2);
    
    p_Conllection->setCollectionHeaderView(view);

}


void MainViewController::onRequest(){
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
                                                CommonHttpJson_selector(MainViewController::onRequestFinished), true);
}


void MainViewController::onRequestFinished(const HttpResponseStatus &status, const CSJson::Value &json){
    CCLog("HttpResponseStatus %d", status);
    if (status == HttpResponseSucceed) {
        const CSJson::Value& value = json["msg"];
        int length = value.size();
        
        CCLog("length = %d ", length);
        
        m_userInfo.m_account = value["account"].asString();
        m_userInfo.m_today_income = value["today_income"].asString();
        m_userInfo.m_today_income = value["today_tu"].asString();
        m_userInfo.m_isOld_user = value["is_old_user"].asString();
        
        CCLog("m_account = %s, m_today_income = %s, m_isOld_user = %s ", m_userInfo.m_account.c_str() ,m_userInfo.m_today_income.c_str(),m_userInfo.m_isOld_user.c_str());
        
        this->initView();
        
    
    }
}











