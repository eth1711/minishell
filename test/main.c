#include <stdio.h>
#include <string.h>

int	check_quotes(char *s, char *es)
{
	char	quote;

	while (s < es)
	{
		if (strchr("\'\"", *s))
		{
			quote = *s;
			s++;
			while (s < es && *s != quote)
			{
				printf("*s: %c\n", *s);
				s++;
			}
			if (*s != quote)
				return (0);
			s++;
		}
		else
			s++;
	}
	return (1);
}


int main()
{
	char *str = "he\"ll\"\'o\"";
	char *estr = str + strlen(str);
	printf("[%c]\n", *estr);
	if (!check_quotes(str, estr))
		printf("quotes not closed\n");
	else
		printf("quotes are closed\n");
}