#include <errno.h>
#include <stdio.h>
#include <string.h>


#define LOGD(format, ...) fprintf(stdout, format, ##__VA_ARGS__)
#define LOGW(format, ...) fprintf(stdout, format, ##__VA_ARGS__)
#define LOGE(format, ...) fprintf(stderr, format, ##__VA_ARGS__)


struct node
{
    int value; /* data stored in the node */
    struct node *next; /* pointer to the next node */
};

void print_list(struct node *head) 
{
    struct node *p = NULL;

    for (p = head; p; p = p->next) {
        if (NULL == p->next) {
            LOGD("[%d]", p->value);
        } else {
            LOGD("[%d]-->", p->value);
        }
    }
}

int main ()
{
    struct node x, y;


    int *p, *q;
    int a;
    int b;
    long c;
    
    a = 3;
    p = &a;

    b = (int)p;
    c = (long)p; 

    q = (int *)c;
    LOGW("a = [%d][%p]\n", a, &a);
    LOGW("p = [%d][%p]\n", *p, p);
    LOGW("b = [%#x]\n", b);
    LOGW("c = [%d][%#lx]\n", *(int *)c, c);

    LOGW("q = [%d][%p]\n", *q, q);

    q = (int *)(uintptr_t)a;
    //q = (int *)(long)a;
    LOGW("q = [%p]\n", q);

    b = (int)q;
    LOGW("b = [%d]\n", b);


    LOGW("\n=======struct============\n");
    x.value = 10;
    y.value = 13;
    x.next = &y;
    y.next = NULL;
    print_list(&x);    
    LOGW("\n");
    LOGW("x = [%p], next = [%p]\n", &x, x.next); 
    LOGW("y = [%p], next = [%p]\n", &y, y.next); 
    LOGW("x.next = [%p], y.next = [%p]\n", &x.next, &y.next); 
    
    //LOGE("x.next - x = [%d]\n", &x.next - &x);
    c = (long) &x;
    LOGW("c = [%#lx][%d]\n", c, *(int *)c);
    
    c += 8;
    LOGW("c = [%#lx][%p]\n", c, *(struct node **)c);
    

    LOGW("\n=======struct============\n");

    return 0;
}

