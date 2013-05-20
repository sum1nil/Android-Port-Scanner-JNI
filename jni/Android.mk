LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := packetbuilder
LOCAL_SRC_FILES := PacketBuilder-jni.c
LOCAL_LDLIBS := -landroid -llog
LOCAL_STATIC_LIBRARIES := native_app_glue
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include $(LOCAL_PATH)/native_app_glue

<<<<<<< HEAD
include $(BUILD_SHARED_LIBRARY)
=======
include $(BUILD_SHARED_LIBRARY)
>>>>>>> 5cbead8cb758b180e7df8d9eee3f8096dfd1e193
