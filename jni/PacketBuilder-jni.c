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
char buffer1[PACKET_LEN];
struct iphdr* ip = (struct iphdr*)buffer1;
char buffer2[PACKET_LEN];
struct tcphdr* tcp = (struct tcphder*)buffer2;

// IP Header functions
static jboolean BuildIpHeader
(JNIEnv* env, jobject callObj, jobject obj) {

	jboolean result = JNI_TRUE;
	jfieldID fid = NULL;
	LOGI("In function BuildIpHeader");
	jclass klass = (*env)->GetObjectClass(env, obj);
	LOGI("Created ip klass");
	if(klass == NULL)	{
		LOGE("Could not reference the instance of IpHeader");
		return JNI_FALSE;
	}

	fid = (*env)->GetFieldID(env, klass, "ihl", "S");
	if(fid == NULL)	{
		result = JNI_FALSE;;
		LOGE("(C) Could not retrieve ip ihl field ID");
		return result;
	}
	else  {
		short value =  (*env)->GetShortField(env, obj, fid);
		ip->ihl = value;
		LOGI("Set ip ihl value to %i", ip->ihl);
	}

	fid = (*env)->GetFieldID(env, klass, "version", "S");
	if(fid == NULL)	{
		result = JNI_FALSE;
		LOGE("(C) Could not retrieve ip version field ID");
		return result;
	}
	else  {
		short value = (*env)->GetShortField(env, obj, fid);
		ip->version = value;
		LOGI("Set ip version value to %i", ip->version);
	}

	fid = (*env)->GetFieldID(env, klass, "tos", "S");
	if(fid == NULL)	{
		result = JNI_FALSE;
		LOGE("(C) Could not retrieve ip tos field ID");
		return result;
	}
	else  {
		short value = (*env)->GetCharField(env, obj, fid);
		ip->tos = value;
		LOGI("Set ip tos value to %i", ip->tos);
	}

	fid = (*env)->GetFieldID(env, klass, "ttl", "S");
	if(fid == NULL)	{
		result = JNI_FALSE;
		LOGE("(C) Could not retrieve ip tos field ID");
		return result;
	}
	else  {
		short value = (*env)->GetCharField(env, obj, fid);
		ip->ttl = value;
		LOGI("Set ip ttl value to %i", ip->ttl);
	}
	fid = (*env)->GetFieldID(env, klass, "check", "S");
	if(fid == NULL)	{
		result = JNI_FALSE;
		LOGE("(C) Could not retrieve ip check field ID");
		return result;
	}
	else  {
		short value = (*env)->GetCharField(env, obj, fid);
		ip->check = value;
		LOGI("Set ip check value to %i", ip->check);
	}
	fid = (*env)->GetFieldID(env, klass, "tot_len", "S");
	if(fid == NULL)	{
		result = JNI_FALSE;
		LOGE("(C) Could not retrieve ip tot_len field ID");
		return result;
	}
	else  {
		short value = (*env)->GetCharField(env, obj, fid);
		ip->tot_len = value;
		LOGI("Set ip tot_len value to %i", ip->tot_len);
	}
	fid = (*env)->GetFieldID(env, klass, "id", "S");
	if(fid == NULL)	{
		result = JNI_FALSE;
		LOGE("(C) Could not retrieve ip id field ID");
		return result;
	}
	else  {
		short value = (*env)->GetCharField(env, obj, fid);
		ip->id = value;
		LOGI("Set ip id value to %i", ip->id);
	}
	fid = (*env)->GetFieldID(env, klass, "frag_off", "S");
	if(fid == NULL)	{
		result = JNI_FALSE;
		LOGE("(C) Could not retrieve ip frag_off field ID");
		return result;
	}
	else  {
		short value = (*env)->GetCharField(env, obj, fid);
		ip->frag_off = value;
		LOGI("Set ip frag_off value to %i", ip->frag_off);
	}
	fid = (*env)->GetFieldID(env, klass, "saddr", "D");
	if(fid == NULL)	{
		result = JNI_FALSE;
		LOGE("(C) Could not retrieve ip saddr field ID");
		return result;
	}
	else  {
		double value = (*env)->GetDoubleField(env, obj, fid);
		ip->saddr = value;
		LOGI("Set ip saddr value to %i", ip->saddr);
	}
	fid = (*env)->GetFieldID(env, klass, "daddr", "D");
	if(fid == NULL)	{
		result = JNI_FALSE;
		LOGE("(C) Could not retrieve ip daddr field ID");
		return result;
	}
	else  {
		double value = (*env)->GetDoubleField(env, obj, fid);
		ip->daddr = value;
		LOGI("Set ip daddr value to %i", ip->daddr);
	}
	return result;
}

