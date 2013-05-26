package com.wly.net;


import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.inputmethod.EditorInfo;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.TextView.OnEditorActionListener;
import android.app.Activity;

public class PacketInfoActivity extends Activity implements OnEditorActionListener
{
	private final static String TAG = "IpInfoActivity";
	// IP header variables
	private char ihl, version, tos, ttl, protocol;
	private short tot_len, id, frag_off;
	private int ipCheck, saddr, daddr;
	// TCP header variables
	private short source, dest, doff, res1, cwr, ece, urg, ack, psh, rst, syn, fin,
 	window, tcpCheck, urg_ptr;
	private long seq, ack_seq;
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		Log.i(TAG, "Entered onCreate() of IpInfoActivity");
		super.onCreate(savedInstanceState);
		setContentView(R.layout.ip_info);
		
	}
	@Override
	protected void onPause() {
		super.onPause();
	  savePacketData();
	}
	private void savePacketData() {
		Bundle packetBundle = new Bundle();
		  // IP datagram
		  packetBundle.putChar("ihl", ihl);
		  packetBundle.putChar("version", version);
		  packetBundle.putChar("tos", tos);
		  packetBundle.putChar("ttl", ttl);
		  packetBundle.putChar("protocol", protocol);
		  packetBundle.putShort("tot_len", tot_len);
		  packetBundle.putShort("id", id);
		  packetBundle.putShort("frag_off", frag_off);
		  packetBundle.putInt("ipCheck", ipCheck);
		  packetBundle.putInt("saddr", saddr);
		  packetBundle.putInt("daddr", daddr);
		  // TCP datagram
		  packetBundle.putShort("source", source);
		  packetBundle.putShort("dest", dest);
		  packetBundle.putShort("doff", doff);
		  packetBundle.putShort("res1", res1);
		  packetBundle.putShort("cwr", cwr);
		  packetBundle.putShort("ece", ece);
		  packetBundle.putShort("urg", urg);
		  packetBundle.putShort("ack", ack);
		  packetBundle.putShort("psh", psh);
		  packetBundle.putShort("rst", rst);
		  packetBundle.putShort("syn", syn);
		  packetBundle.putShort("fin", fin);
		  packetBundle.putShort("window", window);
		  packetBundle.putShort("tcpCheck", tcpCheck);
		  packetBundle.putShort("urg_ptr", urg_ptr);
		  packetBundle.putLong("seq", seq);
		  packetBundle.putLong("ack_seq", ack_seq);
		  PortScannerActivity.createPacketDatagram(packetBundle);

	}
	
	@Override
	public void onSaveInstanceState(Bundle savedPacketInstanceState) {
	  super.onSaveInstanceState(savedPacketInstanceState);
	  // Save UI state changes to the savedInstanceState.
	  // This bundle will be passed to onCreate if the process is
	  // killed and restarted.
	  savePacketData();

	  // etc.
	}

	@Override
	public boolean onEditorAction(TextView v, int actionId, KeyEvent event) 	{
		// TODO Auto-generated method stub
		boolean result = true;
		StringBuilder value = new StringBuilder();
		if (actionId == EditorInfo.IME_ACTION_NEXT || actionId == EditorInfo.IME_ACTION_DONE) {
		// the user is done typing in one EditText box.
			switch (v.getId()) {
			case R.id.iph_ihl:
				Toast.makeText(this, "In iph_ihl case statement.", Toast.LENGTH_SHORT).show();
				value.append(((EditText)v).getText().toString());
				ihl = (char) Integer.parseInt(value.toString());
				value.delete(0, value.capacity());
			break;
			case R.id.iph_version:
				Toast.makeText(this, "In iph_version case statement.", Toast.LENGTH_SHORT).show();
				value.append(((EditText)v).getText().toString());
				version = (char) Integer.parseInt(value.toString());
				value.delete(0, value.capacity());			
			break;
			case R.id.iph_tos:
				Toast.makeText(this, "In iph_tos case statement.", Toast.LENGTH_SHORT).show();
				value.append(((EditText)v).getText().toString());
				tos = (char) Integer.parseInt(value.toString());
				value.delete(0, value.capacity());
			break;
			case R.id.iph_ttl:
				Toast.makeText(this, "In iph_ttl case statement.", Toast.LENGTH_SHORT).show();
				value.append(((EditText)v).getText().toString());
				ttl = (char) Integer.parseInt(value.toString());
				value.delete(0, value.capacity());
			break;
			case R.id.iph_protocol:
				Toast.makeText(this, "In iph_protocol case statement.", Toast.LENGTH_SHORT).show();
				value.append(((EditText)v).getText().toString());
				protocol = (char) Integer.parseInt(value.toString());
				value.delete(0, value.capacity());
			break;
			case R.id.iph_tot_len:
				Toast.makeText(this, "In iph_tot_len case statement.", Toast.LENGTH_SHORT).show();
				value.append(((EditText)v).getText().toString());
				tot_len = (short) Integer.parseInt(value.toString());
				value.delete(0, value.capacity());
			break;
			case R.id.iph_check:
				Toast.makeText(this, "In iph_check case statement.", Toast.LENGTH_SHORT).show();
				value.append(((EditText)v).getText().toString());
				ipCheck = Integer.parseInt(value.toString());
				value.delete(0, value.capacity());
			break;
			case R.id.iph_saddr:
				Toast.makeText(this, "In iph_saddr case statement.", Toast.LENGTH_SHORT).show();
				value.append(((EditText)v).getText().toString());
				saddr = (char) Integer.parseInt(value.toString());
				value.delete(0, value.capacity());
			break;
			case R.id.iph_daddr:
				Toast.makeText(this, "In iph_daddr case statement.", Toast.LENGTH_SHORT).show();
				value.append(((EditText)v).getText().toString());
				daddr = Integer.parseInt(value.toString());
				value.delete(0, value.capacity());
			break;
			default:
				result = false;
				break;
			
			}
		
		}
		savePacketData();
		return result;
	}
}

