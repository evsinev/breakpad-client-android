#include <jni.h>
#include <string>
#include <android/log.h>
#include <unistd.h>

#include "client/linux/handler/exception_handler.h"
#include "client/linux/handler/minidump_descriptor.h"

/*
 * Triggered automatically after an attempt to write a minidump file to the breakpad folder.
 */
bool dumpCallback(const google_breakpad::MinidumpDescriptor &descriptor,
                  void *context,
                  bool succeeded) {

    const char *logcatFilename = (char *) context;

    // Allow system to log the native stack trace.
    __android_log_print(ANDROID_LOG_INFO, "srv.Breakpad",
                        "Wrote breakpad minidump at %s succeeded=%d\n", descriptor.path(),
                        succeeded);

    __android_log_print(ANDROID_LOG_INFO, "srv.Breakpad", "Writing logcat to %s ...\n",logcatFilename);

    if(fork() == 0) {
        int result = execl(
                "/system/bin/logcat"
                , "logcat"
                , "-d"
                , "-v", "threadtime"
                , "-f", logcatFilename
                , NULL
        );

        __android_log_print(ANDROID_LOG_INFO, "srv.Breakpad",
                            "Logcat result is =%d\n",
                            result);
    }
    return false;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_payneteasy_breakpadclient_BreakpadClient_init(JNIEnv *env, jobject thiz,
                                                       jstring a_minidump_directory,
                                                       jstring a_logcat_file) {

    const char *dumpPath        = (char *) env->GetStringUTFChars(a_minidump_directory, NULL);
    const char *logcatFilename  = (char *) env->GetStringUTFChars(a_logcat_file, NULL);

    __android_log_print(ANDROID_LOG_INFO, "srv.Breakpad", "Minidump directory is %s\n", dumpPath);
    __android_log_print(ANDROID_LOG_INFO, "srv.Breakpad", "Logcat   filename  is %s\n", logcatFilename);

    google_breakpad::MinidumpDescriptor descriptor(dumpPath);
    new google_breakpad::ExceptionHandler(descriptor, NULL, dumpCallback, (void*) logcatFilename, true, -1);

    env->ReleaseStringUTFChars(a_minidump_directory, dumpPath);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_payneteasy_breakpadclient_BreakpadClient_performTestCrash(JNIEnv *env, jobject thiz) {
    volatile int* a = (int*)(NULL);
    *a = 1;

}

extern "C"
JNIEXPORT jint JNICALL
Java_com_payneteasy_breakpadclient_BreakpadClient_getVersion(JNIEnv *env, jobject thiz) {
    return 2;
}