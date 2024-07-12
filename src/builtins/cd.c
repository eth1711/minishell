/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:11:06 by amaligno          #+#    #+#             */
/*   Updated: 2024/06/27 16:02:47 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_error;

static void	go_home(t_env *envp)
{
	char	*home;

	home = get_env("HOME", envp);
	if (!home)
	{
		ft_putstr_fd("minish: cd: HOME not set\n", STDERR_FILENO);
		g_error = 1;
		return ;
	}
	put_env("OLDPWD", getcwd(NULL, 0), &envp);
	chdir(home);
	put_env("PWD", ft_strdup(home), &envp);
}

void	ft_cd(char **args_array, t_env *envp)
{
	char	*cwd;

	if (!args_array[1])
	{
		go_home(envp);
		return ;
	}
	if (args_array[2])
	{
		ft_putstr_fd("minsh: cd: too many arguments\n", STDERR_FILENO);
		g_error = 1;
		return ;
	}
	cwd = getcwd(NULL, 0);
	if (chdir(args_array[1]) == 0)
	{
		put_env("OLDPWD", cwd, &envp);
		cwd = getcwd(NULL, 0);
		put_env("PWD", cwd, &envp);
		g_error = errno;
		return ;
	}
	printf("minish: cd: %s: %s\n", args_array[1], strerror(errno));
	g_error = errno;
	free(cwd);
}
