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

	public native boolean buildIpHeader(IpHeader ipHeader);
	
	private byte ihl, ver, tos, flag, ttl, protocol;
	public  byte getIhl(){ return ihl; }
	public  void setIhl(byte ihl){ this.ihl = ihl; }

	public  byte getVer(){ return ver; }
	public  void setVer(byte ver){ this.ver = ver; }

	public  byte getTos(){ return tos; }
	public  void setTos(byte tos){ this.tos = tos; }

	public  byte getFlag(){ return flag; }
	public  void setFlag(byte flag){ this.flag = flag; }

	public  byte getTtl(){return ttl; }
	public  void setTtl(byte ttl){this.ttl = ttl; }

	public  byte setProtocol(){ return protocol; }
	public  void setProtocol(byte protocol){ this.protocol = protocol; }

	private char len, ident,offset, chksum;
	public  char getLen(){ return len; }
	public  void setLen(char len){ this.len = len; }
	
	public  char getIdent(){ return ident; }
	public  void setIdent(char ident){ this.ident = ident; }

	public  char getOffset(){ return offset; }
	public  void setOffset(char offset){ this.offset = offset; }

	public  char getChksum(){ return chksum; }
	public  void setChksum(char chksum){ this.chksum = chksum; }

	private int sourceIp, destIp;
	public  int getSourceIp(){ return sourceIp; }
	public  void setSourceIp(int sourceIp){ this.sourceIp = sourceIp; }

	public  int getDestIp(){ return destIp; }
	public  void setDestIp(int destIp){ this.destIp = destIp; }

	
}
