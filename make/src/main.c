#include <stdio.h>

#include "mylib.h"


int main(int argc, char* argv[])
{
#if defined(DEBUG) && (DEBUG != 0)
	printf("debug is enabled\n");
#else
	printf("debug is disabled\n");
#endif

    printf("max(%i, %i) = %i\n", A, B, max(A,B));

	return 0;
}