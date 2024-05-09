/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtammi <rtammi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:13:28 by rtammi            #+#    #+#             */
/*   Updated: 2024/05/09 18:05:51 by rtammi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*free_return(void *str)
{
	free(str);
	return (NULL);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ret;

	if (count != 0 && size != 0 && count > (SIZE_MAX / size))
		return (NULL);
	ret = malloc(count * size);
	if (!ret)
		return (NULL);
	while (count * size > 0)
	{
		((unsigned char *)ret)[count * size - 1] = 0;
		count--;
	}
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
	return (NULL);
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
		return (NULL);
	ret = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ret)
		return (NULL);
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
