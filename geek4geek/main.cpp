#include <stdio.h>
#include <conio.h>
using namespace std;

#define TEST_FUNC_NAME main_bst

#define DECLARE_TESTMAIN extern void TEST_FUNC_NAME()

void main() {
	DECLARE_TESTMAIN;

	main_bst();
	printf("\n\n\n\nExecution complete, press any key to exit.....");
	getch();
}
