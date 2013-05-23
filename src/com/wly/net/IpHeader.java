package com.wly.net;

// The IP header's structure 

public class IpHeader
{
	public IpHeader(char ihl, char version,  char tos, char ttl, char check, short tot_len,
			short id, short frag_off, double saddr, double daddr) {
					this.ihl = ihl;
					this.version = version;
					this.tos = tos;
  				this.ttl = ttl;
          this.check = check;
					this.id = id;
					this.frag_off = frag_off;
					this.tot_len = tot_len;
					this.saddr = saddr;
					this.daddr = daddr;
	}

	
	private char ihl, version, tos, ttl, check;
	public  char getIhl(){ return ihl; }
	public  void setIhl(char ihl){ this.ihl = ihl; }

	public  char getVer(){ return version; }
	public  void setVer(char version){ this.version = version; }

	public  char getTos(){ return tos; }
	public  void setTos(char tos){ this.tos = tos; }

	public  char getTtl(){return ttl; }
	public  void setTtl(char ttl){this.ttl = ttl; }

	public  char getCheck(){ return check; }
	public  void setCheck(char check){ this.check = check; }
	
	private short tot_len, id, frag_off;


  	public  short getTotalLength(){ return tot_len; }
		public  void setTotalLength(short totu_len){ this.tot_len = tot_len; }
  
  	public  short getId(){ return id; }
		public  void setId(short id){ this.id = id; }
		
		public short getFragOff() { return frag_off; }
		public void setFragOff(short frag_off) { this.frag_off = frag_off; }
  
	private double saddr, daddr;
	public  double getSourceAddress(){ return saddr; }
	public  void setSourceAddress(double saddr){ this.saddr = saddr; }

	public  double getDestAddress(){ return daddr; }
	public  void setDestAddress(double daddr){ this.daddr = daddr; }

	
}
