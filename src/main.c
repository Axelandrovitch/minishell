/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:40:07 by dcampas-          #+#    #+#             */
/*   Updated: 2025/05/22 14:24:40 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>

// // Solo para testear
// void print_tokens(t_token *head)
// {
//     t_token *current = head;
//
//     while (current != NULL)
//     {
//         switch (current->type)
//         {
//             case T_WORD:
//                 printf("T_WORD       : ");
//                 break;
//             case T_PIPE:
//                 printf("T_PIPE       : ");
//                 break;
//             case T_REDIR_IN:
//                 printf("T_REDIR_IN   : ");
//                 break;
//             case T_REDIR_OUT:
//                 printf("T_REDIR_OUT  : ");
//                 break;
//             case T_REDIR_APPEND:
//                 printf("T_REDIR_APPEND: ");
//                 break;
//             case T_HEREDOC:
//                 printf("T_HEREDOC    : ");
//                 break;
//             case T_DQUOTE:
//                 printf("T_DQUOTE     : ");
//                 break;
//             case T_SQUOTE:
//                 printf("T_SQUOTE     : ");
//                 break;
//             case T_EMPTY:
//                 printf("T_EMPTY      : ");
//                 break;
//             default:
//                 printf("UNKNOWN      : ");
//                 break;
//         }
//
//         if (current->value)
//             printf("\"%s\"\n", current->value);
//         else
//             printf("(null)\n");
//
//         current = current->next;
//     }
// }

void	init_minishell (t_shell *shell, char **envp)
{
	shell->env = NULL;
	shell->bin_paths = NULL;
	shell->command_blocks= NULL;
	shell->input = NULL;
	shell->expanded = NULL;
	shell->tokens = NULL;
	shell->env = copy_environment(envp);
	shell->bin_paths = set_path_environment();
}

int	main(int ac,char **av, char **envp)
{
	t_shell	shell;

	if (ac != 1)
	{
		printf("Usage: %s\n", av[0]);
		return (0);
	}
	init_minishell(&shell, envp);
	while (1)
	{
		shell.input = readline("minishell> ");
		if (!shell.input)
		{
			printf ("exit\n");
			break ;
		}
		if (shell.input && *shell.input)
			add_history(shell.input);
		shell.expanded = expand_variables(shell.input, &shell);
		shell.tokens = tokenize(shell.expanded);
		if (check_syntax(shell.tokens))
			exit_shell(&shell, EXIT_FAILURE);
		parse_pipeline(&shell, shell.tokens);
		print_all_command_blocks(shell.command_blocks);
		execute_pipeline(&shell);
		// execute_builtin(shell.tokens);
		// free_shell(&shell);
		// exit_shell(&shell, 0);
	}
	free_env(&shell);
	return (0);
}
