package com.wly.net;
/*

struct tcphdr {
 __u16 source;
 __u16 dest;
 __u32 seq;
 __u32 ack_seq;
 __u16 doff:4,
 res1:4,
 cwr:1,
 ece:1,
 urg:1,]
 ack:1,
 psh:1,
 rst:1,
 syn:1,
 fin:1;
 */
public class TcpHeader
{

 public TcpHeader(int sourceIp, int destIp, int doff, int res1, int cwr, int ece, int urg, int ack,
 		int pst, int rst,int syn, int fin, long seq, long ack_seq) {
				this.sourceIp = sourceIp;
				this.destIp = destIp;
				this.doff =doff;
				this.res1 = res1;
				this.cwr = cwr;
				this.ece = ece;
				this.urg = urg;
				this.ack = ack;
				this.pst = pst;
				this.rst = rst;
				this.syn = syn;
				this.fin = fin;
				this.seq = seq;
				this.ack_seq = ack_seq; 
 }
 
 public native boolean buildTcpHeader(TcpHeader tcpHeader);
 
 private int sourceIp, destIp, doff, res1, cwr, ece, urg,ack, pst,rst,syn,fin;
		public  int getSourceIp(){ return sourceIp; }
		public  void setSourceIp(int sourceIp){ this.sourceIp = sourceIp; }

		public  int getDestIp(){ return destIp; }
		public  void setDestIp(int destIp){ this.destIp = destIp; }

		public  int getDoff(){ return doff; }
		public  void setDoff(int doff){ this.doff = doff; }

		public  int getres1(){ return res1; }
		public  void setres1(int res1){ this.res1 = res1; }

		public  int getCwr(){ return cwr; }
		public  void setCwr(int cwr){ this.cwr = cwr; }

		public  int getEce(){ return ece; }
		public  void setEce(int ece){ this.ece = ece; }

		public  int getUrg(){ return urg; }
		public  void setUrg(int urg){ this.urg = urg; }

		public  int getAck(){ return ack; }
		public  void setAck(int ack){ this.ack = ack; }

		public  int getPst(){ return pst; }
		public  void setPst(int pst){ this.pst = pst; }

		public  int getRst(){ return rst; }
		public  void setRst(int rst){ this.rst = rst; }

		public  int getSyn(){ return syn; }
		public  void setSyn(int syn){ this.syn = syn; }

		public  int getFin(){ return fin; }
		public  void setFin(int fin){ this.fin = fin; }

		private long seq, ack_seq;
		public  long getSeq(){ return seq; }
		public  void setSeq(long seq){ this.seq = seq; }

		public  long getAckSeq(){ return ack_seq; };
		public  void setAckSeq(long ack_seq){ this.ack_seq = ack_seq; };

}
 
