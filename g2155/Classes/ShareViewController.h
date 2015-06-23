//
//  ShareViewController.h
//  2155
//
//  Created by 邱宇青 on 15/6/11.
//
//

#ifndef ___155__ShareViewController__
#define ___155__ShareViewController__

#include <stdio.h>

#include "RootWindow.h"

class ShareViewController : public CAViewController
{
public:
    ShareViewController(string uid);
    
    virtual ~ShareViewController();
    
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
    CAWebView* p_webView;
    ShareDetailMsg m_detailMsg;
    std::string m_uid;
    
    CAView* m_ShardView;
    
    CAActivityIndicatorView* p_pLoading;
};


#endif /* defined(___155__ShareViewController__) */
