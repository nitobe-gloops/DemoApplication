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

	CCLog("DEMO::AppPlatform#getAppVersion() >> call");

	JniMethodInfo jniInfo;
	const char* ret = NULL;

	// Javaの関数 getAppVersionInJava(引数なし、戻り値 String)を取得する
	if(JniHelper::getStaticMethodInfo(jniInfo, CLASS_NAME, "getAppVersionInJava", "()Ljava/lang/String;")) {
//	if(JniHelper::getStaticMethodInfo(jniInfo, CLASS_NAME_02, "getTestAppVersion", "()Ljava/lang/String;")) {
//	if(JniHelper::getStaticMethodInfo(jniInfo, CLASS_NAME_03, "getTestAppVersion", "()Ljava/lang/String;")) {

		CCLog("DEMO::AppPlatform#getAppVersion() >> [Java]getAppVersionInJava()の呼び出し");

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

	CCLog("DEMO::AppPlatform#getAppVersion() >> ret");
	return ret;
}
