/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:40:07 by dcampas-          #+#    #+#             */
/*   Updated: 2025/04/29 14:12:55 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	*expanded;
	t_token	*tokens;
	char **env_v;

	(void)ac;
	(void)av;
	while (1)
	{
		env_v = set_path_environment(env);
		//print_vector(env_v);
		free_vector(env_v);
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
		if (!tokens)
		{
			printf("Error: Tokenization failed\n");
			free(input);
			free(expanded);
			continue ;
		}
		free_tokens(tokens);
		free(expanded);
		free(input);
	}
	return (0);
}