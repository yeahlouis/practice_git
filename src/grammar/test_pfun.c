#include <errno.h>
#include <stdio.h>
#include <string.h>


#define LOGD(format, ...) fprintf(stdout, format, ##__VA_ARGS__)
#define LOGW(format, ...) fprintf(stdout, format, ##__VA_ARGS__)
#define LOGE(format, ...) fprintf(stderr, format, ##__VA_ARGS__)


struct test_fc
{
    int a;
    int b;
    int (*funp)(int, int);
};
typedef void (*f_ptr)();
//void (*f_ptr[10])();
typedef int (*func)(int, int);

int add (int a, int b)
{
    return a + b;
}

int sub (int a, int b)
{
    return a - b;
}


int main ()
{
    struct test_fc tfc;
    int a, b, sum;
    func c;
    int (*funp)(int, int);
    
    a = 3;
    b = 4;

    
    tfc.a = a;
    tfc.b = b;
    tfc.funp = add;

    LOGW("a = [%d], b = [%d]\n", a, b);
    c = add;
    sum = (*c)(a, b); //标准写法
    LOGW("sum = [%d]\n", sum);
    a = sum;

    LOGW("a = [%d], b = [%d]\n", a, b);
    sum = c(a, b); //简化写法
    LOGW("sum = [%d]\n", sum);

    a = sum;
    LOGW("before a = [%d], b = [%d]\n", a, b);

    funp = sub;
    a = (*funp)(a, b); 
    
    LOGW("after  a = [%d], b = [%d]\n", a, b);

    a = funp(a, b); 
    
    LOGW("second a = [%d], b = [%d]\n", a, b);

    int (*d)(int, int) = add; //也可以直接把声明和赋值写在一起
    a = d(a, b);
    LOGW("a = [%d], b = [%d]\n", a, b);

    LOGW("tfc.a = [%d], tfc.b = [%d], tfc_sum = [%d]\n", tfc.a, tfc.b, tfc.funp(tfc.a, tfc.b));

    return 0;
}

