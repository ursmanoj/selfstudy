#include <stdio.h>
#include "foo.h"
 
int main(void)
{
    puts("This is a shared library test in C++...");
    foo();
    return 0;
}