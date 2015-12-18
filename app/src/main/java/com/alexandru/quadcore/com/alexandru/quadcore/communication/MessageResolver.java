package com.alexandru.quadcore.com.alexandru.quadcore.communication;

import android.app.Activity;
import android.widget.ProgressBar;
import android.widget.Toast;

import com.alexandru.quadcore.BluetoothActivity;
import com.alexandru.quadcore.R;

/**
 * Created by Alexandru on 12/18/2015.
 * Helper for taking appropriate action when a message is received
 * All messages from car to android client will respect QuadCore protocol.
 */
public class MessageResolver {


    // ================================ QuadCore protocol ================================

    // message structure
    public static final int MESSAGE_CODE_START = 0;
    public static final int MESSAGE_CODE_STOP = 2;

    public static final int MESSAGE_DATA_START = 2;

    // codes for messages
    public static final int TIME_ELAPSED = 0;
    public static final int BATTERY_STATUS = 1;
    public static final int CAR_SPEED = 2;
    public static final int DISTANCE = 3;
    public static final int WHEEL_LEFT_STATUS = 4;
    public static final int WHEEL_RIGHT_STATUS = 5;
    public static final int SENSOR_STATUS = 6;

    // ================================ END QuadCore protocol ================================


    private BluetoothActivity activity;

    public MessageResolver(Activity activity) {
        this.activity = (BluetoothActivity)activity;
    }

    public void resolve(String message)
    {
        int code;

        try {
            code = Integer.parseInt(message.substring(MESSAGE_CODE_START, MESSAGE_CODE_STOP));
        }
        catch (NumberFormatException ex)
        {
            Toast.makeText(activity, "Received invalid data", Toast.LENGTH_SHORT).show();
            return;
        }

        switch (code)
        {
            case TIME_ELAPSED:
                break;
            case BATTERY_STATUS:
                // get the battery value from the message
                int level = Integer.parseInt(message.substring(MESSAGE_DATA_START, MESSAGE_DATA_START + 2));
                // update UI
                updateUIBaterry(level);
                break;
            case CAR_SPEED:
                break;
            case DISTANCE:
                break;
        }

    }

    /**
     * Updates the progress bar representing the battery status
     * @param level the value of the battery status
     */
    private void updateUIBaterry(int level)
    {
        Toast.makeText(activity, "Battery: " + level, Toast.LENGTH_SHORT).show();
        ((ProgressBar)activity.findViewById(R.id.batteryStatus)).setProgress(level);
    }

    private void updateSensorStatus(int level)
    {

    }

}
