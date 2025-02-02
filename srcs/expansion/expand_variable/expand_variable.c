/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:21:54 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/31 18:01:07 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

bool	expand_is_str_in_char(char *str, char c)
{
	if (str == NULL)
		return (false);
	while (*str != '\0')
	{
		if (*str == c)
			return (true);
		str++;
	}
	return (false);
}

bool	expand_is_variable_word(char *word)
{
	t_quote	f_quote;
	size_t	i;

	i = 0;
	if (word == NULL)
		return (false);
	while (word[i] != '\0')
	{
		f_quote = token_set_flag_quote(word[i]);
		if (f_quote == SINGLE_QUOTE_FLAG)
		{
			while (f_quote != token_set_flag_quote(word[++i]))
			{
				if (word[i] == '\0')
					return (false);
			}
		}
		else
		{
			if (word[i] == '$')
				return (true);
		}
		i++;
	}
	return (false);
}

void	expand_variable_word_list(t_word_list *word_list, t_data *d)
{
	if (expand_is_variable_word(word_list->word))
	{
		expand_get_expanded_token(&(word_list->word), &(word_list->type), d);
	}
}

void	expand_variable_redirect_list(t_redirect_list *redirect_list, t_data *d)
{
	char	*word;
	char	*ifs;

	ifs = envs_get_value("IFS", d->envs_hashmap);
	word = redirect_list->word;
	if (expand_is_variable_word(word))
	{
		expand_get_expanded_token(&(redirect_list->word), \
									&(redirect_list->type), d);
		if (expand_is_ambiguous_error(redirect_list->word, \
										redirect_list->type, ifs))
		{
			redirect_list->is_ambiguous_error = true;
			redirect_list->word = word;
		}
	}
}
