/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtammi <rtammi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:13:25 by rtammi            #+#    #+#             */
/*   Updated: 2024/05/08 18:20:52 by rtammi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_return(void *str)
{
	free(str);
	return (NULL);
}

char	*fd_next(char *buffer)
{
	int		i;
	int		j;
	char	*next;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free_return(buffer));
	next = ft_calloc(ft_strlen(buffer) - i + 1, sizeof(char));
	if (!next)
		return (free_return(buffer));
	i++;
	while (buffer[i])
		next[j++] = buffer[i++];
	free(buffer);
	return (next);
}

char	*fd_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer[i])
		return (0);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
		line = ft_calloc(i + 1, sizeof(char));
	else
		line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (free_return(buffer));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*fd_file(int fd, char *result)
{
	char	*buffer;
	int		read_bytes;
	char	*temp;

	if (!result)
		result = ft_calloc(1, 1);
	if (!result)
		return (free_return(result));
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (free_return(result));
	read_bytes = 1;
	while (read_bytes > 0 && !ft_strchr(result, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free_return(result));
		buffer[read_bytes] = '\0';
		temp = strjoin_free(result, buffer);
		if (!temp)
		{
			free(result);
			return (free_return(buffer));
		}
		free(result);
		result = temp;
	}
	free(buffer);
	if (ft_strlen(result) == 0)
		return (free_return(result));
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free_return(buffer));
	buffer = fd_file(fd, buffer);
	if (!buffer)
		return (free_return(buffer));
	line = fd_line(buffer);
	buffer = fd_next(buffer);
	return (line);
}
