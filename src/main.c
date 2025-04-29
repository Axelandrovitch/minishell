/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:40:07 by dcampas-          #+#    #+#             */
/*   Updated: 2025/04/29 12:35:49 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(void)
{
	char	*input;
	char	*expanded;
	t_token	*tokens;

	while (1)
	{
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
			continue ;
		}
		free(input);
	}
	return (0);
}
