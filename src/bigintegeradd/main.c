//
//  main.c
//  BigIntegerAdd001
//
//  Created by louis sun on 2019/7/24.
//  Copyright © 2019 Trusfort. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 1024
#define DIGIT 64
struct node {
    int n;
    struct node *prev;
    struct node *next;
};
static void init_list_head(struct node *head)
{
    head->next = head;
    head->prev = head;
}
static void __list_add(struct node *new, struct node *prev, struct node *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}
static void list_add(struct node *new, struct node *head)
{
    __list_add(new, head, head->next);
}
static void list_add_tail(struct node *new, struct node *head)
{
    __list_add(new, head->prev, head);
}
static void __list_del(struct node *prev, struct node *next)
{
    next->prev = prev;
    prev->next = next;
}

static void list_del(struct node *entry)
{
    return __list_del(entry->prev, entry->next);
}

static void list_del_all(struct node *head)
{
    struct node *pos, *n;
    for (pos = head->next, n = pos->next; pos != head; pos = n, n = pos->next) {
        list_del(pos);
        free(pos);
    }
}

#define list_for_each(pos,head) \
    for(pos = (head)->next;pos != (head);pos = pos->next)

#define list_for_each_safe(pos,n,head) \
    for(pos = (head)->next,n = pos->next;pos != (head);pos = n,n = pos->next)


static int check_integer_format(char *sz_str, int *flg_sign) {
    int ret = -1;
    int i, j, k, ch;
    int index;
    int flg, flg_comma;
    size_t len;
    
    if (NULL == sz_str || (len = strlen(sz_str)) <= 0) {
        return (ret);
    }
    
    flg = 0;
    index = 0;
    flg_comma = 0;
    for (i = 0, j = 0, k = 0; i < len; i ++) {
        ch = sz_str[i];
        if (isspace(ch)) {
            continue;
        } else if (ch == '+' && 0 == flg) {
            flg = 1;
            continue;
        } else if (ch == '-' && 0 == flg) {
            if (NULL != flg_sign) {
                *flg_sign = 1;
            }
            flg = 1;
            continue;
        } else if (ch == ',') {
            k ++;
            if (k > DIGIT) {
                return (-2);
            }
            if (0 == flg_comma) {
                flg_comma = 1;
                if (index > 4) {
                    return (ret);
                }
            } else {
                if (index != 4) {
                    return (ret);
                }
            }
            
            index = 0;
            sz_str[j++] = sz_str[i];
        } else if (isdigit(ch)) {
            index ++;
            sz_str[j++] = sz_str[i];
            if (index > 4) {
                return (ret);
            }
        } else {
            return (ret);
        }
    } /* end of for */
    
    sz_str[j] = 0;
    if (0 != flg_comma && index != 4) {
        return (ret);
    }
    
    ret = 0;
    
    return (ret);
}


static int format_str(char *sz_str, int len) {
    int ret = -1;
    int i, j, k;
    int len_str;
    
    
    if (NULL == sz_str || (len_str = (int)strlen(sz_str)) <= 0 || len <= len_str) {
        return (ret);
    }
    
    sz_str[len] = 0;
    for (i = (int)(len - 1), j = len_str - 1, k = 1; i >= 0; i --, j --, k ++) {
        if (j >= 0) {
            sz_str[i] = sz_str[j];
        } else {
            if (0 == k % 5) {
                sz_str[i] = ',';
            } else {
                sz_str[i] = '0';
            }
        }

    } /* end of for */
    
    ret = 0;
    
    return (ret);
}


static void print_integer(struct node *head)
{
    char buf[128];
    int flg_first;
    struct node *p_node;
    if (NULL == head) {
        return;
    }
    
    if (head->n != 0) {
        printf("-");
    }
    flg_first = 0;
    *buf = 0;
    for(p_node = head->prev; p_node && p_node != head; p_node = p_node->prev) {
        if (0 == p_node->n) {
            if (0 == flg_first && p_node->prev != head) {
                continue;
            }
        } else {
            flg_first = 1;
        }
        if (p_node->prev == head) {
            snprintf(buf, sizeof(buf), "%0*d",  4, p_node->n);
        } else {
            snprintf(buf, sizeof(buf), "%0*d,", 4, p_node->n);
        }
        printf("%s", buf);
    } /* end of for */
    printf("\n");
    
}

