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

# include "../../minishell.h"

char	*generate_tmp_file(void)
{
	static int	heredoc_counter = 0;
	char		*pid_str;
	char		*counter_str;
	char		*filename;
	char		*full_path;

	pid_str = ft_itoa(getpid());
	counter_str = ft_itoa(heredoc_counter++);
	filename = ft_strjoin("minish-ft_thd", pid_str);
	filename = ft_strjoin_free_s1(filename, "-");
	filename = ft_strjoin_free_s1(filename,counter_str);
	full_path = ft_strjoin("/tmp/", filename);
	//improve malloc error handling
	free(pid_str);
	free(counter_str);
	free(filename);
	return (full_path);
}

int	handle_heredoc(char *delimeter)
{
	char	*line;
	char	*tmpfile;
	int		fd;

	tmpfile = generate_tmp_file();
	if (!tmpfile)
		return  (-1);
	fd = open(tmpfile, O_WRONLY | O_CREAT | O_TRUNC | 0600);
	//why trunc ?
	if (fd == -1)
	{
		perror("open");
		free(tmpfile);
		return (-1);
	}
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimeter) == 0)
		{
			free(line);
			break ;
		}
		else
			ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	close(fd);
	fd = open(tmpfile, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		unlink(tmpfile);
		free(tmpfile);
		return (-1);
	}
	unlink(tmpfile);
	free(tmpfile);
	return (fd);
}

