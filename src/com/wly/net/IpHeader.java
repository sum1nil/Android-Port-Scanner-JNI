package com.wly.net;
/*
// The IP header's structure 
struct ipheader { 
unsigned char iph_ihl:5, iph_ver:4; 
unsigned char iph_tos; 
unsigned short int iph_len;
unsigned short int iph_ident; 
unsigned char iph_flag; 
unsigned short int iph_offset; 
unsigned char iph_ttl; 
unsigned char iph_protocol; 
unsigned short int iph_chksum; 
unsigned int iph_sourceip;
unsigned int iph_destip; 
};
*/
public class IpHeader
{
	public IpHeader(byte ihl, byte ver, byte tos, byte flag, byte ttl, byte protocol, char len,
			char ident, char offset, char chksum, int sourceIp, int destIp) {
					this.ihl = ihl;
					this.ver = ver;
					this.tos = tos;
					this.flag = flag;
					this.ttl = ttl;
					this.protocol = protocol;
					this.len = len;
					this.ident = ident;
					this.offset = offset;
					this.chksum = chksum;
					this.sourceIp = sourceIp;
					this.destIp = destIp;
	}

	private byte ihl, ver, tos, flag, ttl, protocol;
	public native byte getIhl(); // { return ihl; }
	public native byte getVer(); // { return ver; }
	public native byte getTos(); // { return tos; }
	public native byte getFlag(); // { return flag; }
	public native byte getTtl(); // {return ttl; }
	public native byte getProtocol(); // { return protocol; }
	
	private char len, ident,offset, chksum;
	public native char getLen(); // { return len; }
	public native char getIdent(); // { return ident; }
	public native char getOffset(); // { return offset; }
	public native char getChksum(); // { return chksum; }
	
	private int sourceIp, destIp;
	public native int getSourceIp(); // { return sourceIp; }
	public native int getDestIp(); // { return destIp; }
	
	
}
