package com.test.demoapp;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.os.Bundle;
import android.util.Log;

/**
 *  TODO
 *  Activityとしてクラスを作った場合、
 *  マニフェストに追加しないと、C++から呼び出す時にエラーになる
 * */
public class TestOsDependent extends Cocos2dxActivity{
	
	public static String _appVersion = "";
	private static Context _context = TestOsDependent.getContext();
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		Log.i("DEMO::TestOsDependent#onCreate()", "call");
		
		// XXX
		// C++からgetAppVersionInJava()を呼び出すとき、onCreateされる契機が無いため、onCretae()内の処理は実行されない
//		PackageManager pkgMngr = super.getContext().getPackageManager();
//		try {
//			PackageInfo pkgInfo = pkgMngr.getPackageInfo(this.getPackageName(), PackageManager.GET_META_DATA);
//			_appVersion = pkgInfo.versionName;
//		}catch (NameNotFoundException e) {
//			Log.e("DEMO::TestOsDependent#onCreate()", "" + e.getStackTrace());
//		}
	}
	
	
	/**
	 * 
	 * */
	public static String getAppVersionInJava() {
		// androidアプリのバージョンをC++に返却する
		Log.i("DEMO::TestOsDependent#getAppVersionInJava()", "call");

		PackageManager pkgMngr = getContext().getPackageManager();
		try {
			PackageInfo pkgInfo = pkgMngr.getPackageInfo(_context.getPackageName(), PackageManager.GET_META_DATA);
			_appVersion = pkgInfo.versionName;
		}catch (NameNotFoundException e) {
			Log.e("DEMO::TestOsDependent#onCreate()", "" + e.getStackTrace());
		}
		
		return _appVersion;
	}
	
}
