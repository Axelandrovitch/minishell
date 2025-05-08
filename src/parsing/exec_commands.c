/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahetru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:46:01 by ahetru            #+#    #+#             */
/*   Updated: 2025/05/06 17:46:02 by ahetru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int contains_separator(t_command_block *block)
{
    t_token *tok = block->tokens;
    while (tok)
    {
		if (tok->type == T_PIPE || tok->type == T_REDIR_IN || tok->type == T_REDIR_OUT
            || tok->type == T_HEREDOC|| tok->type == T_REDIR_APPEND)
        {
			// De momento un printf se tendra que implementar
            printf("Found separator token type: %d (value: %s)\n", tok->type, tok->value);
        }
        tok = tok->next;
    }
    return (0);
}
