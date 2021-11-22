# ft_malloc  
## Shared C library of dynamic memory allocation mechanisms 

This project is my own implementation of the C standard utility functions *malloc*, *free* and *realloc*, for dynamically allocating, freeing, and reallocating memory. 
The objectives of this project were to:
*  use the *mmap* and *munmap* system calls to create and delete mapping in the virtual address space of the calling process.
*  efficiently use virtual memory for memory allocations, including defragmentation of freed memory blocks.
*  create a shared (dynamic) library (as opposed to a static library).
*  manage the use of *malloc*, *free*, and *realloc* in a multi-threaded program (i.e. making the functions "thread safe").

### Compiling library  
The project contains a Makefile for the following:  
```make all``` to compile the shared library and created a symbolic link to it. The library is named *libft_malloc_$HOSTTYPE.so*, and the symbolic link *libft_malloc.so*. If $HOSTTYPE does not exist as an environmental variable, the Makefile will define it as follows: ```HOSTTYPE := $(shell uname -m)_$(shell uname -s)```   
```make clean``` to remove the object files  
```make fclean``` to run ```make clean``` as well as remove the shared library and symbolic link  
```make re``` to run ```make fclean``` and ```make all```  

### Usage (on Linux)  
* ```export LD_LIBRARY_PATH=<path to libft_malloc.so>```  
* Add ```#include "<path to inludes folder>/ft_malloc.h"``` to the .c file
* Compile your C program: ```gcc -L$LD_LIBRARY_PATH -o <yourexecutable> <yourfile.c> -lft_malloc```
