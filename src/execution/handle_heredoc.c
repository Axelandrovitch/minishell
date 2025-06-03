/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahetru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:20:14 by ahetru            #+#    #+#             */
/*   Updated: 2025/05/27 17:54:31 by ahetru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// static int	should_expand_heredoc(const char *delimiter)
// {
// 	int	i;
//
// 	i = 0;
// 	while (delimiter[i])
// 	{
// 		if (delimiter[i] == '\'' || delimiter[i] == '"')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }
//
// static char	*remove_quotes_from_delimiter(const char *delimiter)
// {
// 	char	*result;
// 	int		i;
// 	int		j;
//
// 	result = malloc(ft_strlen(delimiter) + 1);
// 	if (!result)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (delimiter[i])
// 	{
// 		if (delimiter[i] != '\'' && delimiter[i] != '"')
// 			result[j++] = delimiter[i];
// 		i++;
// 	}
// 	result[j] = '\0';
// 	return (result);
// }
//
// static char	*get_env_value(const char *var_name, t_shell *shell)
// {
// 	int	i;
//
// 	if (!var_name || !shell || !shell->env)
// 		return (NULL);
// 	i = 0;
// 	while (shell->env[i])
// 	{
// 		if (ft_strncmp(shell->env[i], var_name, ft_strlen(var_name)) == 0
// 			&& shell->env[i][ft_strlen(var_name)] == '=')
// 			return (&shell->env[i][ft_strlen(var_name) + 1]);
// 		i++;
// 	}
// 	return (NULL);
// }
//
// static char	*extract_and_expand_var(const char *start, int *i, t_shell *shell)
// {
// 	char	*var_name;
// 	char	*var_value;
// 	int		var_len;
// 	int		k;
//
// 	(*i)++;
// 	var_len = 0;
// 	while (start[1 + var_len] && (ft_isalnum(start[1 + var_len])
// 			|| start[1 + var_len] == '_'))
// 		var_len++;
// 	var_name = malloc(var_len + 1);
// 	if (!var_name)
// 		return (NULL);
// 	k = 0;
// 	while (k < var_len)
// 	{
// 		var_name[k] = start[1 + k];
// 		k++;
// 	}
// 	var_name[var_len] = '\0';
// 	var_value = get_env_value(var_name, shell);
// 	free(var_name);
// 	*i += var_len - 1;
// 	return (var_value ? ft_strdup(var_value) : ft_strdup(""));
// }
//
// static char	*expand_heredoc_variables(const char *line, t_shell *shell)
// {
// 	char	*result;
// 	char	*temp;
// 	int		i;
// 	int		j;
//
// 	if (!line)
// 		return (NULL);
// 	result = malloc(ft_strlen(line) * 2 + 1);
// 	if (!result)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '$' && line[i + 1] && (ft_isalnum(line[i + 1]) || line[i + 1] == '_'))
// 		{
// 			temp = extract_and_expand_var(&line[i], &i, shell);
// 			if (temp)
// 			{
// 				ft_strncpy(&result[j], temp, ft_strlen(temp));
// 				j += ft_strlen(temp);
// 				free(temp);
// 			}
// 		}
// 		else
// 			result[j++] = line[i++];
// 	}
// 	result[j] = '\0';
// 	return (result);
// }
//
// static void	write_line_to_fd(int fd, char *line, int expand, t_shell *shell)
// {
// 	char	*expanded_line;
//
// 	if (expand)
// 	{
// 		expanded_line = expand_heredoc_variables(line, shell);
// 		if (expanded_line)
// 		{
// 			write(fd, expanded_line, ft_strlen(expanded_line));
// 			free(expanded_line);
// 		}
// 	}
// 	else
// 		write(fd, line, ft_strlen(line));
// 	write(fd, "\n", 1);
// }
//
// int handle_heredoc(const char *delimiter, t_shell *shell)
// {
// 	int		pipe_fd[2];
// 	pid_t	pid;
// 	int		status;
// 	char	*clean_delim;
// 	int		expand;
//
// 	if (pipe(pipe_fd) < 0)
// 		return (-1);
// 	clean_delim = remove_quotes_from_delimiter(delimiter);
// 	if (!clean_delim)
// 		return (close(pipe_fd[0]), close(pipe_fd[1]), -1);
//
// 	expand = should_expand_heredoc(delimiter);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		signal(SIGINT, SIG_DFL);
// 		close(pipe_fd[0]);
//
// 		while (1)
// 		{
// 			char *line = readline("> ");
// 			if (!line)
// 				break;
// 			if (ft_strcmp(line, clean_delim) == 0)
// 			{
// 				free(line);
// 				break;
// 			}
// 			write_line_to_fd(pipe_fd[1], line, expand, shell);
// 			free(line);
// 		}
// 		close(pipe_fd[1]);
// 		free(clean_delim);
// 		exit(0);
// 	}
// 	else if (pid > 0)
// 	{
// 		close(pipe_fd[1]);
// 		waitpid(pid, &status, 0);
// 		free(clean_delim);
//
// 		if (WIFSIGNALED(status))
// 		{
// 			close(pipe_fd[0]);
// 			return (-1);
// 		}
// 		return pipe_fd[0];
// 	}
// 	else
// 	{
// 		close(pipe_fd[0]);
// 		close(pipe_fd[1]);
// 		free(clean_delim);
// 		return (-1);
// 	}
// }

static int	has_quotes(const char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			return (1);
		str++;
	}
	return (0);
}

static char	*remove_quotes(const char *str)
{
	char	*res;
	int		i = 0;
	int		j = 0;

	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

static void	write_line_to_fd(int fd, char *line, int expand, t_shell *shell)
{
	char	*expanded_line;

	if (expand)
	{
		expanded_line = expand_variables(line, shell);
		if (expanded_line)
		{
			write(fd, expanded_line, ft_strlen(expanded_line));
			free(expanded_line);
		}
	}
	else
		write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

int	handle_heredoc(const char *delimiter, t_shell *shell)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;
	char	*clean_delim;
	int		expand;

	if (pipe(pipe_fd) < 0)
		return (-1);
	clean_delim = remove_quotes(delimiter);
	if (!clean_delim)
		return (close(pipe_fd[0]), close(pipe_fd[1]), -1);

	expand = !has_quotes(delimiter);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(pipe_fd[0]);

		while (1)
		{
			char *line = readline("> ");
			if (!line)
				break;
			if (ft_strcmp(line, clean_delim) == 0)
			{
				free(line);
				break;
			}
			write_line_to_fd(pipe_fd[1], line, expand, shell);
			free(line);
		}
		close(pipe_fd[1]);
		free(clean_delim);
		exit(0);
	}
	else if (pid > 0)
	{
		close(pipe_fd[1]);
		waitpid(pid, &status, 0);
		free(clean_delim);

		if (WIFSIGNALED(status))
		{
			close(pipe_fd[0]);
			return (-1);
		}
		return pipe_fd[0];
	}
	else
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		free(clean_delim);
		return (-1);
	}
}

int prepare_heredocs(t_command_block *cmd, t_shell *shell)
{
	t_redir	*redir;

	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == T_HEREDOC)
			{
				int fd = handle_heredoc(redir->filename, shell);
				if (fd < 0)
					return (-1);
				redir->heredoc_fd = fd;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

