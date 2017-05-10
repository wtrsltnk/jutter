LOCAL_PATH := $(call my-dir)

###########################
#
# SDL shared library
#
###########################

include $(CLEAR_VARS)

LOCAL_MODULE := SDL2

LOCAL_C_INCLUDES := $(LOCAL_PATH)/sdl2-mirror/include

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)

LOCAL_SRC_FILES := \
	$(wildcard $(LOCAL_PATH)/sdl2-mirror/src/*.c) \
	$(wildcard $(LOCAL_PATH)/sdl2-mirror/src/audio/*.c) \
	$(wildcard $(LOCAL_PATH)/sdl2-mirror/src/audio/android/*.c) \
	$(wildcard $(LOCAL_PATH)/sdl2-mirror/src/audio/dummy/*.c) \
	$(LOCAL_PATH)/sdl2-mirror/src/atomic/SDL_atomic.c \
	$(LOCAL_PATH)/sdl2-mirror/src/atomic/SDL_spinlock.c.arm \
	$(wildcard $(LOCAL_PATH)/sdl2-mirror/src/core/android/*.c) \
	$(wildcard $(LOCAL_PATH)/sdl2-mirror/src/cpuinfo/*.c) \
	$(wildcard $(LOCAL_PATH)/sdl2-mirror/src/dynapi/*.c) \
	$(wildcard $(LOCAL_PATH)/sdl2-mirror/src/events/*.c) \
	$(wildcard $(LOCAL_PATH)/sdl2-mirror/src/file/*.c) \
	$(wildcard $(LOCAL_PATH)/sdl2-mirror/src/haptic/*.c) \
	$(wildcard $(LOCAL_PATH)/sdl2-mirror/src/haptic/dummy/*.c) \
	$(wildcard $(LOCAL_PATH)/sdl2-mirror/src/joystick/*.c) \
	$(wildcard $(LOCAL_PATH)/sdl2-mirror/src/joystick/android/*.c) \
	$(wildcard $(LOCAL_PATH)/sdl2-mirror/src/loadso/dlopen/*.c) \
	$(wildcard $(LOCAL_PATH)/sdl2-mirror/src/power/*.c) \
	$(wildcard $(LOCAL_PATH)/sdl2-mirror/src/power/android/*.c) \
	$(wildcard $(LOCAL_PATH)/sdl2-mirror/src/filesystem/android/*.c) \
	$(wildcard $(LOCAL_PATH)/sdl2-mirror/src/render/*.c) \
	$(wildcard $(LOCAL_PATH)/sdl2-mirror/src/render/*/*.c) \
	$(wildcard $(LOCAL_PATH)/sdl2-mirror/src/stdlib/*.c) \
	$(wildcard $(LOCAL_PATH)/sdl2-mirror/src/thread/*.c) \
	$(wildcard $(LOCAL_PATH)/sdl2-mirror/src/thread/pthread/*.c) \
	$(wildcard $(LOCAL_PATH)/sdl2-mirror/src/timer/*.c) \
	$(wildcard $(LOCAL_PATH)/sdl2-mirror/src/timer/unix/*.c) \
	$(wildcard $(LOCAL_PATH)/sdl2-mirror/src/video/*.c) \
	$(wildcard $(LOCAL_PATH)/sdl2-mirror/src/video/android/*.c)

LOCAL_CFLAGS += -DGL_GLEXT_PROTOTYPES
LOCAL_LDLIBS := -ldl -lGLESv1_CM -lGLESv2 -llog -landroid

include $(BUILD_SHARED_LIBRARY)

###########################
#
# SDL static library
#
###########################

LOCAL_MODULE := SDL2_static

LOCAL_MODULE_FILENAME := libSDL2

LOCAL_SRC_FILES += $(subst $(LOCAL_PATH)/sdl2-mirror/,,$(LOCAL_PATH)/sdl2-mirror/src/main/android/SDL_android_main.c)

LOCAL_LDLIBS := 
LOCAL_EXPORT_LDLIBS := -Wl,--undefined=Java_org_libsdl_app_SDLActivity_nativeInit -ldl -lGLESv1_CM -lGLESv2 -llog -landroid

include $(BUILD_STATIC_LIBRARY)
