/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_is_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:27:37 by tterao            #+#    #+#             */
/*   Updated: 2023/08/15 17:13:51 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "library.h"

void	export_invalid_identifier(char *str, t_data *d);

bool	export_is_symbol(char c)
{
	return (c == '~' || c == '`' || c == '!' || c == '@' || c == '#'
		|| c == '$' || c == '%' || c == '^' || c == '&' || c == '*'
		|| c == '(' || c == ')' || c == '-' || c == '=' || c == '+'
		|| c == '[' || c == '{' || c == ']' || c == '}' || c == '\\'
		|| c == '|' || c == ';' || c == ':' || c == '\'' || c == '\"'
		|| c == ',' || c == '<' || c == '.' || c == '>' || c == '?'
		|| c == '/' || c == '?');
}

static bool	export_is_invalid_key(char *str, t_data *d)
{
	if (ft_isdigit(*str) || *str == '+' || *str == '=')
	{
		export_invalid_identifier(str, d);
		return (true);
	}
	while (*str != '=' && *str != '+' && *str != '\0')
	{
		if (export_is_symbol(*str))
		{
			export_invalid_identifier(str, d);
			return (true);
		}
		str++;
	}
	return (false);
}

static bool	export_is_invalid_operator(char *str, t_data *d)
{
	bool	plus_flag;

	plus_flag = false;
	while (*str != '\0')
	{
		if (!plus_flag && *str == '+')
		{
			str++;
			if (*str != '=')
			{
				export_invalid_identifier(str, d);
				return (true);
			}
			plus_flag = true;
			continue ;
		}
		str++;
	}
	return (false);
}

bool	export_is_error(char *str, t_data *d)
{
	if (export_is_invalid_key(str, d) || export_is_invalid_operator(str, d))
		return (true);
	return (false);
}
