/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahetru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 10:45:37 by ahetru            #+#    #+#             */
/*   Updated: 2025/06/06 10:45:51 by ahetru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	init_expand_struct(t_expand_var *expand_ctx, const char *input)
{
	expand_ctx->i = 0;
	expand_ctx->in_s_quote = 0;
	expand_ctx->in_d_quote = 0;
	expand_ctx->input = input;
	expand_ctx->result = ft_strdup("");
	if (!expand_ctx->result)
		return (-1);
	return (0);
}

static int	process_variable(t_expand_var *ctx, t_shell *shell)
{
	char	*expanded_var;

	if (ctx->input[ctx->i] == '$' && !ctx->in_s_quote && ctx->input[ctx->i + 1]
		&& (ft_isalnum(ctx->input[ctx->i + 1]) || ctx->input[ctx->i + 1] == '_'
			|| ctx->input[ctx->i + 1] == '?' || ctx->input[ctx->i + 1] == '{'))
	{
		expanded_var = extract_and_expand(ctx->input, &ctx->i, shell);
		if (!expanded_var)
			return (1);
		ctx->result = append_str(ctx->result, expanded_var);
		free(expanded_var);
		if (!ctx->result)
			return (1);
		return (1);
	}
	return (0);
}

static int	process_quotes(t_expand_var *ctx)
{
	if (ctx->input[ctx->i] == '\'' || ctx->input[ctx->i] == '\"')
	{
		update_quote_state(ctx->input[ctx->i],
			&ctx->in_s_quote, &ctx->in_d_quote);
		ctx->result = append_char(ctx->result, ctx->input[ctx->i++]);
		if (!ctx->result)
			return (1);
		return (1);
	}
	return (0);
}

static int	append_regular_char(t_expand_var *ctx)
{
	ctx->result = append_char(ctx->result, ctx->input[ctx->i++]);
	if (!ctx->result)
		return (0);
	return (1);
}

char	*expand_variables(const char *input, t_shell *shell)
{
	t_expand_var	expand_ctx;

	init_expand_struct(&expand_ctx, input);
	while (expand_ctx.input[expand_ctx.i])
	{
		if (process_quotes(&expand_ctx))
			continue ;
		if (process_variable(&expand_ctx, shell))
			continue ;
		if (!append_regular_char(&expand_ctx))
			return (NULL);
	}
	return (expand_ctx.result);
}
