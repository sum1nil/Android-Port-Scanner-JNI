package com.wly.net;

// The IP header's structure 
//384 bits
public class IpHeader
{
	public IpHeader(char ihl, char version,  char tos, char ttl, char protocol, short tot_len,
			short id, short frag_off, int ipCheck, int saddr, int daddr) {
					this.ihl = ihl;
					this.version = version;
					this.tos = tos;
					this.ttl = ttl;
					this.ipCheck = ipCheck;
					this.id = id;
					this.frag_off = frag_off;
					this.tot_len = tot_len;
					this.saddr = saddr;
					this.daddr = daddr;
	}

	
	public IpHeader() {
		// TODO Auto-generated constructor stub
		this.ihl = 0;
		this.version = 0;
		this.tos = 0;
		this.ttl = 0;
		this.ipCheck = 0;
		this.id = 0;
		this.frag_off = 0;
		this.tot_len = 0;
		this.saddr = 0;
		this.daddr = 0;
	}


	private char ihl, version, tos, ttl, protocol; 
	
	public  char getIhl(){ return ihl; }
	public  void setIhl(char ihl){ this.ihl = ihl; }

	public  char getVer(){ return version; }
	public  void setVer(char version){ this.version = version; }

	public  char getTos(){ return tos; }
	public  void setTos(char tos){ this.tos = tos; }

	public  char getTtl(){return ttl; }
	public  void setTtl(char ttl){this.ttl = ttl; }

	public  char getProtocol(){return protocol; }
	public  void setProtocol(char protocol){this.protocol = protocol; }
	
	private short tot_len, id, frag_off;
	public short getTotalLen() { return tot_len; }
	public void setTotalLen(short tot_len) { this.tot_len = tot_len; }
  
  	public  short getId(){ return id; }
	public  void setId(short id){ this.id = id; }
		
	public short getFragOff() { return frag_off; }
	public void setFragOff(short frag_off) { this.frag_off = frag_off; }
  
	private int ipCheck, saddr, daddr;
	public  int getIpCheck(){ return ipCheck; }
	public  void setIpCheck(int check){ this.ipCheck = check; } 
 
	public  int getSourceAddress(){ return saddr; }
	public  void setSourceAddress(int saddr){ this.saddr = saddr; }

	public  int getDestAddress(){ return daddr; }
	public  void setDestAddress(int daddr){ this.daddr = daddr; }

	
}
