/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_get_str_to_ifs.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 22:37:08 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/31 09:50:02 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "expansion.h"
#include "library.h"

bool	export_is_symbol(char c);

static size_t	expand_get_string_to_dollar_or_symbol_size(char *word)
{
	size_t	size;

	size = 0;
	while (word[size] != '\0' && (!export_is_symbol(word[size])) && \
			(!ft_isspace(word[size])))
		size++;
	return (size);
}

char	*expand_get_string_to_dollar_or_symbol(char **word)
{
	char	*str;
	size_t	size;
	size_t	i;

	size = expand_get_string_to_dollar_or_symbol_size(*word);
	i = 0;
	str = try_calloc(size + 1, sizeof(char));
	while (i < size)
	{
		str[i] = (*word)[i];
		i++;
	}
	(*word) += size;
	return (str);
}

static size_t	expand_get_size_str_to_ifs(char *word, char *ifs)
{
	size_t	i;

	i = 0;
	while (word[i] != '\0' && expand_is_str_in_char(ifs, word[i]))
	{
		if (word[i] == '\'')
		{
			while (word[++i] == '\'')
			{
				if (word[i] == '\0')
					return (i);
			}
		}
		i++;
	}
	return (i);
}

char	*expand_get_type_to_ifs(char **type, char *word)
{
	char	*new_type;
	size_t	i;

	i = 0;
	new_type = try_calloc(ft_strlen(word) + 1, sizeof(char));
	while (word[i] != '\0')
	{
		new_type[i] = (*type)[i];
		*type++;
		i++;
	}
	return (new_type);
}

char	*expand_get_str_to_ifs(char **word, char *ifs)
{
	char	*str;
	size_t	size;
	size_t	i;

	i = 0;
	size = expand_get_size_str_to_ifs(*word, ifs);
	str = try_calloc(size + 1, sizeof(char));
	while (i < size)
	{
		str[i] = (*word)[i];
		i++;
	}
	*word += size;
	return (str);
}