// TCP Header functions
static jboolean BuildTcpHeader
(JNIEnv* env, jobject callObj, jobject obj)	{
	jboolean result = JNI_TRUE;
	jfieldID fid = NULL;
	LOGI("In function BuildTcpHeader");
	jclass klass = (*env)->GetObjectClass(env, obj);
	LOGI("Created tcp klass");
	if(klass == NULL)	{
		LOGE("Could not reference the instance of TcpHeader");
		return JNI_FALSE;
	}

	fid = (*env)->GetFieldID(env, klass, "source", "I");
	if(fid == NULL)	{
		result = JNI_FALSE;;
		LOGE("(C) Could not retrieve tcp source field ID");
		return result;
	}
	else  {
		int value =  (*env)->GetIntField(env, obj, fid);
		tcp->source = value;
		LOGI("Set tcp source value to %i", tcp->source);
	}

	fid = (*env)->GetFieldID(env, klass, "dest", "I");
	if(fid == NULL)	{
		result = JNI_FALSE;;
		LOGE("(C) Could not retrieve tcp dest field ID");
		return result;
	}
	else  {
		int value =  (*env)->GetIntField(env, obj, fid);
		tcp->dest = value;
		LOGI("Set tcp dest value to %i", tcp->dest);
	}

	fid = (*env)->GetFieldID(env, klass, "doff", "I");
	if(fid == NULL)	{
		result = JNI_FALSE;;
		LOGE("(C) Could not tcp retrieve doff field ID");
		return result;
	}
	else  {
		int value =  (*env)->GetIntField(env, obj, fid);
		tcp->doff = value;
		LOGI("Set tcp doff value to %i", tcp->doff);
	}

	fid = (*env)->GetFieldID(env, klass, "res1", "I");
	if(fid == NULL)	{
		result = JNI_FALSE;;
		LOGE("(C) Could not retrieve tcp res1 field ID");
		return result;
	}
	else  {
		int value =  (*env)->GetIntField(env, obj, fid);
		tcp->res1 = value;
		LOGI("Set tcp res1 value to %i", tcp->res1);
	}

	fid = (*env)->GetFieldID(env, klass, "cwr", "I");
	if(fid == NULL)	{
		result = JNI_FALSE;;
		LOGE("(C) Could not retrieve tcp cwr field ID");
		return result;
	}
	else  {
		int value =  (*env)->GetIntField(env, obj, fid);
		tcp->cwr = value;
		LOGI("Set tcp cwr value to %i", tcp->cwr);
	}

	fid = (*env)->GetFieldID(env, klass, "ece", "I");
	if(fid == NULL)	{
		result = JNI_FALSE;;
		LOGE("(C) Could not retrieve tcp ece field ID");
		return result;
	}
	else  {
		int value =  (*env)->GetIntField(env, obj, fid);
		tcp->ece = value;
		LOGI("Set tcp ece value to %i", tcp->ece);
	}

	fid = (*env)->GetFieldID(env, klass, "urg", "I");
	if(fid == NULL)	{
		result = JNI_FALSE;;
		LOGE("(C) Could not retrieve tcp urg field ID");
		return result;
	}
	else  {
		int value =  (*env)->GetIntField(env, obj, fid);
		tcp->urg = value;
		LOGI("Set tcp urg value to %i", tcp->urg);
	}

	fid = (*env)->GetFieldID(env, klass, "ack", "I");
	if(fid == NULL)	{
		result = JNI_FALSE;;
		LOGE("(C) Could not retrieve tcp ack field ID");
		return result;
	}
	else  {
		int value =  (*env)->GetIntField(env, obj, fid);
		tcp->ack = value;
		LOGI("Set tcp ack value to %i", tcp->ack);
	}

	fid = (*env)->GetFieldID(env, klass, "psh", "I");
	if(fid == NULL)	{
		result = JNI_FALSE;;
		LOGE("(C) Could not retrieve tcp psh field ID");
		return result;
	}
	else  {
		int value =  (*env)->GetIntField(env, obj, fid);
		tcp->psh = value;
		LOGI("Set tcp psh value to %i", tcp->psh);
	}

	fid = (*env)->GetFieldID(env, klass, "rst", "I");
	if(fid == NULL)	{
		result = JNI_FALSE;;
		LOGE("(C) Could not retrieve tcp rst field ID");
		return result;
	}
	else  {
		int value =  (*env)->GetIntField(env, obj, fid);
		tcp->rst = value;
		LOGI("Set tcp rst value to %i", tcp->rst);
	}

	fid = (*env)->GetFieldID(env, klass, "syn", "I");
	if(fid == NULL)	{
		result = JNI_FALSE;;
		LOGE("(C) Could not retrieve tcp syn field ID");
		return result;
	}
	else  {
		int value =  (*env)->GetIntField(env, obj, fid);
		tcp->syn = value;
		LOGI("Set tcp syn value to %i", tcp->syn);
	}

	fid = (*env)->GetFieldID(env, klass, "fin", "I");
	if(fid == NULL)	{
		result = JNI_FALSE;;
		LOGE("(C) Could not retrieve tcp fin field ID");
		return result;
	}
	else  {
		int value =  (*env)->GetIntField(env, obj, fid);
		tcp->fin = value;
		LOGI("Set tcp fin value to %i", tcp->fin);
	}

	fid = (*env)->GetFieldID(env, klass, "window", "I");
	if(fid == NULL)	{
		result = JNI_FALSE;;
		LOGE("(C) Could not retrieve tcp window field ID");
		return result;
	}
	else  {
		int value =  (*env)->GetIntField(env, obj, fid);
		tcp->window = value;
		LOGI("Set tcp window value to %i", tcp->window);
	}

	fid = (*env)->GetFieldID(env, klass, "check", "I");
	if(fid == NULL)	{
		result = JNI_FALSE;;
		LOGE("(C) Could not retrieve tcp check field ID");
		return result;
	}
	else  {
		int value =  (*env)->GetIntField(env, obj, fid);
		tcp->check = value;
		LOGI("Set tcp check value to %i", tcp->check);
	}
	fid = (*env)->GetFieldID(env, klass, "seq", "I");
	if(fid == NULL)	{
		result = JNI_FALSE;;
		LOGE("(C) Could not retrieve tcp seq field ID");
		return result;
	}
	else  {
		int value =  (*env)->GetDoubleField(env, obj, fid);
		tcp->seq = value;
		LOGI("Set tcp seq value to %i", tcp->seq);
	}

		fid = (*env)->GetFieldID(env, klass, "ack_seq", "I");
		if(fid == NULL)	{
			result = JNI_FALSE;;
			LOGE("(C) Could not retrieve tcp ack_seq field ID");
			return result;
		}
		else  {
			int value =  (*env)->GetDoubleField(env, obj, fid);
			tcp->ack_seq = value;
			LOGI("Set tcp ack_seq value to %i", tcp->ack_seq);
		}

	}																																    }																															    }
	return result;
}

// Send packet
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

