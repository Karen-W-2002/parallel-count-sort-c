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

### Compilation & Execution

`
gcc -g -Wall -o count_sort count_sort.c -lpthread
`

`
./count_sort
`

### Questions
**Q1: If we try to parallelize the for i loop (the outer loop), which variables should be private and which should be shared?**

Depending on the algorithm (in this case):

Private: temp, count

Shared: a\[ \]

**Q2: If we parallelize the for i loop using the scoping you specified in the previous part, are there any loop-carried dependencies? Explain**

Loop-carried dependencies: dependence exists across iterations

i.e. if the loop is removed, the dependence no longer exists

**Q3: Can we parallelize the call to memcpy? Can we modify the code so that this part of the function will be parallelizable?"**

My current idea: Yes, different processes/threads write to different part of the array at the same time

HOWEVER, there might be an error

**Q4: How does the performance of your parallelization of Count sort compare to serial Count sort? How does it compare to serial qsort library function?**
