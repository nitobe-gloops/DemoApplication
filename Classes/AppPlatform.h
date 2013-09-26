/*
 * AppPlatform.h
 *
 *  Created on: 2013/09/19
 *      Author: y.nitobe
 */

#ifndef APPPLATFORM_H_
#define APPPLATFORM_H_
#include "cocos2d.h"
#include <string>
#include <jni.h>
#include "platform/android/jni/JniHelper.h"

USING_NS_CC;
using namespace std;

class AppPlatform {
public:
	static const char* getAppVersion();

	static void outputVerboseLog(string className, string methodName, string message);
	static void outputDebugLog(string className, string methodName, string message);
	static void outputInfoLog(string className, string methodName, string message);
	static void outputWarningLog(string className, string methodName, string message);
	static void outputErrorLog(string className, string methodName, string message);

	static void outputLog(JniMethodInfo jniInfo, string className, string methodName, string message);

};

#endif /* APPPLATFORM_H_ */
