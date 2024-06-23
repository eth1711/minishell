/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:11:06 by amaligno          #+#    #+#             */
/*   Updated: 2024/06/24 00:13:25 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(char **args_array)
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

void	ft_cd(char **args_array, t_env *envp)
{
	char	*cwd;

	if (count_args(args_array))
		return ;
	if (!args_array[1])
	{
		cwd = get_env("HOME", envp);
		if (!cwd)
			ft_putstr_fd("minish: cd: HOME not set\n", STDERR_FILENO);
		else
			chdir(cwd);
		return ;
	}
	args_array++;
	cwd = getcwd(NULL, 0);
	if (chdir(*args_array) == 0)
	{
		put_env(ft_strdup("OLDPWD"), cwd, &envp);
		cwd = getcwd(NULL, 0);
		put_env(ft_strdup("PWD"), cwd, &envp);
		return ;
	}
	free(cwd);
	printf("minish: cd: %s: %s\n", *args_array, strerror(errno));
}
