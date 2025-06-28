/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_in_word_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 07:22:29 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/28 07:22:31 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	is_in_word_list(t_vector *word_list, char *word)
{
	size_t	i;
	char	*line;

	i = 0;
	while (i < word_list->num_elements)
	{
		line = *(char **)(get_vector_value(word_list, i));
		if (ft_strncmp(line, word, 5) == 0)
			return (true);
		++i;
	}
	return (false);
}
