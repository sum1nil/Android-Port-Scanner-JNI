package com.wly.net;


import android.os.Bundle;
import android.util.Log;
import android.app.Activity;

public class PacketInfoActivity extends Activity
{
	private final static String TAG = "IpInfoActivity";
	// IP header variables
	private char ihl, version, tos, ttl, protocol;
	private short tot_len, id, frag_off;
	private int saddr, daddr;
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		Log.i(TAG, "Entered onCreate() of IpInfoActivity");
		super.onCreate(savedInstanceState);
		setContentView(R.layout.ip_info);
		
	}

}
