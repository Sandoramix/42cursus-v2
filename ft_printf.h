/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 07:06:50 by odudniak          #+#    #+#             */
/*   Updated: 2025/06/10 07:21:17 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <stdarg.h>

typedef unsigned int	t_uint;

typedef struct s_pf
{

}	t_pf;

int		ft_printf(const char *, ...);

int		printf_core(va_list *list, int fd);


int		ft_printchar(char c, int fd);
int		ft_printstr(char *str, int fd);
int		ft_printint(int value, int fd);
int		ft_printuint(t_uint value, int fd);
int		ft_printhex(t_uint value, bool is_upper, int fd);
int		ft_printaddr(void *ptr, int fd);

#endif