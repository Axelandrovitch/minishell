/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:40:07 by dcampas-          #+#    #+#             */
/*   Updated: 2025/04/25 10:48:21 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>


# include <readline/readline.h>
# include <readline/history.h>

int main()
{
	char	*input;

	while (1)
	{
		input = readline("minishell> ");

		if (!input)
		{
			printf ("exit\n");
			break ;
		}
		if (input)
		{
			add_history(input);
		}
		free(input);
	}
	return (0);
}