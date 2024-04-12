#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <sys/stat.h>

char **ft_split(char const*, char);
char	*ft_strjoin(const char *s1, const char *s2);

void	exec(char *line, char **envp)
{
	int	pid;
	int ret;
	char **args;
	struct stat stats;

	args = ft_split(line, ' ');
	ret = stat(args[0], &stats);
	if (!ret && stats.st_mode & S_IXUSR && !(stats.st_mode & S_IFDIR))
		printf("has execute perms\n");
	else
		printf("no execute perms\n");
	printf("ret: %i\n", ret);
	pid = fork();
	if (!pid)
	{
		pid = fork();
		if (!pid)
		{
			args[0] = ft_strjoin("/bin/", args[0]);
			ret = execve(args[0], args, envp);
			exit(ret);
		}
		ret = wait(0);
		printf("ret: %i\n", ret);
	}
	wait(0);
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