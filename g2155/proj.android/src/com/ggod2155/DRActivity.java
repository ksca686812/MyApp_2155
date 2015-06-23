/*******************************************************************************
 * Copyright (c) 2015 by ehoo Corporation all right reserved.
 * 2015年2月9日 上午11:04:10
 *
 *******************************************************************************/
package com.ggod2155;

import android.app.Activity;
import android.content.Context;
import android.content.res.Configuration;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.widget.RelativeLayout;
import android.widget.Toast;

import com.dianru.sdk.DRSdk;
import com.dianru.sdk.DRSdkInterface;

public class DRActivity extends Activity implements DRSdkInterface {
    private Context context;
    private RelativeLayout drView, drMainView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        context = this;
        int typeExtra = getIntent().getIntExtra(DRSdk.DR_TYPE, -1);
        if (typeExtra == -1) {
            finish();
            return;
        }
        RelativeLayout bgView = new RelativeLayout(this);
        drView = new RelativeLayout(this);
        setContentView(bgView);
        bgView.addView(drView);
        DRSdk.layoutScreen(context, drMainView, drView);
        DRSdk.show(typeExtra, drView, context, this);
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);
        if (drMainView == null)
            return;
        DRSdk.layoutScreen(context, drMainView, drView);
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if (keyCode == KeyEvent.KEYCODE_BACK) {
            if (drMainView != null) {
                View v = drMainView.findViewWithTag(DRSdk.VIEW_TAG);
                if (v != null) {
                    drMainView.removeView(v);
                    return false;
                }
            }
        }
        return super.onKeyDown(keyCode, event);
    }

    /*********************/
    /* 点击广告 */

    /**
     * *****************
     */
    @Override
    public void didClicked(View arg0, Object arg1) {

    }

    /****************************************************/
    /* 广告列表回调 */
    /* view :广告view */
	/* code :广告条数大于0，那么code=0，代表成功 反之code = -1 */

    /**
     * ************************************************
     */
    @Override
    public void didDataReceived(View arg0, int arg1) {

    }

    /*********************/
    /* 点击跳转 */

    /**
     * *****************
     */
    @Override
    public void didJumped(View arg0, Object arg1) {

    }

    /*********************/
    /* 曝光回调 */

    /**
     * *****************
     */
    @Override
    public void didReported(View arg0, Object arg1) {

    }

    /*********************/
    /* 广告彻底释放 */
	/* 从内存中删除 */

    /**
     * *****************
     */
    @Override
    public void didViewClose(View arg0) {
        finish();
    }

    /*********************/
    /* 广告创建成功 */

    /**
     * *****************
     */
    @Override
    public void didViewOpen(View arg0) {
        if (arg0 == null) {
            Toast.makeText(this, "积分墙获取失败，请检查网络", Toast.LENGTH_LONG).show();
            finish();
            return;
        }
        this.drMainView = (RelativeLayout) arg0;
    }
}
