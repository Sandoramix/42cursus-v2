/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 12:37:51 by odudniak          #+#    #+#             */
/*   Updated: 2024/12/21 14:37:17 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	ft_idxof(char *str, char c)
{
	int	i;

	i = -1;
	while (str && str[++i])
		if (str[i] == c)
			return (i);
	return (-1);
}

static char	*append_string(char *str, char *buff, int newline_idx)
{
	const int	str_size = ft_strlen(str);
	int			buff_size;
	char		*result;
	int			i;

	if (ft_strlen(buff) == 0)
		return (str);
	if (newline_idx != -1)
		buff_size = newline_idx + 1;
	else
		buff_size = ft_strlen(buff);
	result = ft_calloc(str_size + buff_size + 1, sizeof(char));
	if (!result)
		return (free(str), NULL);
	i = -1;
	while (++i < str_size)
		result[i] = str[i];
	while (i < str_size + buff_size)
	{
		result[i] = buff[i - str_size];
		i++;
	}
	ft_memmove(buff, buff + buff_size,
		(ft_strlen(buff) - (buff_size - newline_idx == -1)));
	return (free(str), result);
}

char	*get_next_line(int fd)
{
	static char	buffer[GNL_MAX_FD_COUNT][BUFFER_SIZE + 1] = {0};
	char		*result;
	ssize_t		bytes;
	int			newline_idx;

	if (BUFFER_SIZE < 1 || fd < 0 || fd >= GNL_MAX_FD_COUNT)
		return (NULL);
	result = NULL;
	while (true)
	{
		newline_idx = ft_idxof(buffer[fd], '\n');
		result = append_string(result, buffer[fd], newline_idx);
		if (newline_idx != -1)
			return (result);
		bytes = read(fd, buffer[fd], BUFFER_SIZE);
		if (bytes < 0)
			return (free(result), NULL);
		buffer[fd][bytes] = '\0';
		if (bytes == 0)
			return (result);
	}
	return (result);
}

//int	main(int argc, char **argv)
//{
//	int		fd;
//	char	*line;

//	if (argc != 2)
//		return (write(2, "Usage: ", 7), write(2, argv[0], ft_strlen(argv[0])),
//			write(2, " <file>\n", 8), 1);
//	fd = open(argv[1], O_RDONLY);
//	if (fd < 0)
//		return (write(2, "Error: cannot open file\n", 25), 1);
//	line = get_next_line(fd);
//	write(1, "[", 1);
//	write(1, line, ft_strlen(line));
//	write(1, "]", 2);
//	while (line)
//	{
//		free(line);
//		line = get_next_line(fd);
//		write(1, "[", 1);
//		write(1, line, ft_strlen(line));
//		write(1, "]", 2);
//	}
//	return (close(fd), 0);
//}
