/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:32:27 by dcampas-          #+#    #+#             */
/*   Updated: 2025/04/29 17:55:06 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_valid_nb(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+'  || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	exit_with_error(char *arg)
{
	ft_putstr_fd("bash: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(255);
}

int	builtin_exit(char **args)
{
	int		exit_code;
	long	long_exit_code;
	int		arg_count;

	printf("exit\n");
	if (!args[1])
		exit(0);
	if (!is_valid_nb(args[1]))
		exit_with_error(args[1]);
	arg_count = 0;
	while (args[arg_count])
		arg_count++;
	if (arg_count > 2)
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		return (1);
	}
	long_exit_code = ft_atol(args[1]);
	exit_code = long_exit_code % 256;
	if (exit_code < 0)
		exit_code += 256;
	exit(exit_code);
}

int	builtin_pwd(char **args)
{
	char	*cwd; 

	if (args[1])
		return (printf("pwd: too many arguments\n"), 1);
	cwd = getcwd(NULL, 0); //Get the current working directory
	if (!cwd)
		return (perror("getcwd"),1);

	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
