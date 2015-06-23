//
//  UnionViewController.h
//  2155
//
//  Created by 邱宇青 on 15/6/12.
//
//

#ifndef ___155__UnionViewController__
#define ___155__UnionViewController__

#include <stdio.h>

#include "RootWindow.h"

class UnionViewController : public CAViewController
{
public:
    UnionViewController(string uid);
    
    virtual ~UnionViewController();
    
    void viewDidLoad();
    
    void viewDidUnload();
    
public:
    
    void onRequest();
    void onRequestFinished(const HttpResponseStatus& status, const CSJson::Value& json);
    
    void initShareView();
    void buttonCallBack(CAControl* btn,CCPoint point);
    
    void showAlert();
    
    
public:
    CADipSize winSize;
    UnionDetailMsg m_detailMsg;
    std::string m_uid;
    
    CAView* m_UnionView;
    
};


#endif /* defined(___155__UnionViewController__) */
