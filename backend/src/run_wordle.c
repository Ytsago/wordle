/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_wordle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 06:33:22 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/28 06:33:24 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "wordle.h"

int	run_wordle(t_vector *word_list, char *word_to_find)
{
	int		i;
	char	*word;
	int		*result;

	i = 0;
	while (i < 6)
	{
		word = get_next_line(0);
		if (!word)
			return (-1);
		dprintf(2, "word : %s\n", word);
		if (ft_strlen(word) != 6 || !is_in_word_list(word_list, word))
		{
			ft_putstr_fd("Incorrect word\n", 2);
			free(word); // temp for test
			continue ;
		}
		if (ft_strncmp(word_to_find, word, 5) == 0)
			return (0);
		result = get_feedback(word, word_to_find);
		if (!result)
		{
			free(word); // temp for test
			perror("Error");
			return (-1);
		}
		dprintf(2, "%d%d%d%d%d\n", result[0], result[1], result[2], result[3], result[4]);
		free(result);
		free(word); // temp for test
		++i;
	}
	ft_putstr_fd("You lose, the word was : \"", 2);
	ft_putstr_fd(word_to_find, 2);
	ft_putstr_fd("\"\n", 2);
	return (0);
}
