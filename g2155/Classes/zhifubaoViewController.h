//
//  zhifubaoViewController.h
//  g2155
//
//  Created by 邱宇青 on 15/6/17.
//
//

#ifndef __g2155__zhifubaoViewController__
#define __g2155__zhifubaoViewController__

#include <stdio.h>
#include "RootWindow.h"

class zhifubaoViewController : public CAViewController
{
public:
    zhifubaoViewController(int money);
    
    virtual ~zhifubaoViewController();
    
    void viewDidLoad();
    
    void viewDidUnload();
    
public:
    
    void onRequest(string account,string name, string money);
    void onRequestFinished(const HttpResponseStatus& status, const CSJson::Value& json);
    void initView();
    void buttonCallBack(CAControl* btn,CCPoint point);
    
    void showAlert();
public:
    CADipSize winSize;
    
    CAView* m_View;
    
    CAActivityIndicatorView* p_pLoading;
    int m_money;
};





class zhifubaoPreViewController : public CAViewController,CATableViewDelegate,CATableViewDataSource
{
public:
    zhifubaoPreViewController();
    virtual ~zhifubaoPreViewController();
    
    void viewDidLoad();
    
    void viewDidAppear();
    
    void viewDidUnload();
    
    CREATE_FUNC(zhifubaoPreViewController);
    
    virtual void tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
    virtual void tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
    virtual CAView* tableViewSectionViewForHeaderInSection(CATableView* table, const CCSize& viewSize, unsigned int section);
    virtual CAView* tableViewSectionViewForFooterInSection(CATableView* table, const CCSize& viewSize, unsigned int section);
    virtual CATableViewCell* tableCellAtIndex(CATableView* table, const CCSize& cellSize, unsigned int section, unsigned int row);
    virtual unsigned int numberOfRowsInSection(CATableView *table, unsigned int section);
    virtual unsigned int numberOfSections(CATableView *table);
    virtual unsigned int tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
    virtual unsigned int tableViewHeightForHeaderInSection(CATableView* table, unsigned int section);
    virtual unsigned int tableViewHeightForFooterInSection(CATableView* table, unsigned int section);
public:
    void onQuitBtn(CAControl* btn,CCPoint point);
    
    void onRequest();
    void onRequestFinished(const HttpResponseStatus& status, const CSJson::Value& json);
public:
    CADipSize winSize;
    CATableView* p_TableView;
};

#endif /* defined(__g2155__zhifubaoViewController__) */
