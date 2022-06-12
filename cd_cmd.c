/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaizza <aaizza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 19:24:18 by aaizza            #+#    #+#             */
/*   Updated: 2022/06/12 21:32:47 by aaizza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_find_path(char **env, char *path)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], path, ft_strlen_till_c(env[i], '=')))
			return (ft_substr(env[i],
					ft_strlen_till_c(env[i], '=') + 1, ft_strlen(env[i])));
		i++;
	}
	return (NULL);
}

void	cd2(char **args)
{
	if (ft_strncmp(args[1], ".", ft_strlen(args[1])) == 0)
	{
		chdir((const char *)".");
		g_data.exit_code = 0;
	}
	else if (ft_strncmp(args[1], "..", ft_strlen(args[1])) == 0)
	{
		chdir("..");
		g_data.exit_code = 0;
	}
	else
	{
		if (chdir(args[1]) == 0)
			g_data.exit_code = 0;
		else if (chdir(args[1]) == -1)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			perror(args[1]);
			g_data.exit_code = 1;
		}
	}
}

void	cd_cmd(char **args)
{
	char	*home;

	home = ft_find_path(g_data.env, "HOME");
	if (!ft_strncmp(args[1], "~", 1) || !args[1])
	{
		if (!home)
		{
			ft_putendl_fd("Minishell: cd: HOME not set", 2);
			g_data.exit_code = 1;
		}
		chdir(home);
	}
	else if (args[1])
		cd2(args);
}
