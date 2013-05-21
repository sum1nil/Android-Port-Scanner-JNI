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

#include "IpHeader.h"
#include "TcpHeader.h"
//END_INCLUDE(all)

// Global references
static jclass ipCls = 0;
static jclass tcpCls = 0;
static jfieldID fid;



#define PACKET_LEN  81928

#define LOGI(...) ((void)android_log_print(ANDROID_LOG_INFO, "PortScannerActivity", __VA_ARGS__))
#define LOGW(...) ((void)android_log_print(ANDROID_LOG_WARN, "PortScannerActivity", __VA_ARGS__))
#define LOGE(...) ((void)android_log_print(ANDROID_LOG_ERROR, "PortScannerActivity", __VA_ARGS__))

// IP Header functions
  jboolean   Java_com_wly_net_IpHeader_buildIpHeader
  (JNIEnv * env, jobject thiz, jobject obj)	{
	jboolean result = JNI_TRUE;
	char buffer[PACKET_LEN];
	struct iphdr* ip = (struct iphdr*)buffer;
	if (ipCls == 0) {
	    jclass cls1 = (*env)->GetObjectClass(env, obj);
	    if (cls1 == 0) {
	    	result = JNI_FALSE;
	    	return result;
	    }
	    ipCls = (*env)->NewGlobalRef(env, obj);
	    if (ipCls == 0) {
	    	result = JNI_FALSE;
	    	return result;
	    }
	      
	    fid = (*env)->GetFieldID(env, ipCls, "ihl", "B");
	    ip->ihl = (*env)->GetByteField(env, ipCls, fid);
	    fid = (*env)->GetFieldID(env, ipCls, "version", "B");
	    ip->version = (*env)->GetByteField(env, ipCls, fid);
	    fid = (*env)->GetFieldID(env, ipCls, "tos", "B");
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

	}
	return result;
}

// TCP Header functions
  jboolean   Java_com_wly_net_TcpHeader_buildTcpHeader
  (JNIEnv* env, jobject thiz, jobject obj)	{
	jboolean result = JNI_TRUE;

	return result;
}

// Send packet
  jboolean   Java_com_wly_net_PortScannerActivity_sendPacket
  (JNIEnv* env, jobject thiz)	{
	jboolean result = JNI_TRUE;

	return result;
}

  jchar   Java_com_wly_net_PortScannerActivity_computeChecksum
  (JNIEnv* env, jobject thiz, jbyte buf, jint numWords)	{
	jchar result = 456;

	return result;
}


