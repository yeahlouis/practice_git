#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <strings.h>

#include <sys/time.h>

#if 1
#if defined(__ANDROID__) || defined(ANDROID) 
#include <android/log.h>
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,  ##__VA_ARGS__)
#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN, LOG_TAG,  ##__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,  ##__VA_ARGS__)
#else
#define LOGD(format, ...) fprintf(stdout, format, ##__VA_ARGS__)
#define LOGW(format, ...) fprintf(stdout, format, ##__VA_ARGS__)
#define LOGE(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#endif
#else
#define LOGD(format, ...) do {} while (0)
#define LOGW(format, ...) do {} while (0)
#define LOGE(format, ...) do {} while (0)
#endif


int main()
{
    //int ret = EXIT_FAILURE;
    int i;
    struct timeval tv;
    char buf[128];



    LOGW("\narc4random u = ");
    unsigned int u = arc4random();
    i = LOGW("%#X\n", u);
    LOGW("count = [%d]\n", i);

    LOGW("\n");
    //memset(buf, 0x00, sizeof(buf));
    bzero(buf, sizeof(buf)); //strings.h
    arc4random_buf(buf, 32);
    for (i = 0; i < 32; i ++) {
        LOGW("%02X", (buf[i] & 0xFF));
    }

    LOGW("\n\n");
    for (i = 0; i < 10; i ++) {
        u = arc4random_uniform(10);
        LOGW("u = [%u]\n", u);
    }


    LOGW("\n\n");
    //gen_uuid.c
    gettimeofday(&tv, NULL);
    srand((getpid() << 16) ^ getuid() ^ tv.tv_sec ^ tv.tv_usec);
    LOGW("tv.tv_sec \t= [%ld]\n", tv.tv_sec);
    LOGW("time(NULL)\t= [%ld]\n", time(NULL));
    LOGW("\n");


    return EXIT_SUCCESS;
}
