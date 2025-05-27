/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:08:52 by dcampas-          #+#    #+#             */
/*   Updated: 2025/05/27 17:49:39 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

#include "../../minishell.h"

// Verificar y procesar señales recibidas
void	process_signals(void)
{
	if (g_signal_received == SIGINT)
	{
		g_signal_received = 0;
		// Actualizar exit status por la interrupción
		// g_exit_status = 130; // Si tienes esta variable global
	}
	else if (g_signal_received == SIGQUIT)
	{
		g_signal_received = 0;
		// g_exit_status = 131; // Si tienes esta variable global
	}
}

// Función para usar en el main loop
int	check_and_handle_signals(char *input)
{
	if (handle_eof(input))
		return (1);
	process_signals();
	return (0);
}