/*
 * Copyright (C) 2012 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License
 */
package com.wly.net;

import android.app.Activity;
import android.os.Build;
import android.os.Bundle;
import android.support.v4.app.ListFragment;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.ListView;
 
import java.io.IOException;
import java.net.InetAddress; 
import java.net.Socket;
import java.util.*;
import android.os.*;
 
 
final class PortScanTask extends AsyncTask<InetAddress, Integer, String> {	
		@Override
		protected String doInBackground(InetAddress... hosts) {
				StringBuilder portsInfo = new StringBuilder();
				
				return portsInfo.toString();
				}
		protected void onProgressUpdate(Integer... progress) {}
		protected void onPreExecute() { }
		protected void onPostExecute(ArrayList<String> result) { }
	

}
public class PortListFragment extends ListFragment {
    OnPortSelectedListener mCallback;
    List<String> portList = new ArrayList<String>();
    ArrayAdapter<Integer> adapter = null;
    // The container Activity must implement this interface so the frag can deliver messages
    public interface OnPortSelectedListener {
        /** Called by HostFragment when a list item is selected */
        public void onPortSelected(int position);
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // We need to use a different list item layout for devices older than Honeycomb
        int layout = Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB ?
                android.R.layout.simple_list_item_activated_1 : android.R.layout.simple_list_item_1;

        // Create an array adapter for the list view
        adapter = new ArrayAdapter<Integer>(getActivity(), layout, PortScannerActivity.getPortList());
        setListAdapter(adapter);//, Ipsum.Headlines));
    }

    @Override
    public void onStart() {
        super.onStart();
        // When in two-pane layout, set the listview to highlight the selected list item
        // (We do this during onStart because at the point the listview is available.)
        if (getFragmentManager().findFragmentById(R.id.port_list_fragment) != null) {
            getListView().setChoiceMode(ListView.CHOICE_MODE_SINGLE);
       }
    }

    @Override
    public void onAttach(Activity activity) {
        super.onAttach(activity);

        // This makes sure that the container activity has implemented
        // the callback interface. If not, it throws an exception.
        try {
            mCallback = (OnPortSelectedListener) activity;
        } catch (ClassCastException e) {
            throw new ClassCastException(activity.toString()
                    + " must implement OnPortSelectedListener");
        }
    }

    @Override
    public void onListItemClick(ListView l, View v, int position, long id) {
        // Notify the parent activity of selected i;tem
        mCallback.onPortSelected(position);
        
        // Set the item as checked to be highlighted when in two-pane layout
        getListView().setItemChecked(position, true);
    }
  

  private void updateAdapter() {
    adapter.notifyDataSetInvalidated();
    adapter.notifyDataSetChanged();
  }
}
