/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#if (BYTE_ORDER == LITTLE_ENDIAN)
  #define __LITTLE_ENDIAN_BITFIELD
#elif (BYTE_ORDER == BIG_ENDIAN)
  #define __BIG_ENDIAN_BITFIELD
#endif

//BEGIN_INCLUDE(all)
#include <jni.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h> 
#include <endian.h>
#include <sys/socket.h> 
#include <netinet/ip.h> 
#include <netinet/tcp.h>

#include <android/api-level.h>
#include <android/log.h>
#include <android_native_app_glue.h>

#include "Packets.h"
//END_INCLUDE(all)

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "PortScannerActivity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "PortScannerActivity", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "PortScannerActivity", __VA_ARGS__))
#define PACKET_LEN  81928

// Global references
char buffer[PACKET_LEN];
struct iphdr* ip = (struct iphdr*)buffer;


JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved)	{
	LOGI("Loaded the library");

	return JNI_VERSION_1_4;
}

// IP Header functions
JNIEXPORT jboolean JNICALL Java_com_wly_net_PortScannerActivity_buildIpHeader
  (JNIEnv* env, jobject thiz, jobject obj) {
	jboolean result = JNI_TRUE;
	jfieldID fid = 0;
	jclass ipCls = (*env)->GetObjectClass(env, obj);
	if (ipCls == 0) {
	    	result = JNI_FALSE;
	    	LOGE("(C) Could not retrieve IpHeader instance");
	    	return result;
	  }
	    
	   	fid = (*env)->GetFieldID(env, ipCls, "ihl", "B");
	   	if(fid == 0)	{
	   		result = JNI_FALSE;;
	    	LOGE("(C) Could not retrieve ip  ihl field");
	    	return result;
	    }
	    else  {
	    	jbyte value = (*env)->GetByteField(env, ipCls, fid);
	    	ip->ihl = value;
	    	LOGI("Set ip class ihl value to %i", ip->ihl);
	    }
	    
	    fid = (*env)->GetFieldID(env, ipCls, "version", "B");
	    if(fid == 0)	{
	   		result = JNI_FALSE;
	    	LOGE("(C) Could not retrieve ip   version  field");
	    	return result;
	    }
	    else  {
	    	jbyte value = (*env)->GetByteField(env, ipCls, fid);
	    	ip->version = value;
	    	LOGI("Set ip class version value to %i", ip->version);
	    }
	  
	    fid = (*env)->GetFieldID(env, ipCls, "tos", "B");
	    if(fid == 0)	{
	   		result = JNI_FALSE;
	    	LOGE("(C) Could not retrieve tos field");
	    	return result;
	    }
	    else  {
	    	jbyte value = (*env)->GetByteField(env, ipCls, fid);
	    	ip->tos = value;
	    	LOGI("Set ip class tos value to %i", ip->tos);
	    }
	    /*
	    ip->tos = (*env)->GetByteField(env, ipCls, fid);
	    fid = (*env)->GetFieldID(env, ipCls, "ttl", "B");
	    ip->ttl = (*env)->GetByteField(env, ipCls, fid);
	    fid = (*env)->GetFieldID(env,ipCls, "check", "S");
	    ip->check = (*env)->GetShortField(env, ipCls, fid);
	    fid = (*env)->GetFieldID(env,ipCls, "tot_len", "S");
	    ip->tot_len = (*env)->GetShortField(env, ipCls, fid);
	    fid = (*env)->GetFieldID(env,ipCls, "id", "S");
	    ip->id = (*env)->GetShortField(env, ipCls, fid);
	    fid = (*env)->GetFieldID(env, ipCls, "saddr", "F");
	    ip->saddr = (*env)->GetFloatField(env, ipCls, fid);
	    fid = (*env)->GetFieldID(env, ipCls, "daddr", "F");
	    ip->daddr = (*env)->GetFloatField(env, ipCls, fid);
		*/
	    return result;
}

// TCP Header functions
JNIEXPORT jboolean JNICALL  Java_com_wly_net_TcpHeader_buildTcpHeader
  (JNIEnv* env, jobject thiz, jobject obj)	{
	jboolean result = JNI_TRUE;
	jclass tcpCls = 0;

	return result;
}

// Send packet
JNIEXPORT  jboolean JNICALL  Java_com_wly_net_PortScannerActivity_sendPacket
  (JNIEnv* env, jobject thiz)	{
	jboolean result = JNI_TRUE;

	return result;
}
// Compute packet checksum value
JNIEXPORT jlong JNICALL Java_com_wly_net_PortScannerActivity_computeChecksum
  (JNIEnv* env, jobject thiz, jint nwords)	{
  unsigned long sum = 0;
  unsigned short* buf = (unsigned short*)buffer;
	for(sum=0; nwords>0; nwords--) {
		sum += *buf++;
		sum = (sum >> 16) + (sum &0xffff);
		sum += (sum >> 16);
	}
	return (long)(~sum);
}
JNIEXPORT jint JNICALL JNI_OnLoad(Java_VM* vm, void* reserved)	{
	LOGI("Executing JNI_OnLoad");
	// Checks JNI version
	JNIEnv *env;
	jint onLoad_err = -1;
	jclass k;
	static const char* const strClassName="com/wly/net/PortScannerActivity";
	JavaVMInitArgs vm_args;
	if(JNI_GetDefaultJavaVMInitArgs(vm_args) == NULL)  {
		LOGE("Get VM args failed");
		return onLoad_err;
	}

	// Checks JNI version
    if((*vm)->GetEnv(vm, (void**) &env, vm_args.version) != JNI_OK){
        LOGE("JNI Check failure");
        return onLoad_err;
    }
    // Checks if environment is null
    if (env == NULL) {
        LOGE("Env is NULL");
        return onLoad_err;
    }
    k = (*env)->FindClass(env, strClassName1);
    if(k == NULL){
        LOGE("Find Class returns NULL");
        return onLoad_err;
    }
    if ((*env)->RegisterNatives(env, k, methods, sizeof(methods)/sizeof(methods[0])) != JNI_OK){
        LOGE("Method registration failure");
        return onLoad_err;
    }

    LOGI("Successfully executed JNI_onLoad");
    return vm_args.version;

}

