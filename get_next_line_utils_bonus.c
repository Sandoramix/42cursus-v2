/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 12:51:24 by odudniak          #+#    #+#             */
/*   Updated: 2024/12/21 14:26:25 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = dest;
	s = (unsigned char *)src;
	if (d == s)
		return (dest);
	if (d >= s && d <= s + n)
	{
		d += n;
		s += n;
		while (n--)
			*--d = *--s;
		return (dest);
	}
	while (n--)
		*d++ = *s++;
	return (dest);
}

void	*ft_calloc(size_t n, size_t size)
{
	const size_t	total_size = n * size;
	size_t			i;
	char			*ptr;

	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	i = -1;
	while (++i < total_size)
		ptr[i] = 0;
	return (ptr);
}
