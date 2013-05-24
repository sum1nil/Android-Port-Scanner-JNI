package com.wly.net;

// The IP header's structure 
//384 bits
public class IpHeader
{
	public IpHeader(short ihl, short version,  short tos, short ttl, short check, short tot_len,
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

	
	private short ihl, version, tos, ttl, check;
	
	public  short getIhl(){ return ihl; }
	public  void setIhl(short ihl){ this.ihl = ihl; }

	public  short getVer(){ return version; }
	public  void setVer(short version){ this.version = version; }

	public  short getTos(){ return tos; }
	public  void setTos(short tos){ this.tos = tos; }

	public  short getTtl(){return ttl; }
	public  void setTtl(short ttl){this.ttl = ttl; }

	public  short getCheck(){ return check; }
	public  void setCheck(short check){ this.check = check; }
	
	private short tot_len, id, frag_off;


  	public  short getTotalLength(){ return tot_len; }
		public  void setTotalLength(short tot_len){ this.tot_len = tot_len; }
  
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
