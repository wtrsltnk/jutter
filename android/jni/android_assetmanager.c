
#include <android/log.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#ifdef __ANDROID__

/* Include the fopen header */
#include "android_fopen.h"

/* This prototype is needed to prevent a warning about the missing prototype for global function below */
JNIEXPORT void JNICALL Java_net_saaltink_game_PassPerfectActivity_nativeLoad(JNIEnv *env, jobject obj, jobject assetManager);

JNIEXPORT void JNICALL Java_net_saaltink_game_PassPerfectActivity_nativeLoad(JNIEnv *env, jobject obj, jobject assetManager) {
    AAssetManager *mgr = AAssetManager_fromJava(env, assetManager);
    if (mgr == NULL) {
        __android_log_print(ANDROID_LOG_ERROR, "PassPerfect", "error loading asset manager");
    } else {
        android_fopen_set_asset_manager(mgr);
        __android_log_print(ANDROID_LOG_VERBOSE, "PassPerfect", "loaded asset manager");
    }
}

#endif /* __ANDROID__ */
