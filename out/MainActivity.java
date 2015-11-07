package wanin.demo;

import com.wanin.IWnNativeService;
import com.wanin.NativeCmd;

import wanin.demo.R;

import android.app.Activity;
import android.app.ActionBar;
import android.app.Fragment;
import android.os.Bundle;
import android.os.IBinder;
import android.os.Parcel;
import android.os.RemoteException;
import android.os.ServiceManager;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.os.Build;

public class MainActivity extends Activity {

	private IWnNativeService mService;  
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        
        IBinder nativeServiceBinder;  
        Log.d("","getWnNativeServiceBinder");  
        nativeServiceBinder = (IBinder)ServiceManager.getService("WaninNativeService");  
        if(nativeServiceBinder != null)  
            mService = IWnNativeService.Stub.asInterface(nativeServiceBinder);  
        else  
            Log.d("","nativeServiceBinder is null.");  
        
        Button bt = (Button)findViewById(R.id.button1);
        bt.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				try {
					String cmd = "/system/bin/screencap /mnt/sdcard/new1.png";
					Log.d("", "RunCommand ret: " + mService.RunCommand(cmd));
					Log.d("", "SetProperty ret: " + mService.SetProperty("wanin.test", "wanin123"));
					Log.d("", "GetProperty ret: " + mService.GetProperty("init.svc.bootanim"));
				} catch (RemoteException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		});
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

    /**
     * A placeholder fragment containing a simple view.
     */
    public static class PlaceholderFragment extends Fragment {

        public PlaceholderFragment() {
        }

        @Override
        public View onCreateView(LayoutInflater inflater, ViewGroup container,
                Bundle savedInstanceState) {
            View rootView = inflater.inflate(R.layout.fragment_main, container, false);
            return rootView;
        }
    }

}
