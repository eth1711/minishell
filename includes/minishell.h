/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:01:57 by amaligno          #+#    #+#             */
/*   Updated: 2024/02/01 21:49:47 by amaligno         ###   ########.fr       */
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

//Parsing
t_cmd	parser(char *line, char **envp);
t_cmd	parseline(char **s, char *es);
t_cmd	parsepipe(char **s, char *es);

//Builtins
void	cd_cmd(char *line);

//Struct for different struct ptrs, intended to be used in
//exec and gettoken
typedef struct s_types
{
	t_execcmd	*exe;
	t_pipecmd	*pipe;
	t_redircmd	*redir;
}	t_types;

typedef struct s_cmd
{
	int				type;
}	t_cmd;

typedef struct s_execmd
{
	int		type;
	char	*argv;
	char	*eargv;
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
	char	*file;
	char	*efile;
}	t_redircmd;

#endif
