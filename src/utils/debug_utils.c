/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:06:35 by amaligno          #+#    #+#             */
/*   Updated: 2024/02/05 20:34:04 by amaligno         ###   ########.fr       */
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
	printf("argv: ");
	for (int i = 0; exec->argv[i]; i++)
	{
		while (exec->argv[i] < exec->eargv[i])
			printf("%c", *(exec->argv[i]++));
		printf(" ");
	}
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
	printf("filename: ");
	while (*redir->filename && redir->filename < redir->efilename)
		printf("%c", *(redir->filename++));
	printf("\n");
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
}