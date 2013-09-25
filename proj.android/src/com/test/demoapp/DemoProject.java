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

public class DemoProject extends Cocos2dxActivity{
	public static String _appVersion = "";
	private static Context _context = null;
	

    protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);	
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
    
    
	/**
	 * 
	 * */
	public static String getAppVersionInJava() {
		// androidアプリのバージョンをC++に返却する
		Log.i("DEMO::DemoProject#getAppVersionInJava()", "call");

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
