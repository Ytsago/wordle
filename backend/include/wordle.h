/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 05:46:04 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/28 05:46:06 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORDLE_H
# define WORDLE_H

# include "libft.h"

char	*get_random_word(t_vector *word_list);
int		run_wordle(t_vector *word_list, char *word_to_find);
bool	is_in_word_list(t_vector *word_list, char *word);
int		*get_feedback(char *guess, char *target);
void	free_dic(t_vector *word_list);
int	parse_file(t_vector *word_list, char *parse_file);

#endif
