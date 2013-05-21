LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := packetbuilder
LOCAL_SRC_FILES := PacketBuilder-jni.c
LOCAL_LDLIBS := -landroid -llog
LOCAL_STATIC_LIBRARIES := native_app_glue
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../toolchains/arm-linux-androideabi-4.6/prebuilt/windows/lib/gcc/arm-linux-androideabi/4.6/include $(LOCAL_PATH)/../../../android-ndk-r8e/platforms/android-9/arch-arm/usr/include $(LOCAL_PATH)/../../../android-ndk-r8e/sources/android/native_app_glue

include $(BUILD_SHARED_LIBRARY)


