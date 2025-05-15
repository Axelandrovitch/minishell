/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:21:56 by dcampas-          #+#    #+#             */
/*   Updated: 2025/04/29 17:18:21 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>

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
	T_DQUOTE,		// "comi dobles"
	T_SQUOTE,		// 'comi simples'
	T_EMPTY

}	t_token_type;

typedef struct	s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;

}	t_token;

typedef struct	s_redir
{
	t_token_type	type;
	char	*filename;
	struct s_redir	*next;
}	t_redir;

typedef struct	s_command_block
{
	t_token	*tokens;
	t_token	*argv_tokens;
	t_redir	*redirs;
	struct s_command_block	*next;
}	t_command_block;

typedef	struct	s_shell
{
	t_token	*tokens;
	t_command_block	*command_blocks;
	char	**env;
	char	**bin_paths;
	char	*input;
	char	*expanded;
	int		infile_fd;
	int		outfile_fd;
}	t_shell;

//TOKEN
t_token	*new_token(t_token_type type, const char *value, int len);
void	free_tokens(t_token *token);
int		skip_spaces(const char *line, int i);
void	print_tokens(t_token *token);


char	**get_args_from_tokens(t_token *tokens);

t_token	*tokenize(const char *line);

t_command_block	*set_command_block(t_token *head_token);

void	parse_pipeline(t_shell *shell, t_token *tokens);

void	execute_pipeline(t_shell *shell);

int	handle_redirections(t_command_block *command_block);

// $
char	*expand_variables(const char *input);


// parsing

int	is_redirection(t_token *token);

// free commands

void	free_shell(t_shell	*shell);

void	free_env(t_shell *shell);

void	exit_shell(t_shell	*shell, int exit_code);

// environment functions
char	**set_path_environment(void);

char	**copy_environment(char **envp);

char	*get_pathname(char *command, char **path_variable);

// debugging functions
void	print_vector(char **vec);
void	print_command_blocks(t_command_block *head_block);
void	print_all_command_blocks(t_command_block *head);

// memory related functions
void	free_vector(char **vec);

// builtins
int		execute_builtin(t_token *tokens);

#endif

