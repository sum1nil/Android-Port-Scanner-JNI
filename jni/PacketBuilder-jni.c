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
#if (BYTE_ORDER == LITTLE_ENDIAN)
#define __LITTLE_ENDIAN_BITFIELD
#elif (BYTE_ORDER == BIG_ENDIAN)
#define __BIG_ENDIAN_BITFIELD
#endif
#include <android/api-level.h>
#include <android/log.h>
#include <android_native_app_glue.h>
//END_INCLUDE(all)

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "PortScannerActivity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "PortScannerActivity", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "PortScannerActivity", __VA_ARGS__))
#define PACKET_LEN  4096
/*
struct Packet {
	struct pseudo_header phdr;
	struct iphdr iph;
	struct tcphdr tcph;
};
*/

/*
    96 bit (12 bytes) pseudo header needed for tcp header checksum calculation
*/
struct pseudo_header
{
    u_int32_t source_address;
    u_int32_t dest_address;
    u_int8_t placeholder;
    u_int8_t protocol;
    u_int16_t tcp_length;
};
// Global references
char datagram[PACKET_LEN];
// IP Header
struct iphdr* ip = (struct iphdr*)datagram;
// TCP Header
struct tcphdr* tcp = (struct tcphdr*)(datagram + sizeof(struct ip));
// Raw Socket
struct sockaddr_in s_in;
//
struct pseudo_header phdr;
static jfieldID fid = NULL;
// IP Header functions
static jboolean BuildIpHeader
(JNIEnv* env, jobject callObj, jobject obj) {

	jboolean result = JNI_TRUE;

	LOGI("In function BuildIpHeader");
	jclass klass = (*env)->GetObjectClass(env, obj);
	LOGI("Created ip klass");
	if(klass == NULL)	{
		LOGE("Could not reference the instance of IpHeader");
		return JNI_FALSE;
	}

	fid = (*env)->GetFieldID(env, klass, "ihl", "C");
	if(fid == NULL)	{
		result = JNI_FALSE;;
		LOGE("(C) Could not retrieve ip ihl field ID");
		return result;
	}
	else  {
		__u8 value =  (*env)->GetCharField(env, obj, fid);
		ip->ihl = value;
		LOGI("Set ip ihl value to %i", ip->ihl);
	}

	fid = (*env)->GetFieldID(env, klass, "version", "C");
	if(fid == NULL)	{
		result = JNI_FALSE;
		LOGE("(C) Could not retrieve ip version field ID");
		return result;
	}
	else  {
		__u8 value = (*env)->GetCharField(env, obj, fid);
		ip->version = value;
		LOGI("Set ip version value to %i", ip->version);
	}

	fid = (*env)->GetFieldID(env, klass, "tos", "C");
	if(fid == NULL)	{
		result = JNI_FALSE;
		LOGE("(C) Could not retrieve ip tos field ID");
		return result;
	}
	else  {
		__u8 value = (*env)->GetCharField(env, obj, fid);
		ip->tos = value;
		LOGI("Set ip tos value to %i", ip->tos);
	}

	fid = (*env)->GetFieldID(env, klass, "ttl", "C");
	if(fid == NULL)	{
		result = JNI_FALSE;
		LOGE("(C) Could not retrieve ip tos field ID");
		return result;
	}
	else  {
		__u8 value = (*env)->GetCharField(env, obj, fid);
		ip->ttl = value;
		LOGI("Set ip ttl value to %i", ip->ttl);
	}

	fid = (*env)->GetFieldID(env, klass, "tot_len", "S");
	if(fid == NULL)	{
		result = JNI_FALSE;
		LOGE("(C) Could not retrieve ip tot_len field ID");
		return result;
	}
	else  {
		__be16 value = (*env)->GetShortField(env, obj, fid);
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
		__be16 value = (*env)->GetShortField(env, obj, fid);
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
		__be16 value = (*env)->GetShortField(env, obj, fid);
		ip->frag_off = value;
		LOGI("Set ip frag_off value to %i", ip->frag_off);
	}

	fid = (*env)->GetFieldID(env, klass, "check", "I");
	if(fid == NULL)	{
		result = JNI_FALSE;
		LOGE("(C) Could not retrieve ip check field ID");
		return result;
	}
	else  {
		__u16 value = (*env)->GetIntField(env, obj, fid);
		ip->check = value;
		LOGI("Set ip check value to %i", ip->check);
	}

	fid = (*env)->GetFieldID(env, klass, "saddr", "I");
	if(fid == NULL)	{
		result = JNI_FALSE;
		LOGE("(C) Could not retrieve ip saddr field ID");
		return result;
	}
	else  {
		__be32 value = (*env)->GetIntField(env, obj, fid);
		ip->saddr = value;
		LOGI("Set ip saddr value to %i", ip->saddr);
	}
	fid = (*env)->GetFieldID(env, klass, "daddr", "I");
	if(fid == NULL)	{
		result = JNI_FALSE;
		LOGE("(C) Could not retrieve ip daddr field ID");
		return result;
	}
	else  {
		__be32 value = (*env)->GetIntField(env, obj, fid);
		ip->daddr = value;
		LOGI("Set ip daddr value to %i", ip->daddr);
	}
	fid = NULL;
	return result;
}

// TCP Header functions
static jboolean BuildTcpHeader
(JNIEnv* env, jobject callObj, jobject obj)	{
	jboolean result = JNI_TRUE;
	LOGI("In function BuildTcpHeader");
	jclass klass = (*env)->GetObjectClass(env, obj);


	if(klass == NULL)	{
		LOGE("Could not reference the instance of TcpHeader");
		return JNI_FALSE;
	}
	else	{
		LOGI("Created tcp klass");
	}

	fid = (*env)->GetFieldID(env, klass, "source", "S");
	if(fid == NULL)	{
		result = JNI_FALSE;;
		LOGE("(C) Could not retrieve tcp source field ID");
		return result;
	}
	else  {
		__u16 value =  (*env)->GetShortField(env, obj, fid);
		tcp->source = value;
		LOGI("Set tcp source value to %i", tcp->source);
	}

	fid = (*env)->GetFieldID(env, klass, "dest", "S");
	if(fid == NULL)	{
		result = JNI_FALSE;;
		LOGE("(C) Could not retrieve tcp dest field ID");
		return result;
	}
	else  {
		__u16 value =  (*env)->GetShortField(env, obj, fid);
		tcp->dest = value;
		LOGI("Set tcp dest value to %i", tcp->dest);
	}

	fid = (*env)->GetFieldID(env, klass, "doff", "S");
	if(fid == NULL)	{
		result = JNI_FALSE;;
		LOGE("(C) Could not tcp retrieve doff field ID");
		return result;
	}
	else  {
		__u16 value =  (*env)->GetShortField(env, obj, fid);
		tcp->doff = value;
		LOGI("Set tcp doff value to %i", tcp->doff);
	}

	fid = (*env)->GetFieldID(env, klass, "res1", "S");
	if(fid == NULL)	{
		result = JNI_FALSE;;
		LOGE("(C) Could not retrieve tcp res1 field ID");
		return result;
	}
	else  {
		__u16 value =  (*env)->GetShortField(env, obj, fid);
		tcp->res1 = value;
		LOGI("Set tcp res1 value to %i", tcp->res1);
	}

	fid = (*env)->GetFieldID(env, klass, "cwr", "S");
	if(fid == NULL)	{
		result = JNI_FALSE;;
		LOGE("(C) Could not retrieve tcp cwr field ID");
		return result;
	}
	else  {
		__u16 value =  (*env)->GetShortField(env, obj, fid);
		tcp->cwr = value;
		LOGI("Set tcp cwr value to %i", tcp->cwr);
	}

	fid = (*env)->GetFieldID(env, klass, "ece", "S");
	if(fid == NULL)	{
		result = JNI_FALSE;;
		LOGE("(C) Could not retrieve tcp ece field ID");
		return result;
	}
	else  {
		__u16 value =  (*env)->GetShortField(env, obj, fid);
		tcp->ece = value;
		LOGI("Set tcp ece value to %i", tcp->ece);
	}

	fid = (*env)->GetFieldID(env, klass, "urg", "S");
	if(fid == NULL)	{
		result = JNI_FALSE;;
		LOGE("(C) Could not retrieve tcp urg field ID");
		return result;
	}
	else  {
		__u16 value =  (*env)->GetShortField(env, obj, fid);
		tcp->urg = value;
		LOGI("Set tcp urg value to %i", tcp->urg);
	}

	fid = (*env)->GetFieldID(env, klass, "ack", "S");
	if(fid == NULL)	{
		result = JNI_FALSE;;
		LOGE("(C) Could not retrieve tcp ack field ID");
		return result;
	}
	else  {
		__u16 value =  (*env)->GetShortField(env, obj, fid);
		tcp->ack = value;
		LOGI("Set tcp ack value to %i", tcp->ack);
	}

	fid = (*env)->GetFieldID(env, klass, "psh", "S");
	if(fid == NULL)	{
		result = JNI_FALSE;;
		LOGE("(C) Could not retrieve tcp psh field ID");
		return result;
	}
	else  {
		__u16 value =  (*env)->GetShortField(env, obj, fid);
		tcp->psh = value;
		LOGI("Set tcp psh value to %i", tcp->psh);
	}

	fid = (*env)->GetFieldID(env, klass, "rst", "S");
	if(fid == NULL)	{
		result = JNI_FALSE;;
		LOGE("(C) Could not retrieve tcp rst field ID");
		return result;
	}
	else  {
		__u16 value =  (*env)->GetShortField(env, obj, fid);
		tcp->rst = value;
		LOGI("Set tcp rst value to %i", tcp->rst);
	}

	fid = (*env)->GetFieldID(env, klass, "syn", "S");
	if(fid == NULL)	{
		result = JNI_FALSE;;
		LOGE("(C) Could not retrieve tcp syn field ID");
		return result;
	}
	else  {
		__u16 value =  (*env)->GetShortField(env, obj, fid);
		tcp->syn = value;
		LOGI("Set tcp syn value to %i", tcp->syn);
	}

	fid = (*env)->GetFieldID(env, klass, "fin", "S");
	if(fid == NULL)	{
		result = JNI_FALSE;;
		LOGE("(C) Could not retrieve tcp fin field ID");
		return result;
	}
	else  {
		__u16 value =  (*env)->GetShortField(env, obj, fid);
		tcp->fin = value;
		LOGI("Set tcp fin value to %i", tcp->fin);
	}

	fid = (*env)->GetFieldID(env, klass, "window", "S");
	if(fid == NULL)	{
		result = JNI_FALSE;;
		LOGE("(C) Could not retrieve tcp window field ID");
		return result;
	}
	else  {
		__u16 value =  (*env)->GetShortField(env, obj, fid);
		tcp->window = value;
		LOGI("Set tcp window value to %i", tcp->window);
	}

	fid = (*env)->GetFieldID(env, klass, "check", "S");
	if(fid == NULL)	{
		result = JNI_FALSE;;
		LOGE("(C) Could not retrieve tcp check field ID");
		return result;
	}
	else  {
		__u16 value =  (*env)->GetShortField(env, obj, fid);
		tcp->check = value;
		LOGI("Set tcp check value to %i", tcp->check);
	}

	fid = (*env)->GetFieldID(env, klass, "seq", "J");
	if(fid == NULL)	{
		result = JNI_FALSE;;
		LOGE("(C) Could not retrieve tcp seq field ID");
		return result;
	}
	else  {
		__u32 value =  (*env)->GetLongField(env, obj, fid);
		tcp->seq = value;
		LOGI("Set tcp seq value to %i", tcp->seq);
	}

		fid = (*env)->GetFieldID(env, klass, "ack_seq", "J");
		if(fid == NULL)	{
			result = JNI_FALSE;;
			LOGE("(C) Could not retrieve tcp ack_seq field ID");
			return result;
		}
		else  {
			__u32 value =  (*env)->GetLongField(env, obj, fid);
			tcp->ack_seq = value;
			LOGI("Set tcp ack_seq value to %i", tcp->ack_seq);
		}
		return result;
	}

// Send packet
static jboolean SendPacket
(JNIEnv* env, jobject thiz)	{
	jboolean result = JNI_TRUE;
	int s = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);

	int one = 1;
	const int *val = &one;
	if (setsockopt (s, IPPROTO_IP, IP_HDRINCL, val, sizeof (one)) < 0)
	{
	    LOGE("Error setting IP_HDRINCL. Error number : %d . Error message : %s \n" , errno , strerror(errno));
	    return JNI_FALSE;
	}
    //Datagram to represent the packet
    char datagram[4096] , source_ip[32] , *data , *pseudogram;

    //zero out the packet buffer
    memset (datagram, 0, 4096);

	//Data part
	data = datagram + sizeof(struct iphdr) + sizeof(struct tcphdr);
	strcpy(data , "ABCDEFGHIJKLMNOPQRSTUVWXYZ");



	return result;
}

// Compute packet checksum value
static jshort ComputeCheckSum
(JNIEnv* env, jobject thiz, jint nbytes)	{
	register long sum = 0;
	unsigned short oddByte;
	register short answer;

	unsigned short* ptr = (unsigned short*)datagram;
	while(nbytes > 1)	{
		sum += *ptr++;
		nbytes -= 2;
	}
	if(nbytes == 1)	{
		oddByte = 0;
		*((u_char*)&oddByte)= *(u_char*)ptr;
		sum += oddByte;
	}

	sum = (sum>>16) +  (sum & 0xffff);
	sum = sum + (sum>>16);
	answer = (short)~sum;

	return answer;
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
			{"computeCheckSum", "(I)S", (void *)&ComputeCheckSum},
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

