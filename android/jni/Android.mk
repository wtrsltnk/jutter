
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SRC_ROOT := ../..
LIBS_ROOT := $(SRC_ROOT)/libs
SDL_PATH := $(LIBS_ROOT)/sdl2-mirror
GLM_PATH := $(LIBS_ROOT)/glm
BULLET3_PATH := $(LIBS_ROOT)/bullet3

NDK_MODULE_PATH := ../

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include \
    $(LOCAL_PATH)/$(GLM_PATH) \
    $(LOCAL_PATH)/$(BULLET3_PATH)/src \
    $(LOCAL_PATH)/$(LIBS_ROOT)/nanovg/src

# Add your application source files here...
LOCAL_SRC_FILES := $(SRC_ROOT)/src/common/fileio.cpp \
    $(SRC_ROOT)/src/common/geometry.cpp \
    $(SRC_ROOT)/src/common/log.cpp \
    $(SRC_ROOT)/src/common/particles.cpp \
    $(SRC_ROOT)/src/common/postprocesseffect.cpp \
    $(SRC_ROOT)/src/common/randm.cpp \
    $(SRC_ROOT)/src/common/shader.cpp \
    $(SRC_ROOT)/src/common/texture.cpp \
    $(SRC_ROOT)/src/common/timer.cpp \
    $(SRC_ROOT)/src/entities/ballentity.cpp \
    $(SRC_ROOT)/src/entities/cameraentity.cpp \
    $(SRC_ROOT)/src/entities/entity.cpp \
    $(SRC_ROOT)/src/entities/entitymanager.cpp \
    $(SRC_ROOT)/src/entities/targetentity.cpp \
    $(SRC_ROOT)/src/entities/worldentity.cpp \
    $(SRC_ROOT)/src/gamemodes/confirmexitgamemode.cpp \
    $(SRC_ROOT)/src/gamemodes/gamemode.cpp \
    $(SRC_ROOT)/src/gamemodes/mainmenumode.cpp \
    $(SRC_ROOT)/src/gamemodes/practicegamemode.cpp \
    $(SRC_ROOT)/src/system/impl-headers.cpp \
    $(SRC_ROOT)/src/system/input.cpp \
    $(SRC_ROOT)/src/system/sdl2-setup.cpp \
    $(SRC_ROOT)/src/ui/buttoncontrol.cpp \
    $(SRC_ROOT)/src/ui/control.cpp \
    $(SRC_ROOT)/src/ui/fadeout.cpp \
    $(SRC_ROOT)/src/ui/fadeoutlabelcontrol.cpp \
    $(SRC_ROOT)/src/ui/fadeoutswipe.cpp \
    $(SRC_ROOT)/src/ui/imagecontrol.cpp \
    $(SRC_ROOT)/src/ui/labelcontrol.cpp \
    $(SRC_ROOT)/src/ui/panelcontrol.cpp \
    $(SRC_ROOT)/src/ui/hintcontrol.cpp \
    $(SRC_ROOT)/src/ui/animatedvalue.cpp \
    $(SRC_ROOT)/src/ui/scorebugcontrol.cpp \
    $(SRC_ROOT)/src/ui/ui.cpp \
    $(SRC_ROOT)/src/gamerules.cpp \
    $(SRC_ROOT)/src/gamephysics.cpp \
    $(SRC_ROOT)/src/program.cpp \
    $(LIBS_ROOT)/nanovg/src/nanovg.c \
    android_assetmanager.c \
    android_fopen.c \
    $(SDL_PATH)/src/main/android/SDL_android_main.c

LOCAL_SHARED_LIBRARIES := SDL2
LOCAL_STATIC_LIBRARIES := bullet

LOCAL_CFLAGS := -DBUILD_ANDROID -include "android_fopen.h"

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -lGLESv3 -llog -landroid

include $(BUILD_SHARED_LIBRARY)

include ..\libs\bullet3.mk
include ..\libs\sdl2.mk
