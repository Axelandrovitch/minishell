/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:44:30 by dcampas-          #+#    #+#             */
/*   Updated: 2025/05/29 17:54:38 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_invalid_export(char *arg)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	is_valid_identifier_export(const char *str)
{
	int	i;

	if (!str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	should_print_var(char *env_var)
{
	if (!env_var)
		return (0);
	if (env_var[0] == '_')
		return (0);
	return (1);
}

int	print_filtered_env(char **sorted_env)
{
	int	i;

	i = 0;
	while (sorted_env[i])
	{
		if (should_print_var(sorted_env[i]))
			printf("declare -x %s\n", sorted_env[i]);
		i++;
	}
	return (0);
}
