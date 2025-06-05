/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:09:30 by dcampas-          #+#    #+#             */
/*   Updated: 2025/06/05 13:19:44 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_error(const char **args)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd("no such file or directory: ", 2);
	ft_putendl_fd(args[1], 2);
}

int	update_pwd_vars(t_shell *shell, char *old_directory)
{
	char	*new_pwd;
	int		ret;

	if (old_directory)
	{
		ret = update_env_var(shell->env, "OLDPWD", old_directory);
		if (ret != 0)
			return (1);
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (perror("getcwd"), 1);
	ret = update_env_var(shell->env, "PWD", new_pwd);
	free(new_pwd);
	return (ret);
}

int	go_to_path(t_shell *shell, const char *target)
{
	char	*env_path;
	int		ret;

	env_path = ft_getenv(shell, (char *)target);
	if (!env_path)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(target, 2);
		ft_putendl_fd(" not set", 2);
		return (1);
	}
	ret = chdir(env_path);
	free(env_path);
	if (ret == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	handle_no_args(t_shell *shell, char *current_dir)
{
	char	*home;

	home = ft_getenv(shell, "HOME");
	if (!home)
	{
		free(current_dir);
		shell->last_exit_status = 1;
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	if (chdir(home) == -1)
	{
		free(home);
		free(current_dir);
		shell->last_exit_status = 1;
		perror("cd");
		return (1);
	}
	free(home);
	return (0);
}
