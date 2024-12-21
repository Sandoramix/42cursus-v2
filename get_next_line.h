/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 12:30:56 by odudniak          #+#    #+#             */
/*   Updated: 2024/12/21 14:25:30 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);

// UTILS
int		ft_strlen(char *str);

void	*ft_memmove(void *dest, const void *src, size_t n);

/**
 * @brief Allocates a new pointer and sets every byte to 0.
 * @param n Number of bytes to allocate.
 * @param size sizeof(<type>) of the pointer to allocate.
 * @return A pointer to the allocated memory.
 * @example
 * int *ptr = ft_calloc(sizeof(int));
 * // ptr is now a pointer to an int with every byte set to 0
 */
void	*ft_calloc(size_t n, size_t size);

#endif
