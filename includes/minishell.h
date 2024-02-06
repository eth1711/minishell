/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:01:57 by amaligno          #+#    #+#             */
/*   Updated: 2024/02/05 22:04:59 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include "libft.h"

# define WHITESPACE "\n\t\r\v "
# define SYMBOLS "|<>\'\""

//These enums are for the cmd types
//LL and RR represent << and >> respectively
enum
{
	EXEC,
	REDIR,
	PIPE,
	LL,
	RR
};

//Struct for different struct ptrs, intended to be used in
//exec and gettoken
typedef struct s_cmd
{
	int				type;
}	t_cmd;

typedef struct s_execmd
{
	int		type;
	char	**argv;
	char	**eargv;
}	t_execcmd;

typedef struct s_pipecmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipecmd;

typedef struct s_redircmd
{
	int		type;
	t_cmd	*cmd;
	int		fd;
	int		mode;
	char	*filename;
	char	*efilename;
}	t_redircmd;

typedef struct s_types
{
	t_cmd		*cmd;
	t_execcmd	*exec;
	t_pipecmd	*pipe;
	t_redircmd	*redir;
}	t_types;

typedef struct s_token
{
	char	*t;
	char	*et;
}	t_token;

//Parsing

t_cmd	*parser(char *line);
t_cmd	*parseline(char **s, char *es);
t_cmd	*parsepipe(char **s, char *es);

//Nodes
//These functions are constructors for the structs

t_cmd	*pipecmd(t_cmd	*left, t_cmd *right);
t_cmd	*redircmd(t_cmd *cmd, int fd, int mode, t_token filename);
t_cmd	*execmd(int argc);

//Builtins

void	cd_cmd(char *line);

//Parsing utils

int		argcount(char *s, char *es);
int		gettoken(char **s, char *es, char **t, char **et);
int		checktoken(char **s, char *es, char *find);

//Debug utils 

void	print_tree(t_cmd *head);

#endif