static void print_list(struct node *head)
{
    char buf[128];
    int flg_first;
    struct node *p_node;
    if (NULL == head) {
        return;
    }
    
    if (head->n != 0) {
        printf("-");
    } else {
        printf(" ");
    }
    flg_first = 0;
    for(p_node = head->prev; p_node && p_node != head; p_node = p_node->prev) {
        if (0 == flg_first) {
            flg_first = 1;
            if (0 == p_node->n) {
                continue;
            }
        }
        if (p_node->prev == head) {
            snprintf(buf, sizeof(buf), "%0*d",  4, p_node->n);
        } else {
            snprintf(buf, sizeof(buf), "%0*d,", 4, p_node->n);
        }
        printf("%s", buf);
    } /* end of for */
    printf("\n");
    
}

static int comp_integer_list(struct node *head_a, struct node *head_b)
{
    struct node *p_node_a, *p_node_b;
    
    if (NULL == head_a && NULL == head_b) {
        return (0);
    } else if (NULL == head_a){
        return (-1);
    } else if (NULL == head_b){
        return (1);
    }
    
    
    for(p_node_a = head_a->prev, p_node_b = head_b->prev;
        p_node_a && p_node_a != head_a;
        p_node_a = p_node_a->prev, p_node_b = p_node_b->prev) {
        
        if (p_node_a->n == p_node_b->n) {
            continue;
        } else if (p_node_a->n > p_node_b->n) {
            return (1);
        } else  if (p_node_a->n < p_node_b->n) {
            return (-1);
        } else {
            break;
        }
    } /* end of for */
    
    return (0);
}

static int gen_integer_list(struct node *head, char *sz_str)
{
    int ret = -1;
    int flg_loop = 0;
    char buf[5];
    char *p_str, *p_tok;
    struct node *p_node;
    if (NULL == head || NULL == sz_str || strlen(sz_str) <= 0) {
        return (ret);
    }
    
    p_node = (struct node *)malloc(sizeof(struct node));
    if (NULL == p_node) {
        printf("malloc failed\n");
        return (ret);
    }
    memset(p_node, 0x00, sizeof(struct node));
    list_add(p_node, head);//多加一位，留进位用
    
    p_str = sz_str;
    flg_loop = 1;
    while (p_str && flg_loop) {
        if (',' == *p_str) {
            p_str += 1;
        }
        p_tok = strchr((const char *)p_str, ',');
        if (NULL == p_tok) {
            snprintf(buf, sizeof(buf), "%s", p_str);
        } else {
            snprintf(buf, p_tok - p_str + 1, "%s", p_str);
        }
        p_str = p_tok;
        //printf("buf = [%s]\n", buf);
        p_node = (struct node *)malloc(sizeof(struct node));
        if (NULL == p_node) {
            printf("malloc failed\n");
            return (ret);
        }
        memset(p_node, 0x00, sizeof(struct node));
        p_node->n = atoi(buf);
        list_add(p_node, head);
    } /* end of while */
    
    ret = 0;
    return (ret);
}



static int add_integer_list(struct node *head_a, struct node *head_b, struct node *head_res)
{
    int ret = -1;
    int carry = 0;
    int n;
    struct node *p_node_a, *p_node_b, *p_node_res;
    if (NULL == head_a || NULL == head_b || NULL == head_res) {
        return (ret);
    }
    
    carry = 0;
    
    for(p_node_a = head_a->next, p_node_b = head_b->next, p_node_res = head_res->next;
        p_node_a && p_node_a != head_a;
        p_node_a = p_node_a->next, p_node_b = p_node_b->next, p_node_res = p_node_res->next) {
        n = p_node_a->n + p_node_b->n + carry;
        carry = 0;
        p_node_res->n = n % 10000;
        if (n / 10000 > 0) {
            carry = 1;
        }
        
    }
    
    ret = 0;
    return (ret);
}


