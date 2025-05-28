/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:08:52 by dcampas-          #+#    #+#             */
/*   Updated: 2025/05/28 11:26:06 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Verificar y procesar señales recibidas
void	process_signals(void)
{
	if (g_signal_received == SIGINT)
		g_signal_received = 0;
	else if (g_signal_received == SIGQUIT)
		g_signal_received = 0;
}

// Función para usar en el main loop
int	check_and_handle_signals(char *input)
{
	if (handle_eof(input))
		return (1);
	process_signals();
	return (0);
}
