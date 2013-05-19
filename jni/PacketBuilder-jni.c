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
//BEGIN_INCLUDE(all)
#include <string.h>
#include <jni.h>
#include <errno.h>

#include <unistd.h>
#include <stdio.h> 
#include <sys/socket.h> 
#include <netinet/ip.h> 
#include <netinet/tcp.h>

#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>

#include "Packets.h"
//END_INCLUDE(all)

// Global references
static jclass ipCls = 0;
static jclass tcpCls = 0;
static jfieldID fid;

#define __BIG_ENDIAN_BITFIELD
#define PACKET_LEN = 81928
#define LOGI(...) ((void)android_log_print(ANDROID_LOG_INFO, "PortScannerActivity", __VA_ARGS__))
#define LOGW(...) ((void)android_log_print(ANDROID_LOG_WARN, "PortScannerActivity", __VA_ARGS__))

// Check for endianess
bool isBigEndian()
{
int no = 1;
char *chk = (char *)&no;

if (chk[0] == 1)
	{
	return 0;
	}
	else
	{
	return 1;
	}
}

// IP Header functions
JNIEXPORT jboolean JNICALL Java_com_wly_net_IpHeader_buildIpHeader
  (JNIEnv* env, jobject thiz, jobject obj)	{
	jboolean result = JNI_TRUE;
	char buffer[] = char[PACKET_LEN];
	struct iphdr* ip = (struct iphdr*)buffer;
	struct sockaddr_in sin,din;
	if (ipCls == 0) {
	    jclass cls1 = (*env)->GetObjectClass(env, obj);
	    if (cls1 == 0)
	      return;
	    ipCls = (*env)->NewGlobalRef(env, cls1);
	    if (ipCls == 0)
	      return;
	    //	public IpHeader(byte ihl, byte ver, byte tos, byte flag, byte ttl, byte protocol, char len,
		// char ident, char offset, char chksum, int sourceIp, int destIp)
	    fid = (*env)->GetFieldID(env, cls1, "ihl", "B");
	    ip->ihl = (*env)->GetByteField(env, obj, fid);

	  }
	  ... /* access the field using cls and fid */
	return result
}
// TCP Header functions
JNIEXPORT jboolean JNICALL Java_com_wly_net_TcpHeader_buildTcpHeader
  (JNIEnv* env, jobject thiz, jobject obj)	{
	jboolean result = JNI_TRUE;

	return result;
}

// Send packet
JNIEXPORT jboolean JNICALL Java_com_wly_net_PortScannerActivity_sendPacket
  (JNIEnv* env, jobject thiz)	{
	jboolean result = JNI_TRUE;

	return result;
}

