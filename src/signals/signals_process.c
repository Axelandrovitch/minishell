/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:08:52 by dcampas-          #+#    #+#             */
/*   Updated: 2025/05/28 15:51:36 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Verificar y procesar señales recibidas
void	process_signals(void)
{
	ignore_signals();
	if (g_signal_received == SIGINT)
	{
		g_signal_received = 0;
		rl_on_new_line();
	}
	else if (g_signal_received == SIGQUIT)
		g_signal_received = 0;
	restore_signals();
}

// Función para usar en el main loop
int	check_and_handle_signals(char *input)
{
	if (handle_eof(input))
		return (1);
	process_signals();
	return (0);
}
