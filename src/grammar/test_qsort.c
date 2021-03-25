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


static int a_cmp(const void *v1, const void *v2) 
{
    return (*(int*)v1 - *(int*)v2);
}

int main()
{
    //int ret = EXIT_FAILURE;

    int i, ilen;
    int a[] = {1, 5, 3, 2, 6};
    int k = 3;
    int *e = NULL;


    ilen = sizeof(a) / sizeof(*a);
    LOGW("qsort before : ");
    for (i = 0; i < ilen; i ++) {
        if (i == ilen - 1) {
            LOGW("%d\n\n", *(a + i));
        } else {
            LOGW("%d, ", *(a + i));
        }
    }


    qsort(a, sizeof(a)/sizeof(*a), sizeof(*a), a_cmp);

    LOGW("qsort after  : ");
    for (i = 0; i < ilen; i ++) {
        if (i == ilen - 1) {
            LOGW("%d\n\n", *(a + i));
        } else {
            LOGW("%d, ", *(a + i));
        }
    }

    
    LOGW("bsearch...\n");
    //必须要排完序才能用bsearch
    e = bsearch(&k, a, sizeof(a)/sizeof(*a), sizeof(*a), a_cmp);
    LOGW("e = [%p], a = [%p]\n", e, a);
    if (e) {
        LOGW("value = [%d], index = [%zu]\n", *e, e - a); 
    }


    LOGW("\n\n");
    

    return EXIT_SUCCESS;
}
