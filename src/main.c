/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:40:07 by dcampas-          #+#    #+#             */
/*   Updated: 2025/04/29 17:37:42 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"
#include <stdlib.h>

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


int	main(int ac,char **av )
{
	char	*input;
	char	*expanded;
	t_token	*tokens;
	// char	**env_v;

	if (ac != 1)
	{
		printf("Usage: %s\n", av[0]);
		return (0);
	}
	while (1)
	{
		// env_v = set_path_environment();
		// print_vector(env_v);
		// free_vector(env_v);
		input = readline("minishell> ");
		if (!input)
		{
			printf ("exit\n");
			break ;
		}
		if (input && *input)
			add_history(input);
		expanded = expand_variables(input);
		tokens = tokenize(expanded);
		print_tokens(tokens);
		/*if (!tokens)
		{
			printf("Error: Tokenization failed\n");
			free(input);
			free(expanded);
			continue ;
		}*/

		t_command_block *command_block = parse_pipeline(tokens);
		while (command_block)
		{
			
		}
		execute_builtin(tokens);

		free_tokens(tokens);
		free(expanded);
		free(input);
	}
	return (0);
}
