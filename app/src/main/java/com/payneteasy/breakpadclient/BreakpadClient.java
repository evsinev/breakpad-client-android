package com.payneteasy.breakpadclient;

public class BreakpadClient {

    public native void init(String aMinidumpDirectory, String aLogcatFile);

    public native void performTestCrash();

    public native int getVersion();
}
