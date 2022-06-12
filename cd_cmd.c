/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaizza <aaizza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 19:24:18 by aaizza            #+#    #+#             */
/*   Updated: 2022/06/12 20:07:05 by aaizza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	look_for_env_index(char **env, char *start)
// {
// 	int	i;

// 	i = 0;
// 	while (env[i])
// 	{
// 		if (ft_strncmp(start, env[i], ft_strlen(start)) == 0)
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }

// void	cd_error(void)
// {
// 	perror("minishell");
// 	g_data.exit_code = 1;
// 	return ;
// }

// void	cd_cmd(char **args)
// {
// 	char	buff[1000];
// 	int		old_pwd_index;
// 	int		pwd_index;
// 	char	*pwd;

// 	pwd = args[1];
// 	if (!pwd)
// 		pwd = ft_strdup(g_data.env[look_for_env_index
// 				(g_data.env, "HOME=")] + 5);
// 	old_pwd_index = look_for_env_index(g_data.env, "OLDPWD=");
// 	free_if_exists(g_data.env[old_pwd_index]);
// 	g_data.env[old_pwd_index] = \
// 	ft_str_join(ft_strdup("OLDPWD="), getcwd(buff, 1000));
// 	if (chdir(pwd) == -1)
// 		return (cd_error());
// 	pwd_index = look_for_env_index(g_data.env, "PWD=");
// 	free_if_exists(g_data.env[pwd_index]);
// 	g_data.env[pwd_index] = \
// 	ft_str_join(ft_strdup("PWD="), getcwd(buff, 1000));
// 	if (!args[1])
// 		free(pwd);
// 	g_data.exit_code = 0;
// }

char	*ft_find_path(char **env, char *path)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], path, ft_strlen_till_c(env[i], '=')))
			return(ft_substr(env[i], ft_strlen_till_c(env[i], '='), ft_strlen(env[i])));
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
		return ;
	}
	else if (ft_strncmp(args[1], "..", ft_strlen(args[1])) == 0)
	{
		chdir("..");
		g_data.exit_code = 0;
		return ;
	}
	else
	{
		chdir(args[1]);
		g_data.exit_code = 0;
		return ;
	}
}

void	cd_cmd(char **args)
{
	char	*home;

	home = ft_find_path(g_data.env, "HOME");
	if (!args[1])
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
