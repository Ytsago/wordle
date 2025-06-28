/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 05:45:29 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/28 14:13:13 by your_username    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "libft.h"
#include "wordle.h"
#include <SDL2/SDL.h>


int	main(int argc, char **argv)
{
	t_vector	word_list;
	int			return_val;

	srand(time(NULL));
	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./wordle [word list]\n", 2);
		return (1);
	}
	return_val = parse_file(&word_list, argv[1]);
	if (return_val == -1)
	{
		perror("Error");
		return (1);
	}
	if (return_val == -2)
	{
		ft_putstr_fd("Error: One or more word size different than 5\n", 2);
		return (2);
	}
	if (return_val == -3)
	{
		ft_putstr_fd("Error: Less than 10 word present in given file\n", 2);
		free_dic(&word_list);
		return (3);
	}
	run_wordle(&word_list, get_random_word(&word_list));
	free_dic(&word_list);
}
