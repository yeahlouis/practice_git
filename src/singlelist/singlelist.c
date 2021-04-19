#include <stdio.h>
#include <stdlib.h>


#define LOGD(format, ...) fprintf(stdout, format, ##__VA_ARGS__)
#define LOGW(format, ...) fprintf(stdout, format, ##__VA_ARGS__)
#define LOGE(format, ...) fprintf(stderr, format, ##__VA_ARGS__)

struct node
{
    int value; /* data stored in the node */
    struct node *next; /* pointer to the next node */
};


static int add_list(struct node **head, int value)
{
    int ret = -1;

    struct node *p = NULL;
    
    if (NULL == head) {
        return (ret);
    }

    p = (struct node *)malloc(sizeof(struct node));
    if (NULL == p) {
        LOGE("malloc failed!\n");
        return (ret);
    }
    
    p->value = value;
    p->next = *head;
    *head = p;

    ret = 0;
    return (ret);
}



static int reverse_list(struct node **head) 
{
    int ret = -1;

    struct node *prev = NULL, *temp = NULL;
    struct node *cur = NULL;
    
    if (NULL == head) {
        return (ret);
    }
    
    cur = *head;

    while (NULL != cur) {
        temp = cur->next;
        cur->next = prev;
        prev = cur;
        cur = temp;
    }

    *head = prev;
    
    ret = 0;
    return (ret);
}

static int delete_list(struct node **head, int value) 
{
    int ret = -1;

    struct node *cur, *prev;
    
    if (NULL == head) {
        return (ret);
    }
    
    for (cur = *head, prev = NULL;
         cur != NULL && cur->value != value; prev = cur, cur = cur->next);

    if (cur == NULL) {
        ret = 0;
        return (ret);
    } else if (prev == NULL) {
        *head = cur->next;
    } else {
        prev->next = cur->next;
    }

    free(cur);
    
    ret = 0;
    return (ret);
}

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

int main()
{

    //int ret = -1, rc;
    struct node *head = NULL;


    add_list(&head, 1);        
    add_list(&head, 3);        
    add_list(&head, 2);        
    add_list(&head, 5);        
    add_list(&head, 4);        

	LOGD("\n--------list:\t");
    print_list(head);

    reverse_list(&head);
	LOGD("\nreverse-list:\t");
    print_list(head);

    delete_list(&head, 2);
	LOGD("\ndelete--list:\t");
    print_list(head);
	LOGD("\n");


	return 0;
}


