//
//  ExchangeViewController.cpp
//  2155
//
//  Created by 邱宇青 on 15/6/9.
//
//

#include "ExchangeViewController.h"
#include "huaFeiViewController.h"
#include "zhifubaoViewController.h"


ExchangeViewTableCell::ExchangeViewTableCell(){
    this->setAllowsSelected(false);
}

ExchangeViewTableCell::~ExchangeViewTableCell(){
    
}

ExchangeViewTableCell* ExchangeViewTableCell::create(const std::string& identifier, const CADipRect& _rect){
    
    return NULL;
}

void ExchangeViewTableCell::highlightedTableViewCell(){
    this->setBackgroundView(CAView::createWithColor(ccc4(0, 0, 0, 64)));
}


void ExchangeViewTableCell::selectedTableViewCell(){
    this->setBackgroundView(CAView::createWithColor(ccc4(0, 0, 0, 64)));
}


void ExchangeViewTableCell::initWithCell(){
    
}



ExchangeViewController::ExchangeViewController(){
    
}

ExchangeViewController::~ExchangeViewController(){
    
}


void ExchangeViewController::viewDidLoad(){
    winSize = this->getView()->getBounds().size;
    
    if (p_TableView!=NULL) {
        this->getView()->removeSubview(p_TableView);
        p_TableView = NULL;
    }
    
    p_TableView = CATableView::createWithFrame(this->getView()->getBounds());
    p_TableView->setTableViewDataSource(this);
    p_TableView->setTableViewDelegate(this);
    p_TableView->setAllowsSelection(true);
    p_TableView->setScrollEnabled(false);
    p_TableView->setSeparatorColor(CAColor_blue);
    this->getView()->addSubview(p_TableView);
    
    
}

void ExchangeViewController::viewDidAppear(){
    
    RootWindow::getInstance()->getRootTabBarontroller()->setNavigationBarItem(CANavigationBarItem::create("兑换"));
}

void ExchangeViewController::viewDidUnload(){
    
}

void ExchangeViewController::tableViewDidSelectRowAtIndexPath(CrossApp::CATableView *table, unsigned int section, unsigned int row){
    if (row == 0) {
        huafeiPreViewController * huafeiPreViewController = huafeiPreViewController::create();
        huafeiPreViewController->setTitle("话费充值");
        RootWindow::getInstance()->getRootNavigationController()->pushViewController(huafeiPreViewController, true);
        
    }else if (row == 1){
        zhifubaoPreViewController * zhifubaoPreViewController = zhifubaoPreViewController::create();
        zhifubaoPreViewController->setTitle("支付宝提现");
        RootWindow::getInstance()->getRootNavigationController()->pushViewController(zhifubaoPreViewController, true);
    }
}

void ExchangeViewController::tableViewDidDeselectRowAtIndexPath(CrossApp::CATableView *table, unsigned int section, unsigned int row){
    
}


CAView* ExchangeViewController::tableViewSectionViewForHeaderInSection(CrossApp::CATableView *table, const CrossApp::CCSize &viewSize, unsigned int section){
    
    CAView* view = CAView::createWithColor(CAColor_white);
    
    return view;
}

CAView* ExchangeViewController::tableViewSectionViewForFooterInSection(CATableView* table, const CCSize& viewSize, unsigned int section)
{
    CAView* view = CAView::createWithColor(CAColor_white);
    
    return view;
}

CATableViewCell* ExchangeViewController::tableCellAtIndex(CATableView* table, const CCSize& cellSize, unsigned int section, unsigned int row)
{
    
    CCLog("row = %d , section = %d", row, section);
    CADipSize _size = cellSize;
    CATableViewCell* p_Cell = p_TableView->dequeueReusableCellWithIdentifier("2155");
    if (p_Cell == NULL )
    {
        p_Cell = CATableViewCell::create("2155");
        p_Cell->setAllowsSelected(false);
        
        CAView* itemImage = CAView::createWithFrame(CADipRect(0, 0, _size.width, _size.height));
        itemImage->setColor(ccc4(244, 243, 243, 255));
        itemImage->setTag(99);
        p_Cell->addSubview(itemImage);
        
        CADipSize itemSize = itemImage->getBounds().size;
        CALabel* itemText = CALabel::createWithCenter(CADipRect(itemSize.width/2, itemSize.height/3, itemSize.width,40));
        itemText->setTag(100);
        itemText->setFontSize(_px(35));
        itemText->setTextAlignment(CATextAlignmentCenter);
        itemText->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
        p_Cell->addSubview(itemText);
        
        CALabel* itemText2 = CALabel::createWithCenter(CADipRect(itemSize.width/2, itemSize.height/5*4, itemSize.width,40));
        itemText2->setTag(101);
        itemText2->setFontSize(_px(25));
        itemText2->setTextAlignment(CATextAlignmentCenter);
        itemText2->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
        p_Cell->addSubview(itemText2);
        
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
    
    CALabel * label = (CALabel*)p_Cell->getSubviewByTag(100);
    label->setText( unicode_to_utf8(exChangeMenuTag[row]) );
    label->setColor(CAColor_black);
    
    CALabel* label2 = (CALabel*)p_Cell->getSubviewByTag(101);
    label2->setText(unicode_to_utf8(exChangeMenuTag2[row]));
    label2->setColor(CAColor_gray);
    
    
   
    
    return p_Cell;

}



unsigned int ExchangeViewController::numberOfRowsInSection(CATableView *table, unsigned int section)
{
    int cellnum = 0;
    if (section==0) {
        cellnum = 2;
    }else if (section==1){
        cellnum = 6;
    }
    else if (section==2){
        cellnum = 4;
    }
    return cellnum;
}

unsigned int ExchangeViewController::numberOfSections(CATableView *table)
{
    return 1;
}
unsigned int ExchangeViewController::tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    return _px(120);
}

unsigned int ExchangeViewController::tableViewHeightForHeaderInSection(CATableView* table, unsigned int section)
{
    return _px(0);
}

unsigned int ExchangeViewController::tableViewHeightForFooterInSection(CATableView* table, unsigned int section)
{
    return 1;
}