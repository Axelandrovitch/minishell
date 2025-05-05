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
		//print_tokens(tokens);
		/*if (!tokens)
		{
			printf("Error: Tokenization failed\n");
			free(input);
			free(expanded);
			continue ;
		}*/

		execute_builtin(tokens);

		free_tokens(tokens);
		free(expanded);
		free(input);
	}
	return (0);
}
