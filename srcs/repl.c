/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:35:51 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/29 00:52:55 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenize.h"
#include "parse.h"
#include "exec_command.h"
#include "heredoc.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void	reset_vars(t_data *d);
void	end_command(char *line, t_data *d);
void	eof(t_data *d);
void	set_signal_readline(t_data *d);
void	get_signal_num(t_data *d);
void	ignore_signal(t_data *d);

int	g_signal_num = 0;

static void	add_line_history(char *line)
{
	if (line[0] == NULL_CHAR)
		return ;
	add_history(line);
}

static bool	is_only_spaces(char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line))
			return (false);
		line++;
	}
	return (true);
}

static char	*read_line(t_data *d)
{
	char	*line;

	line = readline(PROMPT);
	get_signal_num(d);
	if (line == NULL)
		eof(d);
	if (is_only_spaces(line))
		return (NULL);
	add_line_history(line);
	return (line);
}

static void	free_all_data(t_token *token, t_ast *ast)
{
	token_free_all_tokens(token);
	(void)ast;
}

void	read_eval_print_loop(t_data *d)
{
	char	*line;
	t_token	*token;
	t_ast	*ast;

	while (true)
	{
		reset_vars(d);
		set_signal_readline(d);
		line = read_line(d);
		ignore_signal(d);
		if (line == NULL)
		{
			end_command(line, d);
			continue ;
		}
		token = tokenize(line);
		// debug_print_token(token);
		ast = parse(&token,d);
		// debug_print_ast(ast);
		if (heredoc(ast, d))
			exec_command(ast, EXEC_START, d);
		free_all_data(token, ast);
		end_command(line, d);
	}
}
