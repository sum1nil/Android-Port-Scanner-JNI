package com.wly.net;

public class TcpHeader
{

 public TcpHeader(char source, char dest, char doff, char res1, char cwr, char ece, char urg, char ack,
 		char psh, char rst, char syn, char fin, char window, char check, char urg_ptr, long seq, long ack_seq) {
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
 
 
 private int source, dest, doff, res1, cwr, ece, urg, ack, psh, rst, syn, fin,
 	window, check, urg_ptr;
		public  int getSource(){ return source; }
		public  void setSource(int source){ this.source = source; }

		public  int getDest(){ return dest; }
		public  void setDest(int dest){ this.dest = dest; }

		public  int getDoff(){ return doff; }
		public  void setDoff(int doff){ this.doff = doff; }

		public  int getRes1(){ return res1; }
		public  void setRes1(int res1){ this.res1 = res1; }

		public  int getCwr(){ return cwr; }
		public  void setCwr(int cwr){ this.cwr = cwr; }

		public  int getEce(){ return ece; }
		public  void setEce(int ece){ this.ece = ece; }

		public  int getUrg(){ return urg; }
		public  void setUrg(int urg){ this.urg = urg; }

		public  int getAck(){ return ack; }
		public  void setAck(int ack){ this.ack = ack; }

		public  int getPsh(){ return psh; }
		public  void setPsh(int psh){ this.psh = psh; }

		public  int getRst(){ return rst; }
		public  void setRst(int rst){ this.rst = rst; }

		public  int getSyn(){ return syn; }
		public  void setSyn(int syn){ this.syn = syn; } 

		public  int getFin(){ return fin; }
		public  void setFin(int fin){ this.fin = fin; }

		public  int getWindow(){ return window; }
		public  void setWindow(int window){ this.window = window; }

		public  int getCheck(){ return check; }
		public  void setCheck(int check){ this.check = check; }
		
		public  int getUrgPtr(){ return urg_ptr; }
		public  void setUrgPtr(int urg_ptr){ this.urg_ptr = urg_ptr; }
		
		private double seq, ack_seq;
		public  double getSeq(){ return seq; }
		public  void setSeq(double seq){ this.seq = seq; }

		public  double getAckSeq(){ return ack_seq; };
		public  void setAckSeq(double ack_seq){ this.ack_seq = ack_seq; };

}
 
