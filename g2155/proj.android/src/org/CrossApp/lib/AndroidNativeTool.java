package org.CrossApp.lib;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.sql.Date;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.HashMap;
import java.util.Locale;

import org.CrossApp.lib.Cocos2dxGLSurfaceView;

import cn.sharesdk.framework.CustomPlatform;
import cn.sharesdk.framework.Platform;
import cn.sharesdk.framework.PlatformActionListener;
import cn.sharesdk.framework.ShareSDK;
import cn.sharesdk.framework.TitleLayout;
import cn.sharesdk.framework.Platform.ShareParams;

import com.ggod2155.R;
import com.ggod2155.UnioListener;
import com.ggod2155.g2155;
import com.mob.tools.utils.UIHandler;
import cn.sharesdk.onekeyshare.OnekeyShare;
import cn.sharesdk.onekeyshare.OnekeyShareTheme;
import cn.sharesdk.onekeyshare.Shake2Share;
import cn.sharesdk.onekeyshare.Shake2Share.OnShakeListener;
import cn.sharesdk.onekeyshare.ShareCore;
import cn.sharesdk.tencent.qq.QQ;
import cn.sharesdk.tencent.qzone.QZone;
import cn.sharesdk.tencent.weibo.TencentWeibo;

import android.R.integer;
import android.R.string;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.ContentResolver;
import android.content.ContentValues;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.os.Handler.Callback;
import android.provider.MediaStore;
import android.provider.MediaStore.Images.Media;
import android.provider.Settings;
import android.provider.Settings.SettingNotFoundException;
import android.text.format.DateFormat;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Toast;
import android.provider.Settings.Secure;

@SuppressLint("SdCardPath")
public class AndroidNativeTool {

	public static UnioListener openUnioListener;
	public static PlatformActionListener pPlatFormActionListion;
	private static AlertDialog mDialog = null;
	private static Activity s_pContext;

	native static void NativeReturn(String arg1, Object arg2);

	public AndroidNativeTool(final Activity context) {
		s_pContext = context;

	}

