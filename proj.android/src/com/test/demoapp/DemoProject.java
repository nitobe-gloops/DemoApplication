/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.test.demoapp;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.os.Bundle;
import android.util.Log;
import android.view.WindowManager;

import com.test.util.Logger;

public class DemoProject extends Cocos2dxActivity{
	
	private static String TAG = "DEMO:";	// タグにしたい文字列+":"

	public static String _appVersion = "";
	private static Context _context = null;

    protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);

		Logger.startLogger(this, TAG);
	}

    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// DemoProject should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	
    	//アプリ起動中はバックライトを消さない
    	getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
    	
    	_context = this;
//    	DeviceEnvironment.setContext(this);
    	
    	return glSurfaceView;
    }

    static {
        System.loadLibrary("cocos2dcpp");
    }   
    
    
// .............................................................................
    /**
	 * 
	 * */
	public static String getAppVersionInJava() {
		// androidアプリのバージョンをC++に返却する
		Logger.i(_context, "getAppVersionInJava", "call");

		PackageManager pkgMngr = getContext().getPackageManager();
		try {
			PackageInfo pkgInfo = pkgMngr.getPackageInfo(_context.getPackageName(), PackageManager.GET_META_DATA);
			_appVersion = pkgInfo.versionName;
		}catch (NameNotFoundException e) {
			Log.e("DEMO::TestOsDependent#onCreate()", "" + e.getStackTrace());
		}
		
		return _appVersion;
	}

	
// .............................................................................
	/**
	 * Log出力<br>
	 * verbose
	 * */
	public static void verboseLog(String className, String methodName, String message){
		Logger.v(className, methodName, message);
		
	}

	/**
	 * Log出力<br>
	 * Debug
	 * */
	public static void debugLog(String className, String methodName, String message){
		Logger.d(className, methodName, message);
		
	}

	/**
	 * Log出力<br>
	 * Info
	 * */
	public static void infoLog(String className, String methodName, String message){
		Logger.i(className, methodName, message);
		
	}

	/**
	 * Log出力<br>
	 * Warning
	 * */
	public static void warningLog(String className, String methodName, String message){
		Logger.w(className, methodName, message);
		
	}

	/**
	 * Log出力<br>
	 * Error
	 * */
	public static void errorLog(String className, String methodName, String message){
		Logger.e(className, methodName, message);
		
	}
}
