# Parallel Count Sort C POSIX Threads
A parallel count sort program written using <pthreads.h> in c

### Original Count Sort Algorithm
```c
void Count_sort(int a[], int n) { 
    int i, j, count;
    int* temp = malloc(n∗sizeof(int));
    for (i = 0; i < n; i++) { 
        count = 0; 
        for (j = 0; j < n; j++) 
            if (a[j] < a[i]) count++; 
        else if (a[j] == a[i] && j < i)
            count++;
        temp[count] = a[i]; 
    } 
    memcpy(a, temp, n∗sizeof(int)); 
    free(temp); 
} /∗ Count sort ∗/ 
```
