/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:21:56 by dcampas-          #+#    #+#             */
/*   Updated: 2025/06/09 15:18:40 by dcampas-         ###   ########.fr       */
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
# include <termios.h>

extern int	g_signal_received;

typedef enum e_token_type
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

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;

}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_expand_var
{
	const char	*input;
	char		*result;
	int			i;
	int			in_s_quote;
	int			in_d_quote;
}	t_expand_var;

typedef struct s_parse_state
{
	const char	*line;
	int			i;
	char		buffer[1024];
	int			j;
}	t_parse_state;

typedef struct s_redir
{
	t_token_type	type;
	t_token			*operand;
	int				heredoc_fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_command_block
{
	t_token					*tokens;
	t_token					*argv_tokens;
	t_redir					*redirs;
	char					**argv;
	struct s_command_block	*next;
}	t_command_block;

typedef struct s_shell
{
	t_token			*tokens;
	t_command_block	*command_blocks;
	char			**env;
	char			*input;
	char			*expanded;
	int				last_exit_status;
}	t_shell;

//lexer
t_token			*new_token(t_token_type type, const char *value, int len);
void			free_tokens(t_token *token);
int				skip_spaces(const char *line, int i);
t_token			*create_quote_token(const char *line, int len, char quote_type);
int				is_word_boundary(char c);
t_token			*handle_quotes(const char *line, int *i, char quote_type);
t_token			*handle_pipe(int *i);
t_token			*handle_redir(const char *line, int *i);
int				handle_quoted_char(const char *line, int *i,
					char *buffer, int *j);
int				count_tokens(t_token *tokens);
int				has_adjacent_content(const char *line, int i, char quote_type);
char			**get_args_from_tokens(t_token *tokens);
t_token			*tokenize(const char *line);

// parser
int				check_syntax(t_token *tokens);
int				is_redirection(t_token *token);
t_command_block	*set_command_block(t_token *head_token);
void			parse_pipeline(t_shell *shell, t_token *tokens);
t_token			*token_dup_and_add_back(t_token **block_head, t_token *to_add);
void			parse_command_block(t_command_block *command_block);
void			update_quote_state(char c, int *in_single_q, int *in_double_q);
char			*expand_variables(const char *input, t_shell *shell);
char			*append_str(char *str, const char *to_append);
char			*append_char(char *str, char c);
char			*extract_and_expand(const char *input,
					int *pos, t_shell *shell);

//execution
void			execute_pipeline(t_shell *shell);
int				execute_builtin(char **argv, t_shell *shell);
int				pipe_and_execute(t_command_block *cmd, int prev_fd,
					int *fd, t_shell *shell);
void			execute_single_builtin(t_command_block *cmd, t_shell *shell);
bool			is_single_builtin(t_command_block *cmd);
int				prepare_pipe(int *fd);
void			print_command_not_found(const char *command);
int				is_builtin(const char *command);
int				handle_heredoc(t_token *operand, t_shell *shell);
void			apply_redirections(t_redir *redir);
int				prepare_heredocs(t_command_block *cmd, t_shell *shell);
int				handle_redirections(t_command_block *command_block);

// environment
char			**set_path_environment(t_shell *shell);
char			**copy_environment(char **envp);
int				count_environment_vars(char **envp);
char			*get_pathname(char *command, char **path_variable);
char			*ft_getenv(t_shell *shell, const char *var);
void			form_bin_path(char **envp_vec);
int				find_env_var(char **env, char *key);
int				update_env_var(char **env, char *var_name, char *value);
int				add_env_var(char ***env, char *key, char *value);
int				add_or_update_env(char ***env, char *key, char *value);
void			sort_env_copy(char **env);

// free commands
void			free_vector(char **vec);
void			free_shell(t_shell	*shell);
void			free_env(t_shell *shell);
void			exit_shell(t_shell	*shell, int exit_code);

// debugging functions
void			print_command_blocks(t_command_block *head_block);
void			print_all_command_blocks(t_command_block *head);

// builtins
int				builtin_pwd(char **args, t_shell *shell);
int				builtin_echo(char **args, t_shell *shell);
int				builtin_exit(char **args, t_shell *shell);
int				builtin_env(char **args, t_shell *shell);
int				builtin_cd(char **args, t_shell *shell);
int				builtin_unset(char **args, t_shell *shell);
int				builtin_export(char **args, t_shell *shell);

// export utils
void			print_invalid_export(char *arg);
int				is_valid_identifier_export(const char *str);
int				should_print_var(char *env_var);
int				print_filtered_env(char **sorted_env);
void			update_bin_paths(t_shell *shell);

// cd utils
int				update_pwd_vars(t_shell *shell, char *old_directory);
int				go_to_path(t_shell *shell, const char *target);
int				handle_no_args(t_shell *shell, char *current_dir);

// signals
void			handle_sigint(int sig);
void			setup_interactive_signals(void);
void			setup_child_signals(void);
void			ignore_signals(void);
void			wait_and_get_status(pid_t pid, int *last_status);
#endif
