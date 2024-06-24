/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:11:06 by amaligno          #+#    #+#             */
/*   Updated: 2024/06/24 18:09:49 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(char **args_array)
{
	int	count;

	count = 0;
	while (args_array[count])
		count++;
	if (count > 2)
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	return (0);
}

static void	go_home(t_env *envp)
{
	char	*home;

	home = get_env("HOME", envp);
	if (!home)
		ft_putstr_fd("minish: cd: HOME not set\n", STDERR_FILENO);
	else
	{
		put_env(ft_strdup("OLDPWD"), home, &envp);
		chdir(home);
		put_env(ft_strdup("PWD"), home, &envp);
	}
}

void	ft_cd(char **args_array, t_env *envp)
{
	char	*cwd;

	if (count_args(args_array))
		return ;
	if (!args_array[1])
	{
		go_home(envp);
		return ;
	}
	args_array++;
	if (chdir(*args_array) == 0)
	{
		cwd = getcwd(NULL, 0);
		put_env(ft_strdup("OLDPWD"), cwd, &envp);
		cwd = getcwd(NULL, 0);
		put_env(ft_strdup("PWD"), cwd, &envp);
		return ;
	}
	printf("minish: cd: %s: %s\n", *args_array, strerror(errno));
}
