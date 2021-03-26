#include <stdio.h>
#include <string.h>

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

int is_prime(int x)
{
    int divisor;

    if (x <= 1) {
        return 0;
    }

    for (divisor = 2; divisor * divisor <= x; divisor ++) {
        if (x % divisor == 0) {
            return 0;
        }
    }

    return 1;
}

int main()
{
    int a[] = {15, 11, 49};
    int i;


    for (i = 0; i < (sizeof(a)/sizeof(*a)); i ++) {
        if (is_prime(a[i])) {
            printf("[%d] is prime\n", a[i]);
        } else {
            printf("[%d] is not prime\n", a[i]);
        }
    }

    return 0;
}

