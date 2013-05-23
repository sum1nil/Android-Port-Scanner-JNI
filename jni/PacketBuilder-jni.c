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
 #define NULL ((void *) 0)
 
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
//END_INCLUDE(all)

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "PortScannerActivity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "PortScannerActivity", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "PortScannerActivity", __VA_ARGS__))
#define PACKET_LEN  81928

// Global references
char buffer[PACKET_LEN];
struct iphdr* ip = (struct iphdr*)buffer;

// IP Header functions
static jboolean BuildIpHeader
  (JNIEnv* env, jobject thiz, jobject obj) {
	LOGI("In function BuildIpHeader");
	jboolean result = JNI_TRUE;
	jfieldID fid = 0;
	jclass =
	fid = (*env)->GetFieldID(env, obj, "ihl", "B");
	if(fid == NULL)	{
	   		result = JNI_FALSE;;
	    	LOGE("(C) Could not retrieve  ihl field");
	    	return result;
	    }
	    else  {
	    	jchar value = (*env)->GetByteField(env, obj, fid);
	    	ip->ihl = value;
	    	LOGI("Set ihl value to %i", ip->ihl);
	    }
	    
	    fid = (*env)->GetFieldID(env, obj, "version", "B");
	    if(fid == NULL)	{
	   		result = JNI_FALSE;
	    	LOGE("(C) Could not retrieve version  field");
	    	return result;
	    }
	    else  {
	    	jchar value = (*env)->GetByteField(env, obj, fid);
	    	ip->version = value;
	    	LOGI("Set version value to %i", ip->version);
	    }
	  
	    fid = (*env)->GetFieldID(env, obj, "tos", "B");
	    if(fid == NULL)	{
	   		result = JNI_FALSE;
	    	LOGE("(C) Could not retrieve tos field");
	    	return result;
	    }
	    else  {
	    	jchar value = (*env)->GetByteField(env, obj, fid);
	    	ip->tos = value;
	    	LOGI("Set tos value to %i", ip->tos);
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
static jboolean BuildTcpHeader
  (JNIEnv* env, jobject thiz, jobject obj)	{
	jboolean result = JNI_TRUE;

	return result;
}

// Send packeto
static jboolean SendPacket
  (JNIEnv* env, jobject thiz)	{
	jboolean result = JNI_TRUE;

	return result;
}
// Compute packet checksum value
static jlong ComputeCheckSum
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
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)	{
	LOGI("Executing JNI_OnLoad");
	// Checks JNI version
	JNIEnv *env;
	jclass thiz;
	static const char* const strClassName="com/wly/net/PortScannerActivity";
	

	// Checks JNI version
    if((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_2) != JNI_OK){
        LOGE("JNI Check failure");
        return JNI_ERR;
    }
    // Checks if environment is null
    if (env == NULL) {
        LOGE("Env is NULL");
        return JNI_ERR;
    }
    thiz = (*env)->FindClass(env, strClassName);
    if(thiz == NULL){
        LOGE("Find Class returns NULL");
        return JNI_ERR;
    }
    
    static JNINativeMethod methods[] = { 
    {"sendPacket", "()Z", (void *)&SendPacket},
    {"computeCheckSum", "(I)J", (void *)&ComputeCheckSum}, 
    {"buildIpHeader", "(Lcom/wly/net/IpHeader;)Z", (void *)&BuildIpHeader},
    {"buildTcpHeader", "(Lcom/wly/net/TcpHeader;)Z", (void *)&BuildTcpHeader}
    };
    
    if ((*env)->RegisterNatives(env, thiz, methods, sizeof(methods)/sizeof(methods[0])) != JNI_OK){
        LOGE("Method registration failure");
        return JNI_ERR;
    }
    else
    	LOGI("Method registration succeeded");
		
    LOGI("Successfully executed JNI_onLoad");
    return JNI_VERSION_1_2;

}

