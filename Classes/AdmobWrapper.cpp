#include "AdmobWrapper.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"

#define  JAVA_CLASS_NAME "org/cocos2dx/cpp/AdmobPlugin"

using namespace cocos2d;

static AdmobWrapper * s_Instance = NULL;

AdmobWrapper * AdmobWrapper::getInstance(){
	if(s_Instance == NULL){
		s_Instance = new AdmobWrapper();
	}

	return s_Instance;
}
void AdmobWrapper::setup(){
//void AdmobWrapper::setup(const char* bannerId, const char* lbAudioId){
	
	//Empty for Android 
	
	//CCLOG("AdmobWrapper::setup");
}


void AdmobWrapper::showBanner(){
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo,
			JAVA_CLASS_NAME,"showBanner","()V");
	if(!isHave){
			//CCLOG("jni:openURL showBanner");
	}else{
		minfo.env->CallStaticVoidMethod(minfo.classID,minfo.methodID);
	}
}

void AdmobWrapper::hideBanner(){
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo,
				JAVA_CLASS_NAME,"hideBanner","()V");
	if(!isHave){
			//CCLOG("jni:openURL hideBanner");
	}else{
		minfo.env->CallStaticVoidMethod(minfo.classID,minfo.methodID);
	}
}

void AdmobWrapper::showInterstitial(){
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo,
				JAVA_CLASS_NAME,"showInterstitial","()V");
	if(!isHave){
			//	CCLOG("jni:openURL showInter");
	}else{
		minfo.env->CallStaticVoidMethod(minfo.classID,minfo.methodID);
	}
}

#else
using namespace cocos2d;

static AdmobWrapper * s_Instance = NULL;

AdmobWrapper * AdmobWrapper::getInstance(){
    if(s_Instance == NULL){
        s_Instance = new AdmobWrapper();
    }
    
    return s_Instance;
}

void AdmobWrapper::showBanner(){

}

void AdmobWrapper::hideBanner(){

}

void AdmobWrapper::showInterstitial(){

}

#endif