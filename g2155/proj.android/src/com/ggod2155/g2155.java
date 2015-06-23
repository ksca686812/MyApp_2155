package com.ggod2155;

import java.util.HashMap;

import org.CrossApp.lib.AndroidNativeTool;
import org.CrossApp.lib.Cocos2dxActivity;
import org.CrossApp.lib.Cocos2dxGLSurfaceView;
import org.CrossApp.lib.Cocos2dxHelper.Cocos2dxHelperListener;

import com.dianru.sdk.DRSdk;
import com.mob.tools.utils.UIHandler;
import com.mopan.sdk.MopanWallManager;

import cn.aow.android.DAOW;
import cn.aow.android.DCloseListener;
import cn.aow.android.SDKLoadListener;
import cn.sharesdk.framework.Platform;
import cn.sharesdk.framework.PlatformActionListener;
import cn.sharesdk.framework.ShareSDK;
import cn.sharesdk.framework.Platform.ShareParams;
import cn.waps.AppConnect;

import a.b.c.AdManager;
import a.b.c.listener.Interface_ActivityListener;
import a.b.c.os.OffersManager;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Message;
import android.util.Log;
import android.widget.Toast;
import android.os.Handler.Callback;

public class g2155 extends Cocos2dxActivity implements PlatformActionListener,
		Callback, UnioListener {

	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		ShareSDK.initSDK(this);
		Cocos2dxActivity.actAndroidNativeTool.pPlatFormActionListion = this;
		AndroidNativeTool.openUnioListener = this;
	
	}

	public Cocos2dxGLSurfaceView onCreateView() {
		Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
		// g2155 should create stencil buffer
		glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);

		return glSurfaceView;
	}

	@Override
	public void onCancel(Platform arg0, int arg1) {
		Log.i("weixin", "onCancel");
		Message msg = new Message();
		msg.arg1 = 3;
		msg.arg2 = arg1;
		msg.obj = arg0;
		UIHandler.sendMessage(msg, this);

	}

	@Override
	public void onComplete(Platform arg0, int arg1, HashMap<String, Object> arg2) {
		Log.i("weixin", "onComplete");
		Message msg = new Message();
		msg.arg1 = 1;
		msg.arg2 = arg1;
		msg.obj = arg0;
		UIHandler.sendMessage(msg, this);
	}

	@Override
	public void onError(Platform arg0, int arg1, Throwable arg2) {
		Log.i("weixin", "onError");
		Message msg = new Message();
		msg.arg1 = 2;
		msg.arg2 = arg1;
		msg.obj = arg2;
		UIHandler.sendMessage(msg, this);
	}

	public native void shareStatusNative(int status);

	public boolean handleMessage(Message msg) {
		String text = "";
		switch (msg.arg1) {
		case 1: {
			// 成功
			Platform plat = (Platform) msg.obj;
			text = "分享成功";
			shareStatusNative(1);
		}
			break;
		case 2: {
			// 失败
			if ("WechatClientNotExistException".equals(msg.obj.getClass()
					.getSimpleName())) {
				text = getContext().getString(
						R.string.wechat_client_inavailable);
			} else if ("WechatTimelineNotSupportedException".equals(msg.obj
					.getClass().getSimpleName())) {
				text = getContext().getString(
						R.string.wechat_client_inavailable);
			} else {
				text = getContext().getString(R.string.share_failed);
			}
			shareStatusNative(2);
		}
			break;
		case 3: {
			// 取消
			Platform plat = (Platform) msg.obj;
			text = "分享取消";
			shareStatusNative(3);
		}
			break;
		}

		Toast.makeText(getContext(), text, Toast.LENGTH_LONG).show();
		return false;
	}

	static {
		System.loadLibrary("CrossApp_cpp");
	}

	@Override
	public void openUnion(String mid, String id) {
		switch (Integer.parseInt(id)) {
		case 1:
			initYouMi(id);
			break;
		case 2:
			initDianRu(id);
			break;
		case 3:
			initWaps(id);
			break;
		case 4:
			initDuoMeng(id);
			break;
		case 5:
			
			break;
		case 6:
			initMoPan(id);
			break;
		default:
			break;
		}
	}

	private void initYouMi(String id) {
		AdManager.getInstance(this)
				.init("d83df24f9e18895a", "17100237a5f4fd99");
		AdManager.getInstance(this).setUserDataCollect(true);
		OffersManager.setUsingServerCallBack(true);
		OffersManager.getInstance(this).setCustomUserId(id);
		OffersManager.getInstance(this).onAppLaunch();
		OffersManager.getInstance(this).showOffersWall(
				new Interface_ActivityListener() {

					@Override
					public void onActivityDestroy(Context arg0) {
						// TODO Auto-generated method stub

					}
				});
	}

	private void initWaps(String id) {
		AppConnect.getInstance("91321295228eb07005d0435dc850e8ea", "default",
				this);
		// AppConnect.getInstance(this).initUninstallAd(this);
		AppConnect.getInstance(this).showOffers(this,id);
	}

	private void initDianRu(String id) {
		DRSdk.initialize(this, true, id);
		Intent intent = new Intent(this, DRActivity.class);
		intent.putExtra(DRSdk.DR_TYPE, DRSdk.DR_OFFER);
		startActivity(intent);
	}

	private void initDuoMeng(String id) {
		String pid="56OJxTlIuN1a/o2ld6";
		DAOW.getInstance(this).init(pid,id,
				new SDKLoadListener() {

					@Override
					public void onSuccess() {
						DAOW.getInstance(g2155.this).show(g2155.this);
					}

					@Override
					public void onStart() {
						// TODO Auto-generated method stub

					}

					@Override
					public void onLoading() {
						// TODO Auto-generated method stub

					}

					@Override
					public void onFail() {
						// TODO Auto-generated method stub
						Toast.makeText(g2155.this, "fail", Toast.LENGTH_SHORT)
								.show();

					}
				});
		DAOW.getInstance(this).setOnCloseListener(new DCloseListener() {

			@Override
			public void onClose() {
			}
		});
	}

	private void initMoPan(String id) {
		MopanWallManager.getInstance(this).startMopanWall("16860",
				"7ovrsz7nwa3hk71h");
		MopanWallManager.getInstance(this).showAppWall();
		MopanWallManager.getInstance(this).setUserID(id);
	}

	/**
	 * 退出时回收资源
	 */
	@Override
	protected void onDestroy() {
		super.onDestroy();
		if (OffersManager.getInstance(this) != null) {
			OffersManager.getInstance(this).onAppExit();
		}
		if (AppConnect.getInstance(this) != null) {
			AppConnect.getInstance(this).close();
		}

	}
}
