/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:40:07 by dcampas-          #+#    #+#             */
/*   Updated: 2025/06/05 16:46:49 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// // Solo para testear
void print_tokens(t_token *head)
{
    t_token *current = head;

    while (current != NULL)
    {
        switch (current->type)
        {
            case T_WORD:
                printf("T_WORD       : ");
                break;
            case T_PIPE:
                printf("T_PIPE       : ");
                break;
            case T_REDIR_IN:
                printf("T_REDIR_IN   : ");
                break;
            case T_REDIR_OUT:
                printf("T_REDIR_OUT  : ");
                break;
            case T_REDIR_APPEND:
                printf("T_REDIR_APPEND: ");
                break;
            case T_HEREDOC:
                printf("T_HEREDOC    : ");
                break;
            case T_DQUOTE:
                printf("T_DQUOTE     : ");
                break;
            case T_SQUOTE:
                printf("T_SQUOTE     : ");
                break;
            case T_EMPTY:
                printf("T_EMPTY      : ");
                break;
            default:
                printf("UNKNOWN      : ");
                break;
        }

        if (current->value)
            printf("\"%s\"\n", current->value);
        else
            printf("(null)\n");

        current = current->next;
    }
}

static void	init_minishell(t_shell *shell, char **envp)
{
	shell->env = NULL;
	shell->command_blocks = NULL;
	shell->input = NULL;
	shell->expanded = NULL;
	shell->tokens = NULL;
	shell->env = copy_environment(envp);
}

// Procesar el input y manejar señales/EOF
static int	process_input_line(t_shell *shell)
{
	if (!shell->input)
	{
		printf("exit\n");
		return (1);
	}
	if (g_signal_received == SIGINT)
	{
		g_signal_received = 0;
		return (0);
	}
	if (shell->input && *shell->input)
		add_history(shell->input);
	return (0);
}

// Ejecutar la pipeline completa del comando
static void	execute_command_pipeline(t_shell *shell)
{
	shell->expanded = expand_variables(shell->input, shell);
	shell->tokens = tokenize(shell->expanded);
	if (check_syntax(shell->tokens))
	{
		free_shell(shell);
		return ;
	}
	parse_pipeline(shell, shell->tokens);
	execute_pipeline(shell);
}

// Actualiza la variable de entorno SHLVL
void	update_shlvl(t_shell *shell)
{
	char	*shlvl_str;
	int		shlvl;
	char	*new_value;

	shlvl_str = ft_getenv(shell, "SHLVL");
	if (!shlvl_str)
		shlvl = 1;
	else
	{
		shlvl = ft_atoi(shlvl_str);
		if (shlvl < 0)
			shlvl = 0;
		else
			shlvl++;
		free(shlvl_str);
	}
	new_value = ft_itoa(shlvl);
	if (new_value)
	{
		add_or_update_env(&shell->env, "SHLVL", new_value);
		free(new_value);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	if (ac != 1)
	{
		printf("Usage: %s\n", av[0]);
		return (0);
	}
	shell.last_exit_status = 0;
	init_minishell(&shell, envp);
	update_shlvl(&shell);
	setup_interactive_signals();
	while (1)
	{
		shell.input = readline("minishell> ");
		if (process_input_line(&shell))
			break ;
		if (shell.input && *shell.input)
		{
			execute_command_pipeline(&shell);
			free_shell(&shell);
		}
		else
		{
			free(shell.input);
			shell.input = NULL;
		}
	}
	rl_clear_history();
	exit_shell(&shell, 0);
	return (0);
}
