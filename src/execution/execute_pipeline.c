/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahetru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:26:54 by ahetru            #+#    #+#             */
/*   Updated: 2025/05/21 14:26:55 by ahetru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_side_effect(char	*builtin)
{
	return (0);
}

int	is_pipeline(t_command_block *command_blocks)
{
	t_command_block	*current;
	int	count;

	current = command_blocks;
	count = 0;
	while (current->next)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	execute_pipeline(t_shell *shell)
{
	t_command_block	*current;
	int				fd[2];
	int				prev_fd;
	pid_t			pid;

	current = shell->command_blocks;
	prev_fd = -1;
	while (current)
	{
		if (is_builtin(current->argv[0]))
		{
			handle_builtin(current, shell);
		}
		else
		{
			//handle the rest	
		}
		current = current->next;
	}
}
