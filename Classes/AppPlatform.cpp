/*
 * AppPlatform.cpp
 *
 *  Created on: 2013/09/19
 *      Author: y.nitobe
 */

#include <jni.h>
#include "cocoa/CCString.h"
#include "platform/android/jni/JniHelper.h"
#include "AppPlatform.h"

#define CLASS_NAME "com/test/demoapp/DemoProject"
//#define CLASS_NAME_02 "com/test/demoapp/TestOsDependent"
//#define CLASS_NAME_03 "com/test/util/DeviceEnvironment"

USING_NS_CC;
using namespace std;

const char* AppPlatform::getAppVersion() {

	AppPlatform::outputVerboseLog("AppPlatform", "getAppVersion",  "call");

	JniMethodInfo jniInfo;
	const char* ret = NULL;

	// Javaの関数 getAppVersionInJava(引数なし、戻り値 String)を取得する
	if(JniHelper::getStaticMethodInfo(jniInfo, CLASS_NAME, "getAppVersionInJava", "()Ljava/lang/String;")) {
//	if(JniHelper::getStaticMethodInfo(jniInfo, CLASS_NAME_02, "getTestAppVersion", "()Ljava/lang/String;")) {
//	if(JniHelper::getStaticMethodInfo(jniInfo, CLASS_NAME_03, "getTestAppVersion", "()Ljava/lang/String;")) {

		AppPlatform::outputDebugLog("AppPlatform", "getAppVersion",  "[Java]getAppVersionInJava()の呼び出し");

		// getAppVersionInJava()を呼び出し、戻り値を取得する
		jstring jstr = (jstring)jniInfo.env->CallStaticObjectMethod(jniInfo.classID, jniInfo.methodID);
		// Stringに変換する
		std::string sstr = JniHelper::jstring2string(jstr);

		jniInfo.env->DeleteLocalRef(jniInfo.classID);
		jniInfo.env->DeleteLocalRef(jstr);
		// cocos2d-xのautorelease poolに登録した char*を返却する
		CCString* cstr = CCString::create(sstr.c_str());
		ret = cstr->getCString();
	}

	AppPlatform::outputVerboseLog("AppPlatform", "getAppVersion",  "ret");
	return ret;
}


void AppPlatform::outputVerboseLog(string className, string methodName, string message) {
	JniMethodInfo jniInfo;
	JniHelper::getStaticMethodInfo(jniInfo, CLASS_NAME, "verboseLog", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");

	outputLog(jniInfo, className, methodName, message);
}


void AppPlatform::outputDebugLog(string className, string methodName, string message) {
	JniMethodInfo jniInfo;
	JniHelper::getStaticMethodInfo(jniInfo, CLASS_NAME, "debugLog", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");

	outputLog(jniInfo, className, methodName, message);
}


void AppPlatform::outputInfoLog(string className, string methodName, string message) {
	JniMethodInfo jniInfo;
	JniHelper::getStaticMethodInfo(jniInfo, CLASS_NAME, "infoLog", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");

	outputLog(jniInfo, className, methodName, message);
}


void AppPlatform::outputWarningLog(string className, string methodName, string message) {
	JniMethodInfo jniInfo;
	JniHelper::getStaticMethodInfo(jniInfo, CLASS_NAME, "warningLog", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");

	outputLog(jniInfo, className, methodName, message);
}


void AppPlatform::outputErrorLog(string className, string methodName, string message) {
	JniMethodInfo jniInfo;
	JniHelper::getStaticMethodInfo(jniInfo, CLASS_NAME, "errorLog", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");

	outputLog(jniInfo, className, methodName, message);
}


void AppPlatform::outputLog(JniMethodInfo jniInfo, string className, string methodName, string message) {
	// ★パラメータがStringの場合はjstringに変換する
    // java側は「String」にする。UTF8変換
	jstring stringArg1 = jniInfo.env->NewStringUTF(className.c_str());
	jstring stringArg2 = jniInfo.env->NewStringUTF(methodName.c_str());
	jstring stringArg3 = jniInfo.env->NewStringUTF(message.c_str());

	// getAppVersionInJava()を呼び出し、戻り値を取得する
	jniInfo.env->CallStaticVoidMethod(jniInfo.classID, jniInfo.methodID, stringArg1, stringArg2, stringArg3);

	jniInfo.env->DeleteLocalRef(jniInfo.classID);
	jniInfo.env->DeleteLocalRef(stringArg1);
	jniInfo.env->DeleteLocalRef(stringArg2);
	jniInfo.env->DeleteLocalRef(stringArg3);
}
