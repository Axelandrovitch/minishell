/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:56:14 by dcampas-          #+#    #+#             */
/*   Updated: 2025/05/28 11:26:05 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Configurar señales para procesos hijo (comandos ejecutándose)
void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

// Configurar señales mientras se ejecuta un comando (proceso padre esperando)
void	setup_execution_signals(void)
{
	signal(SIGINT, handle_sigint_child);
	signal(SIGQUIT, handle_sigquit_child);
}

// Ignorar todas las señales (útil durante parsing crítico)
void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

// Restaurar señales después de ignorarlas
void	restore_signals(void)
{
	setup_interactive_signals();
}

// Manejar EOF (Ctrl+D) - verificar si readline devolvió NULL
int	handle_eof(char *input)
{
	if (!input)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		return (1);
	}
	return (0);
}
