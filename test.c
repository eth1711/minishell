#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>

int main(void)
{
	printf(readline(">"));
	while (1)
		printf(readline("\n>"));
}