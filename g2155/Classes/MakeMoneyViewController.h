//
//  MakeMoneyViewController.h
//  2155
//
//  Created by 邱宇青 on 15/6/9.
//
//

#ifndef ___155__MakeMoneyViewController__
#define ___155__MakeMoneyViewController__

#include <stdio.h>

#include "RootWindow.h"

class MakeMoneyViewTableCell : public CATableViewCell
{
public:
    MakeMoneyViewTableCell();
    virtual ~MakeMoneyViewTableCell();
    static MakeMoneyViewTableCell* create(const std::string& identifier, const CADipRect& _rect = CADipRectZero);
    virtual void highlightedTableViewCell();
    virtual void selectedTableViewCell();
public:
    void initWithCell();
};

class MakeMoneyViewController : public CAViewController,CATableViewDelegate,CATableViewDataSource
{
public:
    MakeMoneyViewController(int index);
    virtual ~MakeMoneyViewController();
    
    void viewDidLoad();
    
    void viewDidAppear();
    
    void viewDidUnload();
    
    //CREATE_FUNC(MakeMoneyViewController);
public:
    virtual void tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
    virtual void tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
    
    virtual CATableViewCell* tableCellAtIndex(CATableView* table, const CCSize& cellSize, unsigned int section, unsigned int row);
    virtual unsigned int numberOfRowsInSection(CATableView *table, unsigned int section);
    virtual unsigned int numberOfSections(CATableView *table);
    virtual unsigned int tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
    

public:
    
    void onRequest();
    void onRequestFinished(const HttpResponseStatus& status, const CSJson::Value& json);

    void initTableView();
    void showAlert();
    void buttonCallBack(CAControl* btn,CCPoint point);
public:
    CADipSize winSize;
     
    std::vector<MakeMoneyMsg > m_makeMoneyList;

    CATableView* p_TableView;
    
    CAView* p_alertView;
    int urlID;

};



#endif /* defined(___155__MakeMoneyViewController__) */
