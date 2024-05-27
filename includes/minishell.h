/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:01:57 by amaligno          #+#    #+#             */
/*   Updated: 2024/05/27 19:18:18 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>
# include <sys/stat.h>
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
# define ERR_QUOTES "minish: Expected closing quote\n"
# define ERR_SYTX_RDIR "minish: syntax error near redir\n"
# define ERR_SYTX_PIPE "minish: syntax error near pipe\n"

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

//Basic cmd struct, to be typcasted into the correct node
typedef struct s_cmd
{
	int				type;
}	t_cmd;

//Struct for linked list of args of a cmd
typedef struct s_arg
{
	char			*s;
	struct s_arg	*next;
}	t_arg;

typedef struct s_error
{
	int				type;
	char			*err_msg;
	t_cmd			*head;
}	t_error;

//environement varibale struct
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

//Execution node, contains both list and array of arguments of command
typedef struct s_execcmd
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

//Node with pointers of each node type
typedef struct s_types
{
	t_cmd		*cmd;
	t_execcmd	*exec;
	t_pipecmd	*pipe;
	t_redircmd	*redir;
	t_error		*error;
}	t_types;

typedef struct s_strptrs
{
	char	*s;
	char	*es;
}	t_strptrs;

typedef struct s_pid
{
	pid_t			pid;
	struct s_pid	*next;
}	t_pid;

//exec

void	exec_redir(t_redircmd *redir, t_env *envp);
void	exec_execcmd(t_execcmd *exec, t_env *envp);
void	exec_pipe(t_pipecmd *pipecmd, t_env *envp);
void	exec(t_cmd *head, t_env *envp);
void	start_exec(t_cmd *head, t_env *envp);

//signals

void	init_signals(void);
void	handle_sigint(int sigint, siginfo_t *info, void *data);

//environement

//setter function for env
void	put_env(char *string, t_env **envp);
//getter function for env
char	*get_env(char *key, t_env *envp);

char	**env_to_array(t_env *envp);
t_env	*env_to_list(char **envp);

// Parsing

t_cmd	*parser(char *line, t_env *env);

//expansion

char	*ft_safejoin(char *s1, char *s2);
char	*expansion(t_strptrs toks, t_execcmd *exec, t_env *env);

// Nodes
// These functions are constructors for the structs

t_cmd	*pipecmd(t_cmd	*left, t_cmd *right);
t_cmd	*redircmd(t_cmd *cmd, int fd, int mode, char *filename);
t_cmd	*execcmd(void);
t_arg	*args(char *s, t_arg *next);
t_cmd	*error(t_cmd *head, char *err_msg, int error_number);

// Builtins

void	ft_cd(char **args_array);
void	ft_echo(char **args_array);
void	ft_export(char **args_array, t_env *envp);
void	ft_unset(char **args_array, t_env *envp);
void	ft_exit(char **args_array, t_env *envp);
void	ft_pwd(char **args_array, t_env *envp);

// Parsing utils

int		check_quotes(char *s, char *es);
int		check_quotes(char *s, char *es);
void	list_to_array(t_execcmd *exec);
int		gettoken(char **s, char *es, char **t, char **et);
int		checktoken(char **s, char *es, char *find);

//pid_funcs
t_pid	*new_pid(pid_t pid, t_pid *next);
void	add_pid(t_pid **head, t_pid *new);


// arg list funcs

void	arg_add_back(t_arg **head, t_arg *add);
void	arg_add_front(t_arg **head, t_arg *add);
void	args_free(t_arg *head);
int		arg_count(t_arg *head);
t_arg	*arg_last(t_arg *head);

//free.c
void	free_tree(t_cmd	*head);
void	free_2d(char **array);

// Debug utils 

void	print_env(t_env *env);
void	print_tree(t_cmd *head);

//Exec Utils

int		is_builtin(char **args, t_env *envp);

#endif