	public static void ShowDlg(String[] args) {
		s_pContext.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				mDialog.show();
			}
		});
	}

	static String s;
	public static Uri photoUri;

	public static void CAImageCapture(int type) {
		Intent intent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
		SimpleDateFormat timeStampFormat = new SimpleDateFormat(
				"yyyy_MM_dd_HH_mm_ss");
		String filename = timeStampFormat.format(new Date(0));
		ContentValues values = new ContentValues();
		values.put(Media.TITLE, filename);

		photoUri = s_pContext.getContentResolver().insert(
				MediaStore.Images.Media.EXTERNAL_CONTENT_URI, values);

		intent.putExtra(MediaStore.EXTRA_OUTPUT, photoUri);

		int selectedType = 0;
		if (type == 0) {
			selectedType = 0;
		} else {
			selectedType = 3;
		}

		s_pContext.startActivityForResult(intent, selectedType);
	}

	public static void CAVideoCapture() {
		Intent getImageByCamera2 = new Intent(
				"android.media.action.VIDEO_CAPTURE");
		s_pContext.startActivityForResult(getImageByCamera2, 1);
	}

	public static void CAVideoAlbum() {
		Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
		intent.setType("video/*");
		Intent wrapperIntent = Intent.createChooser(intent, null);
		s_pContext.startActivityForResult(wrapperIntent, 2);
	}

	public static void CAImageAlbum(int type) {
		Intent getImage = new Intent(Intent.ACTION_GET_CONTENT);

		getImage.setType("image/*");

		Intent wrapperIntent2 = Intent.createChooser(getImage, null);
		int selectedType = 0;
		if (type == 0) {
			selectedType = 0;
		} else {
			selectedType = 3;
		}
		s_pContext.startActivityForResult(wrapperIntent2, selectedType);// 3
	}

	public static String getDeviceID() {
		String id = Secure.getString(s_pContext.getContentResolver(),
				Secure.ANDROID_ID);
		return id;
	}

	public static Handler mHander = new Handler() {
		@Override
		public void handleMessage(Message msg) {
			super.handleMessage(msg);
			String text = "";
			switch (msg.arg1) {
			case 1: {
				// 成功
				Platform plat = (Platform) msg.obj;
				text = "分享成功";

			}
				break;
			case 2: {
				// 失败
				if ("WechatClientNotExistException".equals(msg.obj.getClass()
						.getSimpleName())) {
					text = s_pContext
							.getString(R.string.wechat_client_inavailable);
				} else if ("WechatTimelineNotSupportedException".equals(msg.obj
						.getClass().getSimpleName())) {
					text = s_pContext
							.getString(R.string.wechat_client_inavailable);
				} else {
					text = s_pContext.getString(R.string.share_failed);
				}
			}
				break;
			case 3: {
				// 取消
				Platform plat = (Platform) msg.obj;
				text = "分享取消";
			}
				break;
			}

			Toast.makeText(s_pContext, text, Toast.LENGTH_LONG).show();
		}
	};

	// 使用快捷分享完成分享（请务必仔细阅读位于SDK解压目录下Docs文件夹中OnekeyShare类的JavaDoc）
	/**
	 * ShareSDK集成方法有两种</br>
	 * 1、第一种是引用方式，例如引用onekeyshare项目，onekeyshare项目再引用mainlibs库</br>
	 * 2、第二种是把onekeyshare和mainlibs集成到项目中，本例子就是用第二种方式</br> 请看“ShareSDK
	 * 使用说明文档”，SDK下载目录中 </br> 或者看网络集成文档
	 * http://wiki.mob.com/Android_%E5%BF%AB%E9%
	 * 80%9F%E9%9B%86%E6%88%90%E6%8C%87%E5%8D%97
	 * 3、混淆时，把sample或者本例子的混淆代码copy过去，在proguard-project.txt文件中
	 * 
	 * 
	 * 平台配置信息有三种方式： 1、在我们后台配置各个微博平台的key
	 * 2、在代码中配置各个微博平台的key，http://mob.com/androidDoc
	 * /cn/sharesdk/framework/ShareSDK.html
	 * 3、在配置文件中配置，本例子里面的assets/ShareSDK.conf,
	 */
	public static void showShare(boolean silent, String imageUrl,
			String demoUrl, String title, String des, String platform) {

		Context context = s_pContext;
		if (platform != null && platform.length() > 0) {
			Platform plat = null;
			ShareParams sp = new ShareParams();
			sp.setTitle(title);
			sp.setText(des);
			sp.setShareType(Platform.SHARE_WEBPAGE);
			sp.setUrl(demoUrl);
			sp.setImageUrl(imageUrl);

			plat = ShareSDK.getPlatform(platform);

			// if (ctvPlats[0].isChecked()) {
			// plat = ShareSDK.getPlatform("Wechat");
			// } else if (ctvPlats[1].isChecked()) {
			// plat = ShareSDK.getPlatform("WechatMoments");
			// } else {
			// plat = ShareSDK.getPlatform("WechatFavorite");
			// }

			plat.setPlatformActionListener(pPlatFormActionListion);

			// (new PlatformActionListener() {
			// @Override
			// public void onComplete(Platform arg0, int arg1, HashMap<String,
			// Object> arg2) {
			// Log.i("weixin", "onComplete");
			// Toast.makeText(s_pContext, "oncomplete",
			// Toast.LENGTH_SHORT).show();
			// Message msg = new Message();
			// msg.arg1 = 1;
			// msg.arg2 = arg1;
			// msg.obj = arg0;
			// mHander.sendMessage(msg);
			// }
			//
			// @Override
			// public void onError(Platform arg0, int arg1, Throwable arg2) {
			// Log.i("weixin", "onError");
			// Toast.makeText(s_pContext, "onError", Toast.LENGTH_SHORT).show();
			// Message msg = new Message();
			// msg.arg1 = 2;
			// msg.arg2 = arg1;
			// msg.obj = arg2;
			// mHander.sendMessage(msg);
			// }
			//
			// @Override
			// public void onCancel(Platform arg0, int arg1) {
			// Toast.makeText(s_pContext, "onCancel",
			// Toast.LENGTH_SHORT).show();
			// Log.i("weixin", "onCancel");
			// Message msg = new Message();
			// msg.arg1 = 3;
			// msg.arg2 = arg1;
			// msg.obj = arg0;
			// mHander.sendMessage(msg);
			//
			// }
			// });
			plat.share(sp);
		} else {
			OnekeyShare oks = new OnekeyShare();

			Log.i("showShare  java", "come in");

			// oks.setAddress("12345678901");
			oks.setTitle(title);
			Log.i("showShare  title", title);
			// oks.setTitleUrl(demoUrl);
			oks.setText(des);
			oks.setImageUrl(imageUrl);
			oks.setUrl(demoUrl);
			Log.i("showShare  demoUrl", demoUrl);
			//

			// oks.setText("测试分享文字 http://www.baidu.com");
			// oks.setTitle("分享");
			// oks.setImageUrl("http://f1.sharesdk.cn/imgs/2014/02/26/owWpLZo_638x960.jpg");
			// oks.setUrl("http://www.baidu.com");

			oks.setLatitude(23.056081f);
			oks.setLongitude(113.385708f);
			oks.setSilent(silent);

			// 令编辑页面显示为Dialog模式
			// oks.setDialogMode();

			// 在自动授权时可以禁用SSO方式
			// if(!CustomShareFieldsPage.getBoolean("enableSSO", true))
			oks.disableSSOWhenAuthorize();

			// 去除注释，则快捷分享的操作结果将通过OneKeyShareCallback回调
			// oks.setCallback(new OneKeyShareCallback());

			// 去自定义不同平台的字段内容
			// oks.setShareContentCustomizeCallback(new
			// ShareContentCustomizeDemo());

			// 去除注释，则快捷分享九宫格中将隐藏新浪微博和腾讯微博
			// oks.addHiddenPlatform(SinaWeibo.NAME);
			// oks.addHiddenPlatform(TencentWeibo.NAME);

			oks.show(context);
		}

	}

	public static void openUnion(String id, String mid) {

		Log.i("sssss", id);
		Log.i("mid = ", mid);
		openUnioListener.openUnion(mid, id);

	}

	public static int getScreenBrightness() {
		int value = 0;
		ContentResolver cr = s_pContext.getContentResolver();
		try {

			value = Settings.System.getInt(cr,
					Settings.System.SCREEN_BRIGHTNESS);
		} catch (SettingNotFoundException e) {

		}
		return value;
	}

	public static void setScreenBrightness(int value) {

		Cocos2dxActivity mActivity = (Cocos2dxActivity) s_pContext;
		mActivity.mLightHandler.sendEmptyMessage(value);
	}

	public static void browserOpenURL(final String url) {
		s_pContext.runOnUiThread(new Runnable() {
			public void run() {
				try {
					if (s_pContext == null)
						return;
					Intent intent = new Intent();
					intent.setAction("android.intent.action.VIEW");
					Uri content_url = Uri.parse(url);
					intent.setData(content_url);
					s_pContext.startActivity(intent);
				} catch (Exception e) {
					Log.d("CrossApp", "browserOpenURL", e);
				}
			}
		});
	}

	private void cropImageUri(Uri uri, int outputX, int outputY, int requestCode) {
		Intent intent = new Intent("com.android.camera.action.CROP");

		intent.setDataAndType(uri, "image/*");
		intent.putExtra("crop", "true");
		intent.putExtra("aspectX", 1);
		intent.putExtra("aspectY", 1);
		intent.putExtra("outputX", outputX);
		intent.putExtra("outputY", outputY);
		intent.putExtra("scale", true);
		intent.putExtra(MediaStore.EXTRA_OUTPUT, uri);
		intent.putExtra("return-data", false);
		intent.putExtra("outputFormat", Bitmap.CompressFormat.JPEG.toString());
		intent.putExtra("noFaceDetection", true); // no face detection
		SimpleDateFormat timeStampFormat = new SimpleDateFormat(
				"yyyy_MM_dd_HH_mm_ss");
		String filename = timeStampFormat.format(new Date(0));
		ContentValues values = new ContentValues();
		values.put(Media.TITLE, filename);

		photoUri = s_pContext.getContentResolver().insert(
				MediaStore.Images.Media.EXTERNAL_CONTENT_URI, values);

		intent.putExtra(MediaStore.EXTRA_OUTPUT, photoUri);
		s_pContext.startActivityForResult(intent, 1);
	}

	public void onActivityResult(int requestCode, int resultCode, Intent intent) {
		if (resultCode == -1) {
			switch (requestCode) {
			case 2:
			case 3: // Photo
				Uri originalUri = intent.getData();

				String[] proj = { MediaStore.Images.Media.DATA };

				Cursor cursor = s_pContext.managedQuery(originalUri, proj,
						null, null, null);

				int column_index = cursor
						.getColumnIndexOrThrow(MediaStore.Images.Media.DATA);

				cursor.moveToFirst();

				String path = cursor.getString(column_index);

				NativeReturn(path, null);
				break;
			case 1:
				Uri originalUri1;
				if (intent != null && intent.getData() != null) {
					originalUri1 = intent.getData();
				} else {
					originalUri1 = photoUri;
				}

				// 1414136613714.jpg
				String[] proj1 = { MediaStore.Images.Media.DATA };

				Cursor cursor1 = s_pContext.managedQuery(originalUri1, proj1,
						null, null, null);

				int column_index1 = cursor1
						.getColumnIndexOrThrow(MediaStore.Images.Media.DATA);

				cursor1.moveToFirst();

				String path1 = cursor1.getString(column_index1);

				NativeReturn(path1, null);

				break;
			case 0:
				Uri takePhoto;

				// Uri photoUri = s_pContext. getContentResolver().insert(
				// MediaStore.Images.Media.EXTERNAL_CONTENT_URI, values);

				// intent.putExtra(MediaStore.EXTRA_OUTPUT, photoUri);
				if (intent != null && intent.getData() != null) {
					takePhoto = intent.getData();
					cropImageUri(takePhoto, 640, 640, 1);
				} else {
					cropImageUri(photoUri, 640, 640, 1);
				}

				break;

			default:
				break;
			}
		}
	}
}
