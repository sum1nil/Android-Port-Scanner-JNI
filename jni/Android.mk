LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := packetbuilder
LOCAL_SRC_FILES := PacketBuilder-jni.c
LOCAL_LDLIBS := -landroid -llog
LOCAL_STATIC_LIBRARIES := native_app_glue
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include $(LOCAL_PATH)/native_app_glue

include $(BUILD_SHARED_LIBRARY)
