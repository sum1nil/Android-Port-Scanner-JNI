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

    static {
        System.loadLibrary("icom-jni");
    } 
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
		public native int getSourceIp(); // { return sourceIp; }
		public native int getDestIp(); // { return destIp; }
		public native int getDoff(); // { return doff; }
		public native int getres1(); // { return res1; }
		public native int getCwr(); // { return cwr; }
		public native int getEce(); // { return ece; }
		public native int getUrg(); // { return urg; }
		public native int getAck(); // { return ack; }
		public native int getPst(); // { return pst; }
		public native int getRst(); // { return rst; }
		public native int getSyn(); // { return syn; }
		public native int getFin(); // { return fin; }
		
		private long seq, ack_seq;
		public native long getSeq(); // { return seq; }
		public native long getAckSeq(); // { return ack_seq; };
		
}
 
