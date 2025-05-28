/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:23:19 by dcampas-          #+#    #+#             */
/*   Updated: 2025/05/28 11:25:56 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Variable global para manejar señales recibidas
int	g_signal_received = 0;

// Handler para SIGINT (Ctrl+C) en el shell principal
void	handle_sigint(int sig)
{
	(void)sig;
	g_signal_received = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// Handler para SIGINT durante ejecución de comandos
void	handle_sigint_child(int sig)
{
	(void)sig;
	g_signal_received = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
}

// Handler para SIGQUIT (Ctrl+\) durante ejecución de comandos
void	handle_sigquit_child(int sig)
{
	(void)sig;
	g_signal_received = SIGQUIT;
	write(STDOUT_FILENO, "Quit: 3\n", 8);
}

// Configurar señales para el shell principal (modo interactivo)
void	setup_interactive_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
