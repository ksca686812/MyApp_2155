//
//  MyViewController.h
//  2155
//
//  Created by 邱宇青 on 15/6/9.
//
//

#ifndef ___155__MyViewController__
#define ___155__MyViewController__

#include <stdio.h>

#include "RootWindow.h"

class MyViewTableCell : public CATableViewCell
{
public:
    MyViewTableCell();
    virtual ~MyViewTableCell();
    static MyViewTableCell* create(const std::string& identifier, const CADipRect& _rect = CADipRectZero);
    virtual void highlightedTableViewCell();
    virtual void selectedTableViewCell();
public:
    void initWithCell();
};


class MyViewController : public CAViewController,CATableViewDelegate,CATableViewDataSource
{
public:
    MyViewController();
    virtual ~MyViewController();
    
    void viewDidLoad();
    
    void viewDidAppear();
    
    void viewDidUnload();
    
    CREATE_FUNC(MyViewController);
    
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




#endif /* defined(___155__MyViewController__) */
