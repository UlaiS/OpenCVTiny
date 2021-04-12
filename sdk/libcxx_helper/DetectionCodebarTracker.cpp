//
// Created by Ulain on 27/03/2021.
//

#include <jni.h>
#include <string>
#include "BitmapUtil.h"
#include <opencv2/opencv.hpp>

static const char* JavaBridgeClass = "org/opencv/codebar/DetectionCodebarTracker";
using namespace cv;
using namespace std;

static struct {
    jclass jClassPoint;
    jmethodID jMethodInit;
    jfieldID jFieldIDX;
    jfieldID jFieldIDY;
} gPointInfo;

typedef struct{
    std::string type;
    std::int32_t data;
    std::vector <Point> location;
}  decodedObject;

static void initClassInfo(JNIEnv *env) {
    gPointInfo.jClassPoint = reinterpret_cast<jclass>(env -> NewGlobalRef(env -> FindClass("android/graphics/Point")));
    gPointInfo.jMethodInit = env -> GetMethodID(gPointInfo.jClassPoint, "<init>", "(II)V");
    gPointInfo.jFieldIDX = env -> GetFieldID(gPointInfo.jClassPoint, "x", "I");
    gPointInfo.jFieldIDY = env -> GetFieldID(gPointInfo.jClassPoint, "y", "I");
}

static void filterImageCodeBar(JNIEnv *env, jclass type, jlong src, jlong dst){
    Mat* pMatGr = (Mat*)src;
    Mat* cpMatGr = (Mat*)dst;
    //cvtColor(*pMatGr, *pMatGr, COLOR_BGR2GRAY);
    Ptr<CLAHE> clahe = createCLAHE(2.0, Size(8,8));
    clahe->apply(*pMatGr, *pMatGr);
    threshold(*pMatGr, *cpMatGr, 55, 255.0, THRESH_OTSU);

}

static JNINativeMethod gMethods[] = {
        {
            "filterImageCodeBar",
                "(JJ)V",
            (void*)filterImageCodeBar
        }
};

extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv *env = NULL;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_FALSE;
    }
    jclass classJavaBridge = env->FindClass(JavaBridgeClass);
    if(env -> RegisterNatives(classJavaBridge, gMethods, sizeof(gMethods)/ sizeof(gMethods[0])) < 0) {
        return JNI_FALSE;
    }
    initClassInfo(env);
    return JNI_VERSION_1_6;
}