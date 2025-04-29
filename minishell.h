/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:21:56 by dcampas-          #+#    #+#             */
/*   Updated: 2025/04/29 11:29:00 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "libft/inc/libft.h"

typedef enum	e_token_type
{
	T_WORD,			// "palabra"
	T_PIPE,			// "|"
	T_REDIR_IN,		// "<"
	T_REDIR_OUT,	// ">"
	T_REDIR_APPEND,	// ">>"
	T_HEREDOC,		// "<<"
	T_DQUOTE,		// "\"comi dobles\""
	T_SQUOTE,		// "'comi simples'"
	T_EMPTY

}	t_token_type;

typedef struct	s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;

}	t_token;

//TOKEN
t_token	*new_token(t_token_type type, const char *value, int len);
void	free_tokens(t_token *token);
int		skip_spaces(const char *line, int i);
void	print_tokens(t_token *token);

t_token	*tokenize(const char *line);

// $
char		*expand_variables(const char *input);


#endif

