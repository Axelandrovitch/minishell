/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahetru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:10:26 by ahetru            #+#    #+#             */
/*   Updated: 2025/06/11 14:10:30 by ahetru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_no_such_file_or_directory(const char *command)
{
	char	*message;
	char	*final_msg;
	int		len;

	message = ft_strjoin("minishell: ", command);
	final_msg = ft_strjoin(message, ": No such file or directory\n");
	len = ft_strlen(final_msg);
	write(STDERR_FILENO, final_msg, len);
	free(message);
	free(final_msg);
}

void	print_permission_denied(const char *command)
{
	char	*msg;
	char	*final;

	msg = ft_strjoin("minishell: ", command);
	final = ft_strjoin(msg, ": Permission denied\n");
	write(STDERR_FILENO, final, ft_strlen(final));
	free(msg);
	free(final);
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
