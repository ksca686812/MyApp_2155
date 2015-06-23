

#ifndef __HelloCpp__RootWindow__
#define __HelloCpp__RootWindow__

#include <iostream>
#include "CrossApp.h"
#include "CDData.h"

USING_NS_CC;

class RootWindow: public CAWindow
{
    
public:

	static RootWindow* getInstance();
    
	RootWindow();
    
	virtual ~RootWindow();
    
    virtual bool init();
    
    CC_SYNTHESIZE_READONLY(CANavigationController*, m_pRootNavigationController, RootNavigationController);
    
    CC_SYNTHESIZE_READONLY(CATabBarController*, m_pRootTabBarontroller, RootTabBarontroller);
    
    
    //用户ID
    CC_SYNTHESIZE_READONLY(int, m_mid, Mid);
    
public:
    
    void onRequestFinished(const HttpResponseStatus& status, const CSJson::Value& json);
    void onSave_forward_logRequest(const HttpResponseStatus& status, const CSJson::Value& json);
    
    
    void initMainView();
    

    
};


#endif /* defined(__HelloCpp__ViewController__) */