static int sub_integer_list(struct node *head_a, struct node *head_b, struct node *head_res)
{
    int ret = -1;
    int carry = 0;
    int n;
    struct node *p_node_a, *p_node_b, *p_node_res;
    if (NULL == head_a || NULL == head_b || NULL == head_res) {
        return (ret);
    }
    
    carry = 0;
    
    for(p_node_a = head_a->next, p_node_b = head_b->next, p_node_res = head_res->next;
        p_node_a && p_node_a != head_a;
        p_node_a = p_node_a->next, p_node_b = p_node_b->next, p_node_res = p_node_res->next) {

        if (p_node_a->n - carry < p_node_b->n) {
            n = 10000 + p_node_a->n - carry - p_node_b->n;
            carry = 1;
        } else {
            n = p_node_a->n - carry - p_node_b->n;
            carry = 0;
        }
        
        p_node_res->n = n;
    } /* end of for */
    
    ret = 0;
    return (ret);
}

static int opt_integer_list(int flg_opt, struct node *head_a, struct node *head_b, struct node *head_res)
{
    int ret = -1, rv;

    if (NULL == head_a || NULL == head_b || NULL == head_res) {
        return (ret);
    }
    if (0 == flg_opt) { // add
        if (0 == head_a->n && 0 == head_b->n) {
            add_integer_list(head_a, head_b, head_res);
        } else if (0 != head_a->n && 0 != head_b->n) {
            head_res->n = 1;
            add_integer_list(head_a, head_b, head_res);
        } else {
            rv = comp_integer_list(head_a, head_b);
            if (rv > 0) {
                head_res->n = head_a->n;
                sub_integer_list(head_a, head_b, head_res);
            } else if (rv < 0) {
                head_res->n = head_b->n;
                sub_integer_list(head_b, head_a, head_res);
            }
        }
    } else { //sub
        if (head_a->n != head_b->n) {
            head_res->n = head_a->n;
            add_integer_list(head_a, head_b, head_res);
        } else {
            rv = comp_integer_list(head_a, head_b);
            if (rv > 0) {
                head_res->n = head_a->n;
                sub_integer_list(head_a, head_b, head_res);
            } else if (rv < 0) {
                head_res->n = !head_b->n;
                sub_integer_list(head_b, head_a, head_res);
            }
        }
    }
    
    
    ret = 0;
    return (ret);
}



