/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_feedback.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 07:23:16 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/28 07:23:18 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*get_feedback(char *guess, char *target)
{
	int	*feedback;
	int	target_count[256];
	int	i;

	feedback = malloc(sizeof(int) * 5);
	if (!feedback)
		return (NULL);
	i = 0;
	while (i < 256)
		target_count[i++] = 0;
	i = 0;
	while (i < 5)
	{
		if (guess[i] == target[i])
			feedback[i] = 2;
		else
			feedback[i] = 0;
		++i;
	}
	i = 0;
	while (i < 5)
	{
		if (guess[i] != target[i])
			target_count[(unsigned char)target[i]]++;
		++i;
	}
	i = 0;
	while (i < 5)
	{
		if (feedback[i] == 0 && target_count[(unsigned char)guess[i]] > 0)
		{
			feedback[i] = 1;
			target_count[(unsigned char)guess[i]]--;
		}
		++i;
	}
	return (feedback);
}

