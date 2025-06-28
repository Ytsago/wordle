/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_dic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 07:29:17 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/28 07:29:19 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	free_dic(t_vector *word_list)
{
	size_t	i;
	char	*line;

	i = 0;
	dprintf(2, "%zu\n", word_list->num_elements);
	while (i < word_list->num_elements)
	{
		line = *(char **)(get_vector_value(word_list, i));
		free(line);
		++i;
	}
	free_vector(word_list);
}