static int opt_big_integer(int flg_opt)
{
    int rv;
    struct node head_a, head_b, head_res;
    char buf_a[N];
    char buf_b[N];
    char buf_res[N];
    int flg;
    
    int len_a, len_b;
    

    snprintf(buf_res, sizeof(buf_res), "%d", 0);
    memset(&head_a  , 0x00, sizeof(struct node));
    memset(&head_b  , 0x00, sizeof(struct node));
    memset(&head_res, 0x00, sizeof(struct node));
    init_list_head(&head_a);
    init_list_head(&head_b);
    init_list_head(&head_res);
    flg = 0;
    
    while(flg < 2) {
        if (0 == flg) {
            printf("\nPlease input integer a:\n");
            fgets(buf_a, sizeof(buf_a), stdin);
            //snprintf(buf_a, sizeof(buf_a), "%s", "1234,5123,4512,3451,2345");
            //snprintf(buf_a, sizeof(buf_a), "%s", "1111,1111,1111,1111,1111");
            //snprintf(buf_a, sizeof(buf_a), "%s", "-1");
            rv = check_integer_format(buf_a, &head_a.n);
            if (-2 == rv) {
                printf("Integer a = [%s]\n", buf_a);
                printf("Input integer a format error(too long)!\n");
                continue;
            } else if (0 != rv) {
                printf("Integer a = [%s]\n", buf_a);
                printf("Input integer a format error!\n");
                continue;
            } else {
                printf("Integer a = [%d][%s]\n", head_a.n, buf_a);
            }
            flg = 1;
        } else {
            printf("\nPlease input integer b:\n");
            fgets(buf_b, sizeof(buf_b), stdin);
            //snprintf(buf_b, sizeof(buf_b), "%s", "-1111,1111,1111,1111,1111");
            //snprintf(buf_b, sizeof(buf_b), "%s", "2");
            rv = check_integer_format(buf_b, &head_b.n);
            if (-2 == rv) {
                printf("Integer b = [%s]\n", buf_b);
                printf("Input integer b format error(too long)!\n");
                continue;
            } else if (0 != rv) {
                printf("Integer b = [%s]\n", buf_b);
                printf("Input integer b format error!\n");
                continue;
            } else {
                printf("Integer b = [%d][%s]\n", head_b.n, buf_b);
            }
            flg = 2;
        }
    };
    
    printf("\n");
    printf("buf_a = [%d][%s]\n", head_a.n, buf_a);
    printf("buf_b = [%d][%s]\n", head_b.n, buf_b);
    if ((len_a = (int)strlen(buf_a)) <= 0) {
        printf("The programme failed(integer a format error)!\n");
    }
    if ((len_b = (int)strlen(buf_b)) <= 0) {
        printf("The programme failed(integer b format error)!\n");
    }
    
    format_str(buf_res, len_a > len_b ? len_a : len_b);
    if (len_a > len_b) {
        format_str(buf_b, len_a);
        //format_str(buf_res, len_a);
    } else if (len_a < len_b) {
        format_str(buf_a, len_b);
        //format_str(buf_res, len_b);
    }
    printf("format...\n");
    printf("buf_a = [%d][%s]\n", head_a.n, buf_a);
    printf("buf_b = [%d][%s]\n", head_b.n, buf_b);
    //printf("buf_res = [%d][%s]\n", 0,     buf_res);
    printf("\n");
    
    
    
    gen_integer_list(&head_a, buf_a);
    printf("Integer   a:");
    print_list(&head_a);
    
    
    gen_integer_list(&head_b, buf_b);
    printf("Integer   b:");
    print_list(&head_b);
    
    
    gen_integer_list(&head_res, buf_res);
    //printf("Integer res:");
    //print_list(&head_res);
    
    opt_integer_list(flg_opt, &head_a, &head_b, &head_res);
    printf("Integer res:");
    print_list(&head_res);
    //printf("Hello, World!\n");
    
    printf("\n====================result=================\n\n");
    //printf("Integer   a:");
    print_integer(&head_a);
    if (0 == flg_opt) {
        printf("+\n");
    } else {
        printf("-\n");
    }
    //printf("Integer   b:");
    print_integer(&head_b);
    printf("=\n");
    //printf("Integer res:");
    print_integer(&head_res);
    printf("\n===========================================\n");
    
    
    list_del_all(&head_a);
    list_del_all(&head_b);
    list_del_all(&head_res);
    
    return 0;
}

static void print_menu()
{
    printf("\n*******************-menu-*****************\n");
    printf("********Input '+': Big integer add********\n");
    printf("********Input '-': Big integer sub********\n");
    printf("********Input 'h': Print help info********\n");
    printf("********Input 'q': The programme exit*****\n");
    printf("******************************************\n");
}




int main(int argc, const char * argv[])
{
    
    int rv, ch, flg_opt, flg_loop;
    char buf[128];
    printf("===========================================\n");
    printf("====================start==================\n\n");
    print_menu();
    flg_loop = 1;
    while(flg_loop) {
        printf("\nPlease input command: ");
        *buf = 0;
        fgets(buf, sizeof(buf), stdin);
        ch = *buf;
        switch(ch) {
            case 'q':
            case 'Q':
                flg_loop = 0;
                break;
            case '+':
            case '-':
                if ('-' == ch) {
                    flg_opt = 1;
                } else {
                    flg_opt = 0;
                }
                rv = opt_big_integer(flg_opt);
                
            default:
                print_menu();
                break;
        }
    }
    

    printf("\n====================end====================\n");
    printf("===========================================\n");
    return 0;
}




