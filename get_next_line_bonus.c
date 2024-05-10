/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtammi <rtammi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:13:25 by rtammi            #+#    #+#             */
/*   Updated: 2024/05/10 16:33:19 by rtammi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*extract_remaining_buffer(char *buffer)
{
	ssize_t	end_i;
	ssize_t	rem_i;
	char	*rem_content;

	end_i = 0;
	rem_i = 0;
	while (buffer[end_i] && buffer[end_i] != '\n')
		end_i++;
	if (!buffer[end_i])
		return (free_return(buffer));
	rem_content = ft_calloc(ft_strlen(buffer) - end_i + 1, sizeof(char));
	if (!rem_content)
		return (free_return(buffer));
	end_i++;
	while (buffer[end_i])
		rem_content[rem_i++] = buffer[end_i++];
	free(buffer);
	buffer = NULL;
	return (rem_content);
}

char	*extract_line(char *buffer)
{
	ssize_t	i;
	char	*current_line;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
		current_line = ft_calloc(i + 1, sizeof(char));
	else
		current_line = ft_calloc(i + 2, sizeof(char));
	if (!current_line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		current_line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		current_line[i++] = '\n';
	return (current_line);
}

char	*read_cat_chunks(int fd, char *buffer, char *accum_data)
{
	ssize_t	bytes;
	char	*cat_buffer;

	bytes = 1;
	while (bytes > 0 && !ft_strchr(accum_data, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (NULL);
		buffer[bytes] = 0;
		cat_buffer = ft_strjoin(accum_data, buffer);
		if (!cat_buffer)
		{
			free(accum_data);
			return (free_return(buffer));
		}
		free(accum_data);
		accum_data = cat_buffer;
	}
	return (accum_data);
}

char	*read_file_data(int fd, char *accum_data)
{
	char	*buffer;

	if (!accum_data)
		accum_data = ft_calloc(1, 1);
	if (!accum_data)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (free_return(accum_data));
	accum_data = read_cat_chunks(fd, buffer, accum_data);
	if (!accum_data)
		return (NULL);
	free(buffer);
	buffer = NULL;
	if (ft_strlen(accum_data) == 0)
		return (free_return(accum_data));
	return (accum_data);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || fd >= OPEN_MAX)
	{
		if (buffer[fd] != NULL)
			free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = read_file_data(fd, buffer[fd]);
	if (buffer[fd] == NULL)
		return (NULL);
	line = extract_line(buffer[fd]);
	if (line == NULL)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = extract_remaining_buffer(buffer[fd]);
	return (line);
}
