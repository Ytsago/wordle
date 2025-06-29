/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 07:29:36 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/28 18:14:49 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "libft.h"
#include "wordle.h"

int	parse_file(t_vector *word_list, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	vector_init(word_list, sizeof(char *));
	errno = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strlen(line) == 6 && line[5] == '\n')
			line[5] = '\0';
		if (ft_strlen(line) != 5 || (ft_strlen(line) == 5 && (line[4] == '\0' || line[4] == '\n')))
		{
			close(fd);
			return (-2);
		}
		if (vector_add(word_list, &line, 1) == -1)
		{
			free(line);
			free_dic(word_list);
			close(fd);
			return (-1);
		}
		line = get_next_line(fd);
	}
	close(fd);
	if (errno != 0)
	{
		free_dic(word_list);
		return (-1);
	}
	if (word_list->num_elements < DIC_MIN_SIZE)
		return (-3);
	return (0);
}
