/* ************************************************************************** */
/*                                                                            */

/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:35:51 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/06 13:35:43 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenize.h"
#include "parse.h"
#include "exec_command.h"
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
	t_token *token;
	t_ast *pasre_node;
	// t_word_list *word_p;
	// t_redirect_list *redirect_p;
	t_data d;

	extern const char	**environ;

	envs_init(environ, &d);
	d.syntax_flag = false;
	while (true)
	{
		line = read_line();
		if (line == NULL)
			break ;
		token = tokenize(line);
		// debug_print_token(token);
		pasre_node = parse(&token,&d);
		exec_command(pasre_node, EXEC_START, &d);
		// word_p = pasre_node->command_list->word_list;
		// redirect_p = pasre_node->command_list->redirect_list;
		// exec_make_filepath(pasre_node, &d);
		// while(word_p)
		// {
		// 	printf("word:%s\n",word_p->word);
		// 	word_p = word_p->next;
		// }
		// while(redirect_p)
		// {
		// 	printf("redirect type:%d ",redirect_p->type);
		// 	printf("redirect:%s\n",redirect_p->word);
		// 	redirect_p = redirect_p->next;
		// }
		// printf("line          %s\n", line);
		// printf("start 0 end 3 %s\n", ft_substr(line, -1, 3));
		// printf("start 2 end 7 %s\n", ft_substr(line, 2, 7));

		free(line);
	}
}
