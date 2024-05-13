/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtammi <rtammi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:13:25 by rtammi            #+#    #+#             */
/*   Updated: 2024/05/13 16:46:35 by rtammi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*══| get_next_line |══════════════════════════════════════════════════════════*
	
	Purpose:	Reads a file descriptor line by line, providing each line as a
				null-terminated string with the newline character included.
				This function allows sequential reading of text files without
				loading the entire file into memory, making it suitable for
				processing large files or streams.
				
	Parameters:
				fd (IN) -- The file descriptor to read from.

	Returns:	
				A pointer to the line read from the file descriptor. If an error
				occurs, `NULL` is returned.

	Helpers:	
				`extract_remaining_buffer` -- Extracts the remaining content
											  of the buffer after the
											  newline character.
				`extract_line` -- Extracts the line from the buffer.
				`read_cat_chunks` -- Reads and concatenates chunks of data from
									 the file descriptor.
				`read_file_data` -- Reads the data from the file descriptor 
									and manages buffer allocation.
				`get_next_line` -- The main function that orchestrates the
								   reading of lines from the file descriptor.


*═════════════════════════════════════════════════════════════════════════════*/

#include "get_next_line.h"

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
		return (free_return(buffer));
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
			accum_data = NULL;
			free(buffer);
			buffer = NULL;
			return (NULL);
		}
		free(accum_data);
		accum_data = NULL;
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
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (buffer != NULL)
			free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = read_file_data(fd, buffer);
	if (buffer == NULL)
		return (NULL);
	line = extract_line(buffer);
	if (line == NULL)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = extract_remaining_buffer(buffer);
	return (line);
}
