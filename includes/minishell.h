/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:01:57 by amaligno          #+#    #+#             */
/*   Updated: 2024/03/26 20:46:01 by amaligno         ###   ########.fr       */
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
# include <libft.h>

# define CTRL_C SIGINT
# define CTRL_D EOF
# define CTRL_SLSH SIGQUIT

# define WHITESPACE "\n\t\r\v "
# define SYMBOLS "|<>"
# define QUOTES "\'\""

// Error strings
# define ERROR_QUOTES "Expected closing quote"

// These enums are for the cmd types
//LL and RR represent << and >> respectively
enum
{
	EXEC,
	REDIR,
	ERROR,
	PIPE,
	LL,
	RR
};

// Struct for different struct ptrs, intended to be used in
//exec and gettoken
typedef struct s_cmd
{
	int				type;
}	t_cmd;

typedef struct s_arg
{
	char			*s;
	struct s_arg	*next;
}	t_arg;

typedef struct s_error
{
	int				type;
	char			*error_msg;
	t_cmd			*head;
}	t_error;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_execmd
{
	int		type;
	t_arg	*args_list;
	char	**args_array;
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
}	t_redircmd;

typedef struct s_types
{
	t_cmd		*cmd;
	t_execcmd	*exec;
	t_pipecmd	*pipe;
	t_redircmd	*redir;
}	t_types;

typedef struct s_strptrs
{
	char	*s;
	char	*es;
}	t_strptrs;

//signals

void	init_signals(void);

//environement
//getter and setter functions for env

t_env	*env(char *string, t_env *envp);
t_env	*init_envp(char **envp);
char	*get_env(char *key, t_env *envp);
void	put_env(char *string, t_env **envp);

// Parsing

t_cmd	*parser(char *line, t_env *env);

//expansiom
char	*expansion(t_strptrs toks, t_execcmd *exec, t_env *env);

// Nodes
// These functions are constructors for the structs

t_cmd	*pipecmd(t_cmd	*left, t_cmd *right);
t_cmd	*redircmd(t_cmd *cmd, int fd, int mode, char *filename);
t_cmd	*execmd(void);
t_arg	*args(char *s, t_arg *next);
t_cmd	*error(t_cmd *head, char *message);

// Builtins

void	cd_cmd(char *line);

// Parsing utils

int		check_quotes(char *s, char *es);
int		check_quotes(char *s, char *es);
void	list_to_array(t_execcmd *exec);
int		gettoken(char **s, char *es, char **t, char **et);
int		checktoken(char **s, char *es, char *find);

// arg list funcs
void	arg_add_back(t_arg **head, t_arg *add);
void	arg_add_front(t_arg **head, t_arg *add);
void	args_free(t_arg *head);
int		arg_count(t_arg *head);
t_arg	*arg_last(t_arg *head);

//free.c
void	free_tree(t_cmd	*head);
void	free_2D(char **array);

// Debug utils 

void	print_env(t_env *env);
void	print_tree(t_cmd *head);

#endif
