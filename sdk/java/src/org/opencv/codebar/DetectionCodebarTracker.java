package org.opencv.codebar;

public class DetectionCodebarTracker {

    static {
        System.loadLibrary("detection_based_tracker");
    }

    public static native void filterImageCodeBar(long im, long dst);
}
