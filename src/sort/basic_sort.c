#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int a[], int n)
{
    int i, j;
    int tmp;

    if (NULL == a || n < 2) {
        return;
    }

    for (i = 0; i < n - 1; i ++) {
        for (j = n - 1; j > i; j --) {
            if (a[j] < a[j - 1]) {
                tmp = a[j];
                a[j] = a[j - 1];
                a[j - 1] = tmp;
            } 
        } /* end of for j */
    } /* end of for i */
}

void select_sort (int a[], int n)
{
    int i, j, k;
    int tmp;

    if (NULL == a || n < 2) {
        return;
    }

    for (i = 0; i < n - 1; i ++) {
        k = i;
        for (j = i + 1; j < n; j ++) {
            if (a[j] < a[k]) {
		        k = j;
            } 
        } /* end of for j */
        if (k != i) {
            tmp = a[k];
            a[k] = a[i];
            a[i] = tmp;
        }
    } /* end of for i */
}

void insert_sort (int a[], int n)
{
    int i, j;
    int tmp;

    if (NULL == a || n < 2) {
        return;
    }

    for (i = 1; i < n; i ++) {
        tmp = a[i];
        for (j = i; j > 0 && a[j - 1] > tmp; j --) {
            a[j] = a[j - 1]; 
        }
        a[j] = tmp;
    } /* end of for i */ 
}


void shell_sort (int a[], int n)
{
    int i, j, gap;
    int tmp;

    if (NULL == a || n < 2) {
        return;
    }

    for (gap = n / 2; gap > 0; gap /= 2) {
        for (i = gap; i < n; i ++) {
            tmp = a[i];
            for (j = i; j > gap - 1 && a[j - gap] > tmp; j -= gap) {
                a[j] = a[j - gap]; 
            }
            a[j] = tmp;
        } /* end of for i */
    } /* end of for gap */
}

void quick_sort (int a[], int l, int r)
{
    int i, j;
    int pivot;
    if (l < 0 || l >= r) {
        return;
    }

    pivot = a[l];
    i = l;
    j = r;
    while (i < j) {
        while (i < j && a[j] >= pivot) {
            j--;
        }
        if (j > i) {
            a[i] = a[j];
        }
        while (i < j && a[i] <= pivot) {
            i++;
        }
        if (i < j) {
            a[j] = a[i];
        }
    } /* end of while (i < j) */
    a[i] = pivot;
    quick_sort(a, l, i-1);
    quick_sort(a, i+1, r);
}


void adjust_heap(int a[], int i, int n)
{
    int child;
    int tmp; 
    
    for (tmp = a[i]; (i * 2 + 1) < n; i = child) {
        child = i * 2 + 1;
        if ((child + 1) < n && a[child + 1] > a[child])
            child ++;
        if (tmp < a[child]) {
            a[i] = a[child];
        } else {
            break;
        }
    } /* end of for */

    a[i] = tmp;
}
void heap_sort(int a[], int n)
{
    int i;
    int tmp;
    
    for (i = n / 2; i >= 0; i--) { // build heap
        adjust_heap(a, i, n);
    }
    
    for (i = n - 1; i > 0; i--) {
        tmp = a[0];
        a[0] = a[i];
        a[i] = tmp;
        adjust_heap(a, 0, i);
    }
    
}


int main()
{
	int a[16], b[16];
	int i;
	int len;
	len = sizeof(a) / sizeof(a[0]);
	printf("\nlen = [%d]\n", len);
	for (i = 0; i < len; i ++) {
		b[i] = arc4random() & 0xFF;
	}

	printf("buble-befort:\t");
	for (i = 0; i < len; i ++) {
		a[i] = b[i];
		if (i == 0) {
			printf("%d", a[i]);
		} else {
			printf(",%d", a[i]);
		}
	}
	bubble_sort(a, len);
	printf("\nbuble-after:\t");
	for (i = 0; i < len; i ++) {
		if (i == 0) {
			printf("%d", a[i]);
		} else {
			printf(",%d", a[i]);
		}
	}

	printf("\n\nselect-befort:\t");
	for (i = 0; i < len; i ++) {
		a[i] = b[i];
		if (i == 0) {
			printf("%d", a[i]);
		} else {
			printf(",%d", a[i]);
		}
	}
	select_sort(a, len);
	printf("\nselect-after:\t");
	for (i = 0; i < len; i ++) {
		if (i == 0) {
			printf("%d", a[i]);
		} else {
			printf(",%d", a[i]);
		}
	}
	printf("\n\ninsert-befort:\t");
	for (i = 0; i < len; i ++) {
		a[i] = b[i];
		if (i == 0) {
			printf("%d", a[i]);
		} else {
			printf(",%d", a[i]);
		}
	}
	insert_sort(a, len);
	printf("\ninsert-after:\t");
	for (i = 0; i < len; i ++) {
		if (i == 0) {
			printf("%d", a[i]);
		} else {
			printf(",%d", a[i]);
		}
	}
	printf("\n\nshell-befort:\t");
	for (i = 0; i < len; i ++) {
		a[i] = b[i];
		if (i == 0) {
			printf("%d", a[i]);
		} else {
			printf(",%d", a[i]);
		}
	}
	shell_sort(a, len);
	printf("\nshell-after:\t");
	for (i = 0; i < len; i ++) {
		if (i == 0) {
			printf("%d", a[i]);
		} else {
			printf(",%d", a[i]);
		}
	}
	printf("\n\nquick-befort:\t");
	for (i = 0; i < len; i ++) {
		a[i] = b[i];
		if (i == 0) {
			printf("%d", a[i]);
		} else {
			printf(",%d", a[i]);
		}
	}
	quick_sort(a, 0, len - 1);
	printf("\nquick-after:\t");
	for (i = 0; i < len; i ++) {
		if (i == 0) {
			printf("%d", a[i]);
		} else {
			printf(",%d", a[i]);
		}
	}


	printf("\n\nheap-befort:\t");
	for (i = 0; i < len; i ++) {
		a[i] = b[i];
		if (i == 0) {
			printf("%d", a[i]);
		} else {
			printf(",%d", a[i]);
		}
	}
	heap_sort(a, len);
	printf("\nheap-after:\t");
	for (i = 0; i < len; i ++) {
		if (i == 0) {
			printf("%d", a[i]);
		} else {
			printf(",%d", a[i]);
		}
	}


    len -= 1;
	printf("\n\nheap-befort:\t");
	for (i = 0; i < len; i ++) {
		a[i] = b[i];
		if (i == 0) {
			printf("%d", a[i]);
		} else {
			printf(",%d", a[i]);
		}
	}
	heap_sort(a, len);
	printf("\nheap-after:\t");
	for (i = 0; i < len; i ++) {
		if (i == 0) {
			printf("%d", a[i]);
		} else {
			printf(",%d", a[i]);
		}
	}



    len -= 1;
	printf("\n\nheap-befort:\t");
	for (i = 0; i < len; i ++) {
		a[i] = b[i];
		if (i == 0) {
			printf("%d", a[i]);
		} else {
			printf(",%d", a[i]);
		}
	}
	heap_sort(a, len);
	printf("\nheap-after:\t");
	for (i = 0; i < len; i ++) {
		if (i == 0) {
			printf("%d", a[i]);
		} else {
			printf(",%d", a[i]);
		}
	}

	printf("\n");


	return 0;
}
