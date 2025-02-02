/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:54:09 by tterao            #+#    #+#             */
/*   Updated: 2023/08/31 18:15:57 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

char	*token_get_is_expand_type_word(char *word, size_t len);
char	token_set_type_word(char c);

static char	*get_type_word(char *word, size_t len)
{
	char	*type_word;
	size_t	i;
	t_quote	f_quote;

	type_word = try_calloc((len + 1), sizeof(char));
	i = 0;
	while (word[i] != '\0')
	{
		f_quote = token_set_flag_quote(word[i]);
		type_word[i] = token_set_type_word(word[i]);
		while (f_quote != DEFAULT)
		{
			i++;
			if (word[i] == '\0')
				return (type_word);
			else if (f_quote == token_set_flag_quote(word[i]))
			{
				type_word[i] = token_set_type_word(word[i]);
				break ;
			}
			type_word[i] = '0';
		}
		i++;
	}
	return (type_word);
}

char	*token_get_type_word(char *word, bool is_expand)
{
	char	*type_word;
	size_t	len;

	if (word == NULL)
		return (NULL);
	len = ft_strlen(word);
	if (is_expand)
		type_word = token_get_is_expand_type_word(word, len);
	else
		type_word = get_type_word(word, len);
	return (type_word);
}
