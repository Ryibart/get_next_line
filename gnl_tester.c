/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_tester.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtammi <rtammi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:56:36 by rtammi            #+#    #+#             */
/*   Updated: 2024/06/13 15:38:22 by rtammi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*══| gnl_tester |═════════════════════════════════════════════════════════════*
    
    Purpose:    Opens three text files and reads lines from each using the
                `get_next_line` function. It prints the lines read from each
                file, along with the total number of lines read from all files.

    Parameters: 
                None.

    Returns:    
                0 -- Indicates successful execution of the program.

*═════════════════════════════════════════════════════════════════════════════*/

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"
int	main(void)
{
	char	*line;
	char	*line2;
	char	*line3;
	int		one = 1;
	int		two = 1;
	int		three = 1;
	int		fd1;
	int		fd2;
	int		fd3;
	int		total;
	fd1 = open("your_file1.txt", O_RDONLY);
	fd2 = open("your_file2.txt", O_RDONLY);
	fd3 = open("your_file3.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd1);
		line2 = get_next_line(fd2);
		line3 = get_next_line(fd3);
		if (!line && !line2 && !line3)
			break ;
		if (line)
		printf("fd 1 line [%02d]: %s", one, line);
		if (line2)
		printf("fd 2 line [%02d]: %s", two, line2);
		if (line3)
		printf("fd 3 line [%02d]: %s", three, line3);
		total = one + two + three;
		printf("total lines: %d\n", total);
		free(line);
		free(line2);
		free(line3);
		if (line)
		one++;
		if (line2)
		two++;
		if (line3)
		three++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}

