/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:23:19 by dcampas-          #+#    #+#             */
/*   Updated: 2025/05/28 16:25:55 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Estado global de señales
int g_received_signal = 0;

int is_command_running(void)
{
	if (g_received_signal == SIGINT)
	{
		g_received_signal = 0;
		return (1);
	}
	return (0);
}

//Maneja la señal SIGINT (Ctrl+C) en el shell interactivo
void handle_interactive_ctrl_c(int signal_num)
{
	ignore_signals();
	(void)signal_num;
	g_received_signal = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	if (!is_command_running())
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	restore_signals();
}

//Maneja SIGINT (Ctrl+C) para procesos hijo
void handle_child_ctrl_c(int signal_num)
{
	(void)signal_num;
	g_received_signal = SIGINT;
}


//Maneja SIGQUIT (Ctrl+\) para procesos hijo

void handle_child_ctrl_backslash(int signal_num)
{
	(void)signal_num;
	g_received_signal = SIGQUIT;
	write(STDOUT_FILENO, "Quit: 3\n", 8);
}


//Configura los manejadores de señales para el modo interactivo
void setup_interactive_mode_signals(void)
{
	signal(SIGINT, handle_interactive_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
