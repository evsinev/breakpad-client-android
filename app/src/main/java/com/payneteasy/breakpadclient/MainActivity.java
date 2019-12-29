package com.payneteasy.breakpadclient;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.io.File;

public class MainActivity extends Activity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("breakpad-client");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final BreakpadClient breakpadClient = new BreakpadClient();
        breakpadClient.init(getFilesDir().getAbsolutePath(), new File(getFilesDir(), System.currentTimeMillis()+".txt").getAbsolutePath());

        TextView textView = findViewById(R.id.text);
        textView.setText("Version is " + breakpadClient.getVersion());
        
        Button button = findViewById(R.id.button);
        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                breakpadClient.performTestCrash();
            }
        });
    }

}
