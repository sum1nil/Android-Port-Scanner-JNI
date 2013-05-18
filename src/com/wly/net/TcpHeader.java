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
 
 private int sourceIp, destIp, doff, res1, cwr, ece, urg,ack, pst,rst,syn,fin;
		public int getSourceIp() { return sourceIp; }
		public int getDestIp() { return destIp; }
		public int getDoff() { return doff; }
		public int getres1() { return res1; }
		public int getCwr() { return cwr; }
		public int getEce() { return ece; }
		public int getUrg() { return urg; }
		public int getAck() { return ack; }
		public int getPst() { return pst; }
		public int getRst() { return rst; }
		public int getSyn() { return sourceIp; }
		public int getFin() { return sourceIp; }
		
		private long seq, ack_seq;
		public long getSeq() { return seq; }
		public long getAckSeq() { return ack_seq; };
		
}
 
