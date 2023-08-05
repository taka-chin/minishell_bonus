/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:35:51 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/04 15:54:39 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenize.h"
#include "library.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <stdlib.h>

static void	add_line_history(char *line)
{
	if (line[0] == NULL_CHAR)
		return ;
	add_history(line);
}

static char	*read_line()
{
	char	*line;

	line = readline(PROMPT);
	if (!line)
		return (NULL);
	add_line_history(line);
	return (line);
}

void	read_eval_print_loop()
{
	char	*line;

	while (true)
	{
		line = read_line();
		if (line == NULL)
			break ;
		debug_print_token(tokenize(line));
		// printf("line          %s\n", line);
		// printf("start 0 end 3 %s\n", ft_substr(line, -1, 3));
		// printf("start 2 end 7 %s\n", ft_substr(line, 2, 7));
		free(line);
	}
}
