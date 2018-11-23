#include "cocos2d.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include "ttest.h"
#include "JniTest.h"


#define CLASS_NAME "com/kingBook/killFruit/TestHelper"

using namespace cocos2d;

extern "C"{
	void ccPay(const int money, const char* product, const char* extData){
		JniMethodInfo t;
		if(JniHelper::getStaticMethodInfo(t, CLASS_NAME, "pay", "(ILjava/lang/String;Ljava/lang/String;)V"))
		{
			jstring jproduct = t.env->NewStringUTF(product);
			jstring jextData = t.env->NewStringUTF(extData);
			t.env->CallStaticVoidMethod(t.classID, t.methodID, money, jproduct, jextData);
			t.env->DeleteLocalRef(jproduct);
			t.env->DeleteLocalRef(jextData);
		}
	}

	void Java_com_kingBook_killFruit_TestHelper_payCallback(JNIEnv *env, jobject thiz, jstring result)
	{
		const char *str = env->GetStringUTFChars(result, NULL);
		payCallback(str);
		env->ReleaseStringUTFChars(result, str);
	}
}
