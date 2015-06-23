//
//  MainViewController.h
//  2155
//
//  Created by 邱宇青 on 15/6/9.
//
//

#ifndef ___155__MainViewController__
#define ___155__MainViewController__

#include <stdio.h>
#include "RootWindow.h"

class MainViewController : public CAViewController,CACollectionViewDelegate,CACollectionViewDataSource
{
public:
    MainViewController();
    virtual ~MainViewController();
    
    void viewDidLoad();
    
    void viewDidUnload();
    
    void viewDidAppear();
    
    CREATE_FUNC(MainViewController);
    
    //操作代理
    virtual void collectionViewDidSelectCellAtIndexPath(CACollectionView *collectionView, unsigned int section, unsigned int row, unsigned int item);
    
    virtual void collectionViewDidDeselectCellAtIndexPath(CACollectionView *collectionView, unsigned int section, unsigned int row, unsigned int item);
    
    
    //headView 的内容
    virtual CAView* collectionViewSectionViewForHeaderInSection(CACollectionView *collectionView, const CCSize& viewSize, unsigned int section);
    

    //Cell的内容
    virtual CACollectionViewCell* collectionCellAtIndex(CACollectionView *collectionView, const CCSize& cellSize, unsigned int section, unsigned int row, unsigned int item);
    //view 中 Section数量
    virtual unsigned int numberOfSections(CACollectionView *collectionView);
    //每个section包括几个cell
    virtual unsigned int numberOfRowsInSection(CACollectionView *collectionView, unsigned int section);
    //每个cell里的item数量
    virtual unsigned int numberOfItemsInRowsInSection(CACollectionView *collectionView, unsigned int section, unsigned int row);
    //cell的高度
    virtual unsigned int collectionViewHeightForRowAtIndexPath(CACollectionView* collectionView, unsigned int section, unsigned int row);
    //每个section的headerView 高度
    virtual unsigned int collectionViewHeightForHeaderInSection(CACollectionView *collectionView, unsigned int section);
    
    void initView();
    
    void onRequest();
    void onRequestFinished(const HttpResponseStatus& status, const CSJson::Value& json);
    
public:
    void onNaviBarRightButClick(CAControl*, CCPoint);
public:
    CADipSize winSize;
    CACollectionView* p_Conllection;
    
    userInfo m_userInfo;

};



#endif /* defined(___155__MainViewController__) */
