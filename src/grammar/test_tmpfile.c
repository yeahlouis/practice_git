#include <errno.h>
#include <stdio.h>
#include <string.h>


#define LOGD(format, ...) fprintf(stdout, format, ##__VA_ARGS__)
#define LOGW(format, ...) fprintf(stdout, format, ##__VA_ARGS__)
#define LOGE(format, ...) fprintf(stderr, format, ##__VA_ARGS__)

typedef char aaa;
//typedef int  aaa;

int main ()
{

        int err = -1;
        int i;
        char buffer[256];
        FILE *fp;

        printf("sizeof(char) = [%zu], sizeof(int) = [%zu]\n", sizeof(char), sizeof(int));
        printf("sizeof(aaa) = [%zu]\n", sizeof(aaa));
        fp = tmpfile();
        if (NULL == fp) {
            err = errno ? errno : -1;    
            LOGE("tmpfile faile! errno = [%d], error = [%s]\n", err, strerror(err));            
        }


        snprintf(buffer, sizeof(buffer), "%s", "abc\n");
        //fputs (buffer,fp);
        fwrite(buffer, 1, strlen(buffer), fp);
        snprintf(buffer, sizeof(buffer), "%s", "aaa\n");
        //fputs (buffer,fp);
        fwrite(buffer, 1, strlen(buffer), fp);
        snprintf(buffer, sizeof(buffer), "%s", "ccc\n");
        //fputs (buffer,fp);
        fwrite(buffer, 1, strlen(buffer), fp);
        rewind(fp);

        while (!feof(fp)) {
            if (fgets (buffer,256,fp) == NULL) break;
            fputs (buffer, stdout);
        }

        fclose (fp);




        return 0;
}
