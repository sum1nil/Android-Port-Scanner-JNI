LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := packetbuilder
LOCAL_SRC_FILES := PacketBuilder-jni.c
LOCAL_LDLIBS := -landroid -llog -ldl
LOCAL_STATIC_LIBRARIES := native_app_glue c m stdc++
LOCAL_C_INCLUDES := /data/data/com.aide.ui/files/ndksupport-20130506/android-ndk-aide/sources/android/native_app_glue /data/data/com.aide.ui/files/ndksupport-20130506/android-ndk-aide/platforms/android-4/arch-arm/usr/include /data/data/com.aide.ui/files/ndksupport-20130506/android-ndk-aide/toolchains/arm-linux-androideabi-4.6/prebuilt/linux-arm/lib/gcc/arm-linux-androideabi/4.6/include

include $(BUILD_SHARED_LIBRARY)


