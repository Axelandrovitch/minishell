/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:26:20 by dcampas-          #+#    #+#             */
/*   Updated: 2024/11/11 12:58:37 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/get_next_line.h"
#include "../../inc/libft.h"

char	*extract_line(char *basin_buffer)
{
	int		i;
	int		j;
	char	*line;

	if (!basin_buffer || basin_buffer[0] == '\0')
		return (NULL);
	i = 0;
	while (basin_buffer[i] && basin_buffer[i] != '\n')
		i++;
	line = (char *)malloc(i + 2);
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = basin_buffer[j];
		j++;
	}
	if (basin_buffer[i] == '\n')
		line[j++] = '\n';
	line[j] = '\0';
	return (line);
}

char	*obtain_remaining(char *basin_buffer)
{
	int		i;
	int		j;
	char	*remaining;

	if (!basin_buffer)
		return (NULL);
	i = 0;
	while (basin_buffer[i] && basin_buffer[i] != '\n')
		i++;
	if (basin_buffer[i] == '\n')
		i++;
	remaining = (char *)malloc(ft_strlen(basin_buffer) - i + 1);
	if (!remaining)
	{
		free(basin_buffer);
		return (NULL);
	}
	j = 0;
	while (basin_buffer[i])
		remaining[j++] = basin_buffer[i++];
	remaining[j] = '\0';
	free(basin_buffer);
	return (remaining);
}

void	*append_buffer(char *basin_buffer, char *read_buffer)
{
	char	*temp;

	temp = ft_strjoin(basin_buffer, read_buffer);
	if (!temp)
		return (NULL);
	free(basin_buffer);
	return (temp);
}

char	*read_from_file(char *basin_buffer, int fd)
{
	int		bytes_read;
	char	*cup_buffer;

	cup_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!cup_buffer)
		return (NULL);
	bytes_read = read(fd, cup_buffer, BUFFER_SIZE);
	if (bytes_read == -1)
	{
		free(cup_buffer);
		return (free(basin_buffer), basin_buffer = NULL, NULL);
	}
	while (bytes_read > 0)
	{
		cup_buffer[bytes_read] = '\0';
		basin_buffer = append_buffer(basin_buffer, cup_buffer);
		if (ft_strchr(basin_buffer, '\n'))
			break ;
		bytes_read = read(fd, cup_buffer, BUFFER_SIZE);
	}
	free(cup_buffer);
	if (bytes_read == -1)
		return (NULL);
	return (basin_buffer);
}

char	*get_next_line(int fd)
{
	static char	*basin_buffer;
	char		*line;
	char		*new_basin_buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!basin_buffer)
		basin_buffer = ft_calloc(1, sizeof(char));
	if (!ft_strchr(basin_buffer, '\n'))
		basin_buffer = read_from_file(basin_buffer, fd);
	if (!basin_buffer)
		return (NULL);
	line = extract_line(basin_buffer);
	if (!line)
		return (free(basin_buffer), basin_buffer = NULL, NULL);
	new_basin_buffer = obtain_remaining(basin_buffer);
	if (!new_basin_buffer)
		return (free(line), free(basin_buffer), basin_buffer = NULL, NULL);
	basin_buffer = new_basin_buffer;
	return (line);
}
