package com.test.util;

import android.app.Activity;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.util.Log;

public class DeviceEnvironment {
	
	private static Activity _act = null;

	
	/**
	 * 
	 * */
	public static void setContext(Activity activity) {
		_act = activity;
	}
	
	
	/**
	 * 
	 * */
	public static String getTestAppVersion() {
		String appVersion = null;
		PackageManager pkgMngr = _act.getPackageManager();
		try {
			PackageInfo pkgInfo = pkgMngr.getPackageInfo(_act.getPackageName(), PackageManager.GET_META_DATA);
			appVersion = pkgInfo.versionName;
		}catch (NameNotFoundException e) {
			Log.e("DEMO::TestOsDependent#onCreate()", "" + e.getStackTrace());
		}
		
		return appVersion;
	}
}