#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/history.h>
#include <readline/readline.h>

char **ft_split(char const*, char);

void	exec(char *line, char **envp)
{
	int	pid;
	int ret;
	char **args;

	args = ft_split(line, ' ');
	pid = fork();
	if (!pid)
	{
		pid = fork();
		if (!pid)
		{
			ret = execve(args[0], args, envp);
			exit(ret);
		}
		ret = wait(0);
		printf("ret: %i\n", ret);
	}
}

int main(int c, char **argv, char **envp)
{
	char *line;

	line = readline("test$");
	while (line)
	{
		exec(line, envp);
		free(line);
		line = readline("test$");
	}
}