package com.alexandru.quadcore;

import android.app.Activity;
import android.graphics.Color;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;

import com.alexandru.quadcore.com.alexandru.quadcore.controls.Speedometer;

public class MainActivity extends Activity {

    private Speedometer speedometer;
    private double prg = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Customize SpeedometerGauge
        speedometer = (Speedometer)findViewById(R.id.speedometer);

        // Add label converter
        speedometer.setLabelConverter(new Speedometer.LabelConverter() {
            @Override
            public String getLabelFor(double progress, double maxProgress) {
                return String.valueOf((int) Math.round(progress));
            }
        });

        // configure value range and ticks
        speedometer.setMaxSpeed(100);
        speedometer.setMajorTickStep(10);
        speedometer.setMinorTicks(1);

        // Configure value range colors
        speedometer.addColoredRange(30, 140, Color.GREEN);
        speedometer.addColoredRange(140, 180, Color.YELLOW);
        speedometer.addColoredRange(180, 400, Color.RED);

        findViewById(R.id.button).setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                accelerate(null);
                return true;
            }
        });

    }


    public void accelerate(View view)
    {
        prg += 1;
        if (prg > 100)
            prg = 0;
        speedometer.setSpeedAccelerating(prg, 200, 0, 1.9f);
    }

}
