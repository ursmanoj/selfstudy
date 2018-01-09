#include <stdio.h>
 
 
void foo(void)
{
    puts("Hello, I'm a shared library");
	int a = 10;
	
	int b =a +1;
	
	printf("b=%d\n", b);
}