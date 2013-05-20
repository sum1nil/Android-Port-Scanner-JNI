package com.wly.net;

public class TcpHeader
{

 public TcpHeader(short source, short dest, short doff, short res1, short cwr, short ece, short urg, short ack,
 		short psh, short rst, short syn, short fin, short window, short check, short urg_ptr, float seq, float ack_seq) {
				this.source = source;
				this.dest = dest;
				this.doff = doff;
				this.res1 = res1;
				this.cwr = cwr;
				this.ece = ece;
				this.urg = urg;
				this.ack = ack;
				this.psh = psh;
				this.rst = rst;
				this.syn = syn;
				this.fin = fin;
				this.window = window;
				this.check = check;
				this.urg_ptr = urg_ptr;
				this.seq = seq;
				this.ack_seq = ack_seq; 
 }
 
 public native boolean buildTcpHeader(TcpHeader tcpHeader);
 
 private short source, dest, doff, res1, cwr, ece, urg,ack, psh,rst,syn,fin,
 	window, check, urg_ptr;
		public  short getSource(){ return source; }
		public  void setSource(short source){ this.source = source; }

		public  short getDest(){ return dest; }
		public  void setDest(short dest){ this.dest = dest; }

		public  short getDoff(){ return doff; }
		public  void setDoff(short doff){ this.doff = doff; }

		public  short getRes1(){ return res1; }
		public  void setRes1(short res1){ this.res1 = res1; }

		public  short getCwr(){ return cwr; }
		public  void setCwr(short cwr){ this.cwr = cwr; }

		public  short getEce(){ return ece; }
		public  void setEce(short ece){ this.ece = ece; }

		public  short getUrg(){ return urg; }
		public  void setUrg(short urg){ this.urg = urg; }

		public  short getAck(){ return ack; }
		public  void setAck(short ack){ this.ack = ack; }

		public  short getPsh(){ return psh; }
		public  void setPsh(short psh){ this.psh = psh; }

		public  short getRst(){ return rst; }
		public  void setRst(short rst){ this.rst = rst; }

		public  short getSyn(){ return syn; }
		public  void setSyn(short syn){ this.syn = syn; } 

		public  short getFin(){ return fin; }
		public  void setFin(short fin){ this.fin = fin; }

		public  short getWindow(){ return window; }
		public  void setWindow(short window){ this.window = window; }

		public  short getCheck(){ return check; }
		public  void setCheck(short check){ this.check = check; }
		
		public  short getUrgPtr(){ return urg_ptr; }
		public  void setUrgPtr(short urg_ptr){ this.urg_ptr = urg_ptr; }
		
		private float seq, ack_seq;
		public  float getSeq(){ return seq; }
		public  void setSeq(float seq){ this.seq = seq; }

		public  float getAckSeq(){ return ack_seq; };
		public  void setAckSeq(float ack_seq){ this.ack_seq = ack_seq; };

}
 
