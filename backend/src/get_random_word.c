/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_random_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 06:20:58 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/28 06:21:00 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*get_random_word(t_vector *word_list)
{
	int	random_value;

	random_value = (int)(((float)rand() \
		/ (float)RAND_MAX) * word_list->num_elements);
	return (*(char **)(get_vector_value(word_list, random_value)));
}
