#include "CommonHttpManager.h"

#define _T(x) L##x
#define CHAR    wchar_t

static const char* App_key = "5fe1be9a5c61fecd5be7277f0d2ea7a9";

static const char* basicTag[5] =
{
    "fastlogin",
    "login",
    "userinfo",
    "prentice_info",
    "union_info"
};

static const char* MakeMoneyTag[4] =
{
    "union_list",
    "forward_duty_list",
    "union_info",
    "forward_duty_info"
};

//首页

struct userInfo
{
    std::string m_account;
	std::string m_today_income;
	std::string m_today_tu;
    std::string m_isOld_user;
};

static const CHAR* mainMenuTag[4] =
{
    _T("快速赚钱"), _T("分享赚钱"), _T("开发中。。"), _T("夺宝")
};

static const CHAR* mainMenuTag2[4] =
{
    _T("安装应用超赚钱"), _T("参与分享赚更多"), _T("开发中。。"), _T("全民参与拿大奖")
};

//兑换
static const CHAR* exChangeMenuTag[2] =
{
    _T("话费充值"), _T("支付宝提现")
};

static const CHAR* exChangeMenuTag2[2] =
{
    _T("快速充值，充的多送的多"), _T("直接提现，快速安全")
};

static const CHAR* zhifubaoMenu[8] =
{
    _T("支付宝提现10元"),
    _T("支付宝提现30元"),
    _T("支付宝提现50元"),
    _T("支付宝提现100元"),
    _T("优惠价：10元"),
    _T("优惠价：28元"),
    _T("优惠价：46元"),
    _T("优惠价：90元")
};

static const CHAR* huafeiMenu[8] =
{
    _T("手机话费提现10元"),
    _T("手机话费提现30元"),
    _T("手机话费提现50元"),
    _T("手机话费提现100元"),
    _T("优惠价：10元"),
    _T("优惠价：28元"),
    _T("优惠价：46元"),
    _T("优惠价：90元")
};


//赚钱
struct MakeMoneyMsg
{
    std::string m_id;
    std::string m_title;
    std::string m_short_desc;
    std::string m_imageUrl;
    std::string m_add_money;
    std::string m_status;
};

static const CHAR* MakeMoneyTitile[2] =
{
    _T("请选择任意手机赚钱任务，下载，安装玩游戏，就能每天秦松赚入零花钱。玩越多赚越多，现在就开始吧"),
    _T("请选择任意分享任务，按提示完成微信转发或公众号关注，就能轻松获取现金了，马上去分享吧")
};

static const CHAR* ShareStatusTitile[3] =
{
    _T("未分享"),
    _T("已分享"),
    _T("已到量")
};

struct ShareDetailMsg
{
    std::string m_id;
    std::string m_title;
    std::string m_imageUrl;
    std::string m_add_money;
    std::string m_read_num;
    std::string m_money_get;
    std::string m_demo_url;
    std::string m_preview_url;
};

struct UnionDetailMsg
{
    std::string m_id;
    std::string m_title;
    std::string m_imageUrl;
    std::string m_add_money;
    std::string m_desc;
    std::string m_url;
};

static std::string ShareUid;




///师徒
struct shareToFriendMsg
{
	std::string m_title;
	std::string m_desc;
	std::string m_img;
    std::string m_share_url;
};

struct TudiMsg
{
    std::string tudi_amount;
    std::string tudi_count;
    std::string tudi_reward;
    std::string tusun_amount;
    std::string tusun_count;
    std::string tusun_reward;
    
    std::vector<std::string> mytudisInfo;
};

static const CHAR* shouTuTip[2] =
{
    _T("为什么要收徒弟？（必读）"), _T("如何收取更多的徒弟？（必读）")
};




//我的
static const CHAR* aboutMenuTag[5] =
{
	_T("我的账号"),
    _T("我的消息"),
    _T("任务记录"),
    _T("兑换记录"),
    _T("常见问题")
};
