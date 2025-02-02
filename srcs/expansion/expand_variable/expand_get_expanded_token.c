/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_get_expanded_token.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 20:02:21 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/31 18:32:14 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void	expand_get_joined(char **expand, char **join_word, \
							char **join_type, bool is_expand)
{
	char	*type;

	type = token_get_type_word(*expand, is_expand);
	*join_word = try_strjoin_free(*join_word, *expand);
	*join_type = try_strjoin_free(*join_type, type);
	free(*expand);
	*expand = NULL;
	free(type);
}

char	*expand_get_expand_word(char **word, t_envs **envs)
{
	char	*target_word;
	char	*target_value;

	target_word = expand_get_string_to_dollar_or_symbol(word);
	target_value = envs_get_value(target_word, envs);
	free(target_word);
	target_word = NULL;
	return (target_value);
}

char	*expand_convert_dollar_word(char **word, t_data *d)
{
	char	*expand_word;
	t_quote	f_quote;

	expand_word = *word;
	(*word)++;
	f_quote = token_set_flag_quote((*word)[0]);
	if (**word == '\0')
		return (try_strdup(expand_word));
	if (f_quote == SINGLE_QUOTE_FLAG || f_quote == DOUBLE_QUOTE_FLAG)
	{
		expand_word = expand_get_delete_dollar_quote(word, f_quote);
	}
	else if (**word == '?')
	{
		expand_word = expand_get_exit_status(word, d->exit_status);
	}
	else
	{
		expand_word = expand_get_expand_word(word, d->envs_hashmap);
	}
	return (expand_word);
}

void	expand_get_expanded_token(char **token, char **type, t_data *d)
{
	char	*tmp;
	char	*expand_word;
	char	*join_word;
	char	*join_type;

	join_word = NULL;
	join_type = NULL;
	tmp = *token;
	while (*tmp != '\0')
	{
		if (*tmp == '$')
		{
			expand_word = expand_convert_dollar_word(&tmp, d);
			expand_get_joined(&expand_word, &join_word, &join_type, true);
		}
		else
		{
			expand_word = expand_get_str_to_dollar(&tmp);
			expand_get_joined(&expand_word, &join_word, &join_type, false);
		}
	}
	free(*token);
	free(*type);
	*token = join_word;
	*type = join_type;
}
