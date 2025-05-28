/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:21:56 by dcampas-          #+#    #+#             */
/*   Updated: 2025/05/28 13:52:28 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "libft/inc/libft.h"

extern int	g_signal_received; // Variable global para manejar señales

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

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct	s_redir
{
	t_token_type	type;
	char			*filename;
	struct s_redir	*next;
}	t_redir;

typedef struct	s_command_block
{
	t_token					*tokens;
	t_token					*argv_tokens;
	t_redir					*redirs;
	char					**argv;
	struct s_command_block	*next;
}	t_command_block;

typedef	struct	s_shell
{
	t_token			*tokens;
	t_command_block	*command_blocks;
	char			**env;
	char			**bin_paths;
	char			*input;
	char			*expanded;
	int				infile_fd;
	int				outfile_fd;
	int				last_exit_status;
}	t_shell;

//TOKEN
t_token	*new_token(t_token_type type, const char *value, int len);
void	free_tokens(t_token *token);
int		skip_spaces(const char *line, int i);


char	**get_args_from_tokens(t_token *tokens);

t_token	*tokenize(const char *line);

t_command_block	*set_command_block(t_token *head_token);

void	execute_pipeline(t_shell *shell);

int		handle_redirections(t_command_block *command_block);

// $
char	*expand_variables(const char *input, t_shell *shell);


// parsing
int		check_syntax(t_token *tokens);
int		is_redirection(t_token *token);
void	apply_redirections(t_redir *redir);
void	parse_pipeline(t_shell *shell, t_token *tokens);

// free commands
void	free_vector(char **vec);
void	free_shell(t_shell	*shell);
void	free_env(t_shell *shell);
void	exit_shell(t_shell	*shell, int exit_code);

// environment functions
char	**set_path_environment(void);
char	**copy_environment(char **envp);
int		count_environment_vars(char **envp);
char	*get_pathname(char *command, char **path_variable);
char	*ft_getenv(t_shell *shell, char *var);

// env_utils
int		find_env_var(char **env, char *key);
int		update_env_var(char **env, char *var_name, char *value);
int		add_env_var(char ***env, char *key, char *value);
int		add_or_update_env(char ***env, char *key, char *value);


// debugging functions
void	print_vector(char **vec);
void	print_command_blocks(t_command_block *head_block);
void	print_all_command_blocks(t_command_block *head);

// builtins
int		builtin_pwd(char **args);
int		builtin_echo(char **args);
int		builtin_exit(char **args, t_shell *shell);
int		builtin_env(char **args, char **env);
int		builtin_cd(char **args, t_shell *shell);
int		builtin_export(char **args, t_shell *shell);
int		builtin_unset(char **args, char **env);

// sort
void	sort_env_copy(char **env);

int		execute_builtin(char **argv, t_shell *shell);

// signals	
void	handle_sigint(int sig);
void	handle_sigint_child(int sig);
void	handle_sigquit_child(int sig);
void	setup_interactive_signals(void);

void	setup_child_signals(void);
void	setup_execution_signals(void);
void	ignore_signals(void);
void	restore_signals(void);
int		handle_eof(char *input);

void	process_signals(void);
int		check_and_handle_signals(char *input);


#endif