/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:32:54 by hsawamur          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/08/22 13:23:36 by hsawamur         ###   ########.fr       */
=======
/*   Updated: 2023/08/16 09:41:02 by hsawamur         ###   ########.fr       */
>>>>>>> 106-単語分割
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void expand_token_word_list(t_word_list *word_list, t_data *d)
{
	char *expand_word;

	expand_word = expand_get_expanded_token(word_list->word, d);
	word_list->word = expand_word;
}

void expand_variable_word_list(t_word_list **head, t_data *d)
{
	t_word_list *node;

	node = expand_can_dollar_quote_string_word_list(head);
	while (node != NULL)
	{
		if (node->type == TOKEN_SINGLE_QUOTE)
		{
			node = node->next;
			while (node->type != TOKEN_SINGLE_QUOTE)
				node = node->next;
		}
		if (node->type == WORD && ft_strchr(node->word, '$'))
			expand_token_word_list(node, d);
		node = node->next;
	}
}
