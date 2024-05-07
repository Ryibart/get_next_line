/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtammi <rtammi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:13:28 by rtammi            #+#    #+#             */
/*   Updated: 2024/05/07 20:13:33 by rtammi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*u_s;

	i = 0;
	u_s = (unsigned char *)s;
	while (i < n)
	{
		u_s[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ret;

	if (count != 0 && size != 0 && count > (SIZE_MAX / size))
		return (0);
	ret = malloc(count * size);
	if (!ret)
		return (0);
	ft_bzero(ret, count * size);
	return (ret);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	u_c;

	i = 0;
	u_c = (char)c;
	while (s[i] != '\0')
	{
		if (s[i] == u_c)
			return ((char *)&s[i]);
		i++;
	}
	if (u_c == '\0')
		return ((char *)&s[i]);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*strjoin_free(char const *s1, char const *s2)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	ret = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ret)
		return (0);
	while (s1[i] != '\0')
	{
		ret[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		ret[i] = s2[j];
		i++;
		j++;
	}
	ret[i] = '\0';
	return (ret);
}
