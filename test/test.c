#include "stdio.h"

int main()
{
	int	*array[3];
	printf("array len: %lu\n", sizeof(array)/sizeof(int *));
}