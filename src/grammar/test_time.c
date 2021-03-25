#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

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


static long long get_time_stamp()
{
   struct timeval tv;
   long long microsec;
   gettimeofday(&tv, NULL);
   microsec = (tv.tv_sec * 1000000) + (tv.tv_usec);
   return microsec;

}

int main()
{
    int ret = EXIT_FAILURE;
    clock_t t0;
    struct timeval tv;
    struct timeval tv1, tv2;
    struct tm *lt;
    struct tm loc;
    char buf[128];


    t0 = clock();
    gettimeofday(&tv1, NULL);

    LOGD("\nsleep...\n");
    sleep(1);


    LOGD("\n");
    long long ll = get_time_stamp();
    LOGD("get_time_stamp microsec = [%lld]\n", ll);

    gettimeofday(&tv, NULL);
    srand((getpid() << 16) ^ getuid() ^ tv.tv_sec ^ tv.tv_usec);

    LOGD("tv.tv_sec \t= [%ld]\n", tv.tv_sec);
    LOGD("time(NULL)\t= [%ld]\n", time(NULL)); //time_t就是个long型的数字

    
    LOGD("\n");
    LOGD("ctime(tv.tv_sec) = [%s]\n", ctime(&tv.tv_sec)); //返回的字符串是个静态变量,不需要内存的释放,不支持多线程
    memset(buf, 0x00, sizeof(buf));
    ctime_r(&tv.tv_sec, buf);
    LOGD("ctime_r(tv.tv_sec, buf) = [%s]\n", buf); 
     

    LOGD("\n");
    lt = localtime(&tv.tv_sec); //返回是静态变量,不需要内存的释放,不支持多线程
    LOGD("lt->tm_year = [%d][%d]\n", lt->tm_year, lt->tm_year + 1900);
    LOGD("asctime(lt) = [%s]\n", asctime(lt)); //返回的字符串是个静态变量,不需要内存的释放,不支持多线程
    
    memset(buf, 0x00, sizeof(buf));
    LOGD("asctime_r(lt, buf) = [%s]\n", asctime_r(lt, buf)); 

    memset(buf, 0x00, sizeof(buf));
    localtime_r(&tv.tv_sec, &loc);
    LOGD("asctime_r(loc, buf) = [%s]\n", asctime_r(&loc, buf)); 

    LOGD("\n");
    strftime(buf, sizeof(buf), "%Y", &loc); 
    LOGD("year = [%s]\n", buf);

    strftime(buf, sizeof(buf), "%F", &loc); 
    LOGD("[%s]\n", buf);

    strftime(buf, sizeof(buf), "%c", &loc); 
    LOGD("[%s]\n", buf);



    LOGD("\n");
    gettimeofday(&tv2, NULL);
    long usec = (tv2.tv_sec - tv1.tv_sec) * 1000000 + tv2.tv_usec - tv1.tv_usec;
    LOGD("gettimeofday-usec = [%ldus]\n", usec); //实际时间
    LOGD("clock---------total: %ldus\n", (clock() - t0)); //CPU占用时间
    LOGD("clock---------total: %lfms\n", (double)(clock() - t0) * 1000 / CLOCKS_PER_SEC);
    LOGD("clock---------total: %lf s\n", (double)(clock() - t0) / CLOCKS_PER_SEC);
    
    LOGD("\n");


    ret = EXIT_SUCCESS;
    return (ret);
}

