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

### Description

Above count sort algorithm mixed with odd even sort for parallelisation

### Functions
- **void Count_sort(int a[], int n)**

The local part of the parallelised count sort algorithm

- **void sort_arr(void \*arg)**

The global part of the parallelised count sort algorithm

- **void print_array(int a[], int n)**

prints array a

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

Why is count and temp local? 

because I localised the whole function of count sort, with each of the threads calling it

**Q2: If we parallelize the for i loop using the scoping you specified in the previous part, are there any loop-carried dependencies? Explain**

Yes there are loop dependencies in the for i loop. Inside the for i loop, the j loop exists, and if the i loop is removed from existence, then the dependence wouldn't exist anymore. That's how we can tell that there is loop-carried depedency.

**Q3: Can we parallelize the call to memcpy? Can we modify the code so that this part of the function will be parallelizable?"**

Yes memcpy can be parallelised but only inside the local function! The way I wrote it, inside count sort it can be parallelised because the function is local. However, it can not be parallelised if copying TO a GLOBAL array.

Line 62: memcpy(a, temp, n\*sizeof(int)); is parallelised because the function is local

Line 109: memcpy(a + id\*keys, local_arr, keys\*sizeof(int)); is not parallelised because a is a GLOBAL variable and I made it thread safe with mutexes

**Q5: How does the performance of your parallelization of Count sort compare to serial Count sort? How does it compare to serial qsort library function?**

Serial Count Sort: O(n^2)

My Parallelised Count Sort: O(n)

QSort Library Func: O(nlogn)
