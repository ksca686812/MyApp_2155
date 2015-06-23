//
//  ExchangeViewController.h
//  2155
//
//  Created by 邱宇青 on 15/6/9.
//
//

#ifndef ___155__ExchangeViewController__
#define ___155__ExchangeViewController__

#include <stdio.h>
#include "RootWindow.h"

class ExchangeViewTableCell : public CATableViewCell
{
public:
    ExchangeViewTableCell();
    virtual ~ExchangeViewTableCell();
    static ExchangeViewTableCell* create(const std::string& identifier, const CADipRect& _rect = CADipRectZero);
    virtual void highlightedTableViewCell();
    virtual void selectedTableViewCell();
public:
    void initWithCell();
};


class ExchangeViewController : public CAViewController,CATableViewDelegate,CATableViewDataSource
{
public:
    ExchangeViewController();
    virtual ~ExchangeViewController();
    
    void viewDidLoad();
    
    void viewDidAppear();
    
    void viewDidUnload();
    
    CREATE_FUNC(ExchangeViewController);
    
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
    CADipSize winSize;
    CATableView* p_TableView;
};



#endif /* defined(___155__ExchangeViewController__) */
