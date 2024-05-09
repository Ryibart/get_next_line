/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtammi <rtammi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:13:31 by rtammi            #+#    #+#             */
/*   Updated: 2024/05/09 17:00:39 by rtammi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>

char	*get_next_line(int fd);

char	*free_return(void *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
char	*strjoin_free(char const *s1, char const *s2);

#endif