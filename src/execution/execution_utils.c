/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:38:33 by ahetru            #+#    #+#             */
/*   Updated: 2025/06/05 12:14:36 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_builtin(const char *command)
{
	if (!ft_strcmp(command, "exit"))
		return (1);
	if (!ft_strcmp(command, "echo"))
		return (1);
	if (!ft_strcmp(command, "cd"))
		return (1);
	if (!ft_strcmp(command, "pwd"))
		return (1);
	if (!ft_strcmp(command, "export"))
		return (1);
	if (!ft_strcmp(command, "unset"))
		return (1);
	if (!ft_strcmp(command, "env"))
		return (1);
	return (0);
}

bool	is_single_builtin(t_command_block *cmd)
{
	if (cmd == NULL)
		return (false);
	if (cmd->next != NULL)
		return (false);
	if (!cmd->argv || !cmd->argv[0])
		return (false);
	if (!is_builtin(cmd->argv[0]))
		return (false);
	return (true);
}

int	prepare_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

void	print_command_not_found(const char *command)
{
	char	*message;
	char	*message_endl;
	int		len;

	message = ft_strjoin("minishell: command not found: ", command);
	message_endl = ft_strjoin(message, "\n");
	len = ft_strlen(message_endl);
	write(STDERR_FILENO, message_endl, len);
	free(message);
	free(message_endl);
}
