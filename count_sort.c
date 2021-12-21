#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define ThreadNUM 1

void Count_sort(int a[], int n);
void print_array(int a[], int n);

struct Arguments {
    int *a;
    int n;
} args;

int main()
{
    int n = 4;
    int a[] = {3, 2, 1, 0};

    // call threads
    pthread_t id[ThreadNUM];
    unsigned int thread_ids[ThreadNUM];

    //args.a get sizeof(a)/threadNUM numbers

    for(int i = 0; i < ThreadNUM; i++) {
        //args.a = malloc(n*sizeof(int));
        //memcpy(args.a, a, sizeof(a));
        args.n = n;
    }

    Count_sort(args.a, args.n);

    
    print_array(a, n);

    return 0;
}

void Count_sort(int a[], int n) { 
    int i, j, count;
    int* temp = malloc(n*sizeof(int));
    for (i = 0; i < n; i++) { 
        count = 0;
        for (j = 0; j < n; j++) 
            if (a[j] < a[i]) count++; 
            else if (a[j] == a[i] && j < i)
            count++;
        temp[count] = a[i];
    }

    // mutex
    memcpy(a, temp, n*sizeof(int));
    free(temp); 
} /* Count sort */

void print_array(int a[], int n) {
    for(int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}
