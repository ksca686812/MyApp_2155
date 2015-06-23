//
//  TeacherAndPupilViewController.h
//  2155
//
//  Created by 邱宇青 on 15/6/9.
//
//

#ifndef ___155__TeacherAndPupilViewController__
#define ___155__TeacherAndPupilViewController__

#include <stdio.h>

#include "RootWindow.h"

class TeacherAndPupilViewTableCell : public CATableViewCell
{
public:
    TeacherAndPupilViewTableCell();
    virtual ~TeacherAndPupilViewTableCell();
    static TeacherAndPupilViewTableCell* create(const std::string& identifier, const CADipRect& _rect = CADipRectZero);
    virtual void highlightedTableViewCell();
    virtual void selectedTableViewCell();
public:
    void initWithCell();
};


class TeacherAndPupilViewController : public CAViewController,CATableViewDelegate,CATableViewDataSource
{
public:
    TeacherAndPupilViewController();
    virtual ~TeacherAndPupilViewController();
    
    void viewDidLoad();
    
    void viewDidAppear();
    
    void viewDidUnload();
    
    CREATE_FUNC(TeacherAndPupilViewController);
    
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
    void initTableView();
    void showAlert();
    void onRequest();
    void onRequestFinished(const HttpResponseStatus& status, const CSJson::Value& json);

    void onShareBtn(CAControl* btn,CCPoint point);
    void buttonCallBack(CAControl* btn,CCPoint point);
public:
    CADipSize winSize;
    CATableView* p_TableView;
    
    shareToFriendMsg m_shareMsg;
    TudiMsg          m_pageMsg;
    
    CAView* p_alertView;
};



#endif /* defined(___155__TeacherAndPupilViewController__) */
