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
#define LOGI(...) ((void)android_log_print(ANDROID_LOG_INFO, "PortScannerActivity", __VA_ARGS__))
#define LOGW(...) ((void)android_log_print(ANDROID_LOG_WARN, "PortScannerActivity", __VA_ARGS__))
#define LOGE(...) ((void)android_log_print(ANDROID_LOG_ERROR, "PortScannerActivity", __VA_ARGS__))
#define PACKET_LEN  81928

// Global references
char buffer[PACKET_LEN];
struct iphdr* ip = (struct iphdr*)buffer;

jboolean result = JNI_TRUE;

// IP Header functions
jboolean   Java_com_wly_net_IpHeader_buildIpHeader(JNIEnv * env, jobject thiz, jobject obj)	{
	
		jfieldID fid = 0;
		jclass ipCls = 0;
		ipCls = (*env)->GetObjectClass(env, obj);
	  if (ipCls == 0) {
	    	result = JNI_FALSE;
	    	LOGE("(C) Could not retrieve ip java class");
	    	return result;
	  }
	    
	   	fid = (*env)->GetFieldID(env, ipCls, "ihl", "B");
	   	if(fid == 0)	{
	   		result = JNI_FALSE;;
	    	LOGE("(C) Could not retrieve ip class ihl value");
	    	return result;
	    }
	    else  {
	    	ip->ihl = (*env)->GetByteField(env, ipCls, fid);
	    	LOGI("Set ip class ihl value to %d", ip->ihl);
	    }
	    
	    fid = (*env)->GetFieldID(env, ipCls, "version", "B");
	    if(fid == 0)	{
	   		result = JNI_FALSE;
	    	LOGE("(C) Could not retrieve ip class version value");
	    	return result;
	    }
	    else  {
	    	ip->version = (*env)->GetByteField(env, ipCls, fid);
	    	LOGI("Set ip class version value to ", ip->version);
	    }
	  
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
	jclass tcpCls = 0;

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
  unsigned long sum = 0;
	for(sum=0; nwords>0; nwords--) sum += *buf++  {
	sum = (sum >> 16) + (sum &0xffff); 
	sum += (sum >> 16); 
	}
	return (unsigned short)(~sum); 
}


