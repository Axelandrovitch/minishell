/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:32:06 by dcampas-          #+#    #+#             */
/*   Updated: 2025/06/04 13:52:12 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_getenv(t_shell *shell, const char *var)
{
	int		i;
	int		var_len;
	char	*ret;

	i = 0;
	var_len = ft_strlen(var);
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], var, var_len) == 0
			&& shell->env[i][var_len] == '=')
		{
			ret = ft_strdup(shell->env[i] + var_len + 1);
			if (!ret)
				exit_shell(shell, 1);
			return (ret);
		}
		i++;
	}
	return (NULL);
}

int	add_or_update_env(char ***env, char *key, char *value)
{
	int	pos;

	if (!key || !env || !*env)
		return (1);
	pos = find_env_var(*env, key);
	if (pos >= 0)
		return (update_env_var(*env, key, value));
	else
		return (add_env_var(env, key, value));
}

void	sort_env_copy(char **env)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				temp = env[i];
				env[i] = env[j];
				env[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	free_vector(char **vec)
{
	int	i;

	i = 0;
	if (!vec)
		return ;
	while (vec[i])
	{
		free(vec[i]);
		i++;
	}
	free(vec);
}
