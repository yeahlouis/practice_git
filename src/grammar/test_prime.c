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

/* square root of a long < 65536 */
long i_sqrt (long x)
{
  long    x1, x2;

  x2 = 16;
  do {
    x1 = x2;
    x2 = x1 - ((x1 * x1) - x) / (2 * x1);
  } while (x1 != x2);

  if (x1 * x1 > x) {
    --x1;
  }

  return x1;
}

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
    int a[] = {2, 3, 5, 15, 11, 49, 79};
    int i;


    for (i = 0; i < (sizeof(a)/sizeof(*a)); i ++) {
        if (is_prime(a[i])) {
            printf("[%d] is prime\n", a[i]);
        } else {
            printf("[%d] is not prime\n", a[i]);
        }
    }

    i = i_sqrt(49);
    printf("sqrt(49) = %d\n", i);

    i = i_sqrt(80);
    printf("sqrt(80) = %d\n", i);

    i = i_sqrt(512);
    printf("sqrt(512) = %d\n", i);

    return 0;
}

