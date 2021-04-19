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

int to2print(unsigned int x, char *buf, size_t len) 
{
    int ret = -1;
    int i, j, flg;
    int size;

    if (NULL == buf || len <= 0) {
        return  (ret);
    } else {
        *buf = 0;
    }
    if (0 == x) {
        snprintf(buf, len, "%s", "0b0");
        ret = 0;
        return (ret);
    } else {
        snprintf(buf, len, "%s", "0b");
    } 
    size = sizeof(x) * 8;
    flg = 0;
    for (i = 0, j = size - 1; i < size; i ++, j --) {
        if (strlen(buf) >= len - 1) {
            break;
        }
        if (0 == (x & (1 << j))) {
            if (0 != flg) {
                snprintf(buf + strlen(buf), len - strlen(buf), "%d", 0);
            }
        } else {
            snprintf(buf + strlen(buf), len - strlen(buf), "%d", 1);
            if (0 == flg) {
                flg = 1;
            }
        } 
    }

    ret = 0;
    return (ret);
}


int bits(unsigned int x)
{
    int n = 0;

    while (0 != x) {
        x &= x - 1;
        n ++;
    }
    return n;
}


static int bit_count(unsigned int i) {
    // Hacker's Delight, Figure 5-2
    i -= (i >> 1) & 0x55555555;
    i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
    i = ((i >> 4) + i) & 0x0F0F0F0F;
    i += i >> 8;
    i += i >> 16;
    return i & 0x0000003F;
}



int main()
{
    int n;
    int a = 3, b = 11;
    char buf[64];
    
    to2print(a, buf, sizeof(buf));
    n = bits(a);
    LOGW("n = [%d], a = [%d][%#x][%s]\n", n, a, a, buf);
    
    to2print(b, buf, sizeof(buf));
    n = bits(b);
    LOGW("n = [%d], b = [%d][%#x][%s]\n", n, b, b, buf);


    printf("\n====bit_count====\n");
    to2print(a, buf, sizeof(buf));
    n = bit_count(a);
    LOGW("n = [%d], a = [%d][%#x][%s]\n", n, a, a, buf);
    
    to2print(b, buf, sizeof(buf));
    n = bit_count(b);
    LOGW("n = [%d], b = [%d][%#x][%s]\n", n, b, b, buf);

    return 0;
}

