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

char **tokens_to_argv(t_token *tokens)
{
	int count = 0;
	t_token *tmp = tokens;

	while (tmp)
	{
		if (tmp->type == T_WORD)
			count++;
		tmp = tmp->next;
	}

	char **argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return NULL;

	tmp = tokens;
	int i = 0;
	while (tmp)
	{
		if (tmp->type == T_WORD)
			argv[i++] = strdup(tmp->value); // ou ft_strdup
		tmp = tmp->next;
	}
	argv[i] = NULL;

	return argv;
}

void	execute_pipeline(t_command_block *blocks, char **envp)
{
	int pipe_fd[2];
	int prev_fd = -1;
	pid_t pid;

	while (blocks)
	{
		if (blocks->next && pipe(pipe_fd) == -1)
		{
			perror("pipe");
			return;
		}

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return;
		}
		else if (pid == 0) // CHILD
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (blocks->next)
			{
				close(pipe_fd[0]);
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
			}
			char **argv = tokens_to_argv(blocks->tokens);
			if (!argv)
				exit(EXIT_FAILURE);

			char *cmd_path = resolve_path(argv[0], envp);
			if (!cmd_path)
			{
				fprintf(stderr, "command not found: %s\n", argv[0]);
				free_vector(argv);
				exit(127);
			}
			execve(cmd_path, argv, envp);
			perror("execve");
			free(cmd_path);
			free_vector(argv);
			exit(127);
		}
		else // PARENT
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (blocks->next)
			{
				close(pipe_fd[1]);
				prev_fd = pipe_fd[0];
			}
		}
		blocks = blocks->next;
	}
	while (wait(NULL) > 0);
}
