/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahetru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:41:00 by ahetru            #+#    #+#             */
/*   Updated: 2025/04/29 13:41:01 by ahetru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_vector(char **vec)
{
	int	i;

	i = 0;
	while (vec[i])
	{
		printf("%s\n", vec[i]);
		i++;
	}
}

void	free_vector(char **vec)
{
	int	i;

	i = 0;
	while (vec[i])
	{
		free(vec[i]);
		i++;
	}
	free(vec);
}

static void	form_bin_path(char **envp_vec)
{
	char	*full_path;
	int		i;

	i = 0;
	while (envp_vec[i])
	{
		full_path = ft_strjoin(envp_vec[i], "/");
		if (!full_path)
		{
			free_vector(envp_vec);
			perror("Could not create executable path");
			exit(EXIT_FAILURE);
		}
		free(envp_vec[i]);
		envp_vec[i] = full_path;
		i++;
	}
}

char	**set_path_environment(char **envp)
{
	size_t	i;
	char	**envp_vec;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			envp_vec = ft_split(envp[i] + 5, ':');
			if (!envp_vec)
			{
				printf("Memory allocation failed\n");
				exit (1);
			}
			form_bin_path(envp_vec);
			return (envp_vec);
		}
		i++;
	}
	return (NULL);
}
