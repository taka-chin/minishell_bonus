/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:35:33 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/29 23:53:10 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static char *expand_convert_dollar_word_delimiter(char **word, t_data *d)
{
	char *expand_word;

	expand_word = *word;
	(*word)++;
	if (**word == '\0')
		return (try_strdup(expand_word));
	if (**word == '?')
		expand_word = expand_get_exit_status(word, d->exit_status);
	else
		expand_word = expand_get_expand_word(word, d->envs_hashmap);
	return (expand_word);
}

// typeを作る　voidにしてchar *token, char *typeにポインタ文字列入れる

static void	expand_get_expanded_word_delimiter(char **token, char **type, t_data *d)
{
	char	*tmp;
	char	*expand_word;
	char	*join_word;
	char	*join_type_word;

	join_word = NULL;
	join_type_word = NULL;
	tmp = *token;
	while (*tmp != '\0')
	{
		if (*tmp == '$')
		{
			expand_word = expand_convert_dollar_word_delimiter(&tmp, d);
			join_word = try_strjoin_free(join_word, expand_word);
			join_type_word = try_strjoin_free(join_type_word, token_get_type_word(expand_word, true));
			free(expand_word);
		}
		else
		{
			expand_word = expand_get_str_to_dollar(&tmp);
			join_word = try_strjoin_free(join_word, expand_word);
			join_type_word = try_strjoin_free(join_type_word, token_get_type_word(expand_word, false));
			free(expand_word);
		}
	}
	*token = join_word;
	*type = join_type_word;
}

void	expand_redirect_list(t_redirect_list **redirect_list, t_data *d)
{
	t_redirect_list *node;
	char			*ifs;
	bool			is_empty_ifs;
	

	node = *redirect_list;
	while (node != NULL)
	{
		if (node->re_type == PS_FILE && ft_strchr(node->word, '$'))
		{
			expand_variable_redirect_list(node, d);
			ifs = envs_get_value("IFS", d->envs_hashmap);
			is_empty_ifs = expand_is_empty_ifs(ifs);
				// exit(0);
			if (!node->is_ambiguous_error)
			{
				// printf("ok   %s\n", node->word);
				if (!is_empty_ifs && expand_is_word_splitting_word(node->word, node->type, ifs))
					expand_word_splitting_redirect_list(node, ifs);
				if (expand_is_delete_quotation_word(node->type))
					expand_delete_quotation_redirect_list(node);
			}
			// expand_filename(node);
			// expand_word_splitting_word_list(node, d);
			// expand_filename(node);
			// printf("type %s, word %s\n", node->type, node->word);
		}
		else if (node->re_type == PS_DELIMITER && ft_strchr(node->word, '$'))
		{
			//単純な展開クウォート削除も行わない関数作成
			expand_get_expanded_word_delimiter(&(node->word), &(node->type), d);
		}
		// exit(0);
		node = node->next;
	}
}

// bool expand_is_tokens(char *expand_word)
// {
// 	bool f_space;

// 	f_space = false;
// 	while (*expand_word != '\0')
// 	{
// 		if (f_space)
// 			return (true);
// 		if (ft_isspace(*expand_word))
// 			f_space = true;
// 		expand_word++;
// 	}
// 	return (false);
// }

// void expand_token_redirect_list(t_redirect_list *redirect_list, t_data *d, t_redirect_type is_quote)
// {
// 	char *expand_word;

// 	expand_word = expand_get_expanded_token(redirect_list->word, d);
// 	// 環境変数がない場合, トークンが複数に分かれる場合
// 	if (is_quote != PS_REDIRECT_DOUBLE_QUOTE &&
// 		(expand_word == NULL || expand_is_tokens(expand_word)))
// 	{
// 		free(expand_word);
// 		// token->is_abm_error = true;
// 	}
// 	else
// 	{
// 		// free(redirect_list->word);
// 		redirect_list->word = expand_word;
// 	}
// }

// void expand_variable_redirect_list(t_redirect_list *head, t_data *d)
// {
// 	t_redirect_list *node;

// 	node = expand_can_dollar_quote_string_redirect(&head);
// 	while (node != NULL)
// 	{
// 		if (node->re_type == TOKEN_SINGLE_QUOTE)
// 		{
// 			node = node->next;
// 			while (node->re_type != TOKEN_SINGLE_QUOTE)
// 				node = node->next;
// 		}
// 		if (node->type != TOKEN_SINGLE_QUOTE && ft_strchr(node->word, '$'))
// 			expand_token_redirect_list(node, d, node->re_type);
// 		node = node->next;
// 	}
// }