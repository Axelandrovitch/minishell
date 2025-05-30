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

static void	exit_with_error(char *arg, t_shell *shell)
{
	shell->last_exit_status = 2;
	ft_putstr_fd("bash: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(shell->last_exit_status);
}

static int	is_valid_nb(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
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

static int	is_long_overflow(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		if ((result > LONG_MAX / 10)
			|| (result == LONG_MAX / 10 && ((sign == 1 && (str[i] - '0') > 7)
					|| (sign == -1 && (str[i] - '0') > 8))))
			return (1);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (0);
}

int	builtin_exit(char **args, t_shell *shell)
{
	int		exit_code;
	long	long_exit_code;
	int		arg_count;

	printf("exit\n");
	if (!args[1])
		exit(0);
	if (!is_valid_nb(args[1]) || is_long_overflow(args[1]))
		exit_with_error(args[1], shell);
	arg_count = 0;
	while (args[arg_count])
		arg_count++;
	if (arg_count > 2)
	{
		shell->last_exit_status = 1;
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		return (1);
	}
	long_exit_code = ft_atol(args[1]);
	exit_code = long_exit_code % 256;
	if (exit_code < 0)
		exit_code += 256;
	exit_shell(shell, exit_code);
	return (0);
}

// PWD
int	builtin_pwd(char **args, t_shell *shell)
{
	char	*cwd;

	if (args[1])
	{
		shell->last_exit_status = 1;
		return (printf("pwd: too many arguments\n"), 1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		shell->last_exit_status = 1;
		return (perror("getcwd"), 1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
