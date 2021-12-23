#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define ThreadNUM 2
#define N 8

void Count_sort(int a[], int n);
void sort_arr(void *arg);
void print_array(int a[], int n);

// global array
int a[N] = {3, 2, 1, 0, 3, 2, 1, 0};
int thread_count = 0, thread_count_ = 0;
int isDone = 0, isDone_ = 0;

// mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main()
{
    int i;

    // call threads
    pthread_t thread[ThreadNUM];
    unsigned int tid[ThreadNUM];

    // assign ID to each thread starting from 0
    for(i = 0; i < ThreadNUM; i++)
    {
        tid[i] = i;
        pthread_create(&thread[i], NULL, sort_arr, &tid[i]);
    }

    // Wait for threads
    for(i = 0; i < ThreadNUM; i++)
    {
        pthread_join(thread[i], NULL); 
    }

    // Print the new array
    print_array(a, N);

    return 0;
}

void Count_sort(int a[], int n)
{
    int i, j, count;
    int* temp = malloc(n*sizeof(int));
    for (i = 0; i < n; i++)
    { 
        count = 0;
        for (j = 0; j < n; j++) 
            if (a[j] < a[i]) count++; 
            else if (a[j] == a[i] && j < i) count++;
        temp[count] = a[i];
    }

    // mutex
    memcpy(a, temp, n*sizeof(int));
    free(temp); 
} /* Count sort */

void sort_arr(void *arg)
{
    int phase, id = *((int*)arg);

    int keys = N/ThreadNUM;
    int local_arr[keys];

    // ThreadNUM or N?
    for(phase = 0; phase < N; phase++)
    {
        // Barrier 1
        // Reset for barrier 2
        if(id == 0)
        {
            thread_count = 0;
            isDone = 1;
            isDone_ = 0;
        }

        while(1)
            if(isDone)
                break;

        pthread_mutex_lock(&mutex);
        thread_count++;
        pthread_mutex_unlock(&mutex);
        while(1)
            if(thread_count == ThreadNUM)
                break;

        if(phase%2 == 0) // Even phase
        {
            // Reading from global array
            memcpy(local_arr, a + id*keys, keys*sizeof(int));
            //print_array(local_arr, keys);

            // Sorting algorithm
            Count_sort(local_arr, keys);
            //printf("Phase %d Thread %d: ", phase, id);
            //print_array(local_arr, keys);
            
            // Writing to global array
            pthread_mutex_lock(&mutex);
            memcpy(a + id*keys, local_arr, keys*sizeof(int));
            pthread_mutex_unlock(&mutex);
        }
        else // Odd phase
        {
            // check if array is in range
            if(id*keys + 1 + keys < N)
            {
                // Reading from global array
                memcpy(local_arr, a + id*keys + 1, keys*sizeof(int));
                //print_array(local_arr, keys);

                // Sorting algorithm
                Count_sort(local_arr, keys);
                //printf("Phase %d Thread %d: ", phase, id);
                //print_array(local_arr, keys);

                // Writing to global array
                pthread_mutex_lock(&mutex);
                memcpy(a + id*keys + 1, local_arr, keys*sizeof(int));
                pthread_mutex_unlock(&mutex);
            }
        }

        // Barrier 2
        // Reset for barrier 1

        if(id == 0)
        {
            thread_count_ = 0;
            isDone_ = 1;
            isDone = 0; 
        }

        while(1)
            if(isDone_)
                break;

        pthread_mutex_lock(&mutex);
        thread_count_++;
        pthread_mutex_unlock(&mutex);
        while(1)
            if(thread_count_ == ThreadNUM)
                break;

        //print_array(a, N);
    }
}

void print_array(int a[], int n)
{
    int i;
    for(i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}
