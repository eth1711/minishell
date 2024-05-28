/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:06:35 by amaligno          #+#    #+#             */
/*   Updated: 2024/05/28 16:15:18 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_exec(t_execcmd *exec)
{
	if (!exec)
	{
		printf("print_exec: exec node is null\n");
		return ;
	}
	printf("----------------EXEC----------------\n");
	printf("argv, list: ");
	for (t_arg *ptr = exec->args_list; ptr; ptr = ptr->next)
		printf("[%s]", ptr->s);
	printf("\nargv, array: ");
	for (char **ptr = exec->args_array; ptr && *ptr; ptr++)
		printf("[%s]", *ptr);
	printf("\n");
}

void	print_redir(t_redircmd	*redir)
{
	if (!redir)
	{
		printf("print_redir: redir node is null\n");
		return ;
	}
	printf("----------------REDIR----------------\n");
	printf("FD: %i\n", redir->fd);
	printf("mode: %i\n", redir->mode);
	printf("filename: [%s]\n", redir->filename);
	print_tree(redir->cmd);
}

void	print_pipe(t_pipecmd *pipe)
{
	if (!pipe)
	{
		printf("print_pipe: pipe node is null\n");
		return ;
	}
	printf("----------------PIPE----------------\n");
	printf("LEFT:\n");
	print_tree(pipe->left);
	printf("\nRIGHT:\n");
	print_tree(pipe->right);
}

void	print_tree(t_cmd *head)
{
	if (!head)
	{
		printf("print_tree: head node is null\n");
		return ;
	}	
	if (head->type == PIPE)
		print_pipe((t_pipecmd *)head);
	else if (head->type == EXEC)
		print_exec((t_execcmd *)head);
	else if (head->type == REDIR)
		print_redir((t_redircmd *)head);
	else if (head->type == ERROR)
		print_tree(((t_error *)head)->head);
}

void	print_env(t_env *env)
{
	while (env)
	{
		// printf("%s\n", env->string);
		printf("%s=%s\n", env->key, env->value);
		// printf("key: %s\n", env->key);
		// printf("value:%s\n", env->value);
		env = env->next;
	}
	printf("\n");
}
