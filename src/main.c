/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:40:07 by dcampas-          #+#    #+#             */
/*   Updated: 2025/05/29 19:14:31 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

static void	init_minishell(t_shell *shell, char **envp)
{
	shell->env = NULL;
	shell->bin_paths = NULL;
	shell->command_blocks = NULL;
	shell->input = NULL;
	shell->expanded = NULL;
	shell->tokens = NULL;
	shell->env = copy_environment(envp);
	shell->bin_paths = set_path_environment();
}

// Procesar el input y manejar señales/EOF
static int	process_input_line(t_shell *shell)
{
	if (!shell->input)
	{
		printf("exit\n");
		return (1);
	}
/* 	if (check_and_handle_signals(shell->input))
	{
		free(shell->input);
		shell->input = NULL;
		return (1);
	} */
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
		return ;//TODO
	}
	parse_pipeline(shell, shell->tokens);
	print_all_command_blocks(shell->command_blocks);
	execute_pipeline(shell);
}

/* void	ft_setenv(t_shell *shell, const char *key, const char *value)
{
	char	*env_var;

	if (!key || !value)
		return ;
	env_var = ft_strjoin(key, "=");
	if (!env_var)
		return ;
	env_var = ft_strjoin(env_var, value);
	if (!env_var)
		return ;
	add_or_update_env(&shell->env, env_var, NULL);
	free(env_var);
} */

void	update_shlvl(t_shell *shell)
{
	char	*shlvl_str;
	int		shlvl;
	char	*new_value;
	char	*args[] = {"unset", "SHLVL", NULL};

	shlvl_str = ft_getenv(shell, "SHLVL");
	if (!shlvl_str)
	{
		update_env_var(shell->env, "SHLVL", "1");
		return ;
	}
	shlvl = ft_atoi(shlvl_str);
	if (shlvl < 0)
		shlvl = 0;
	else if (shlvl >= 999)
	{
		printf("minishell: warning: SHLVL too high, resetting to 1\n");
		shlvl = 1;
	}
	else
		shlvl++;
	new_value = ft_itoa(shlvl);

	builtin_unset(args, shell->env);
	update_env_var(shell->env, "SHLVL", new_value);
	free(new_value);
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
			break;
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
	free_env(&shell);
	return (0);
}
