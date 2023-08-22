/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:02:01 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/22 13:13:51 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_execution.h"

void command_execution(t_ast *node, t_operator operator, t_data * d)
{
	static size_t i = 0;

	if (node->left_hand != NULL)
		command_execution(node->left_hand, node->type, &d);
	if (node->type == PS_LOGICAL_AND || node->type == PS_LOGICAL_OR)
		;
	else if (node->right_hand != NULL)
		command_execution(node->right_hand, operator, & d);
	else if (operator== START && node->right_hand != NULL)
		command_execution(node->right_hand, END, &d);
	i++;
	printf("num   %zu\n", i);
	// if (node->type == COMMAND)
	// {
	// 	bool	ret = do_redirection(node, &d);
	// 	if (ret == false && operator != LOGICAL_OR)
	// 	{
	// 		//エラー処理
	// 		//redirectionが失敗したらこのノードのコマンドを実行しない
	// 		//open readが失敗したときなど
	// 		return;
	// 	}
	// 	else if (ret == false && operator == LOGICAL_OR)//operator=LOGICAL_ORの場合、次のコマンドを実行
	// 	{
	// 		exec_wait_child_process(node);
	// 		command_execution(node->right_hand, operator, &d);
	// 	}
	// 	else if (operator == PIPE)
	// 		exec_pipe(node);
	// 	else if (operator == LOGICAL_AND)
	// 	{
	// 		if (exec_l_and(node))
	// 			command_execution(node->right_hand, operator, &d);
	// 	}
	// 	else if (operator == LOGICAL_OR)
	// 	{
	// 		if (exec_l_or(node));
	// 			command_execution(node->right_hand, operator, &d);
	// 	}
	// 	else if (operator == START && exec_is_builtin(node))//operatorなしかつ実行するのはbuiltinのみなので、親プロセスで実行
	// 		return (builtin(node, NULL, &d));//builtin.hの関数
	// 	else
	// 		exec_fork(node, &d);
	// }
	// if (operator == START)
	// 	exec_wait_child_process(node, &d);
}

int main(void)
{
	extern const char **environ;
	t_data data;

	t_ast *node;
	t_ast *left_node;
	t_ast *right_node;

	t_word_list *word_list_left;
	t_word_list *word_list_right;

	t_redirect_list_list *redirect_list_left;
	t_redirect_list_list *redirect_list_right;

	word_list_left = debug_new_word_list("$", 0, WORD);
	word_list_left->next = debug_new_word_list("\'", 1, TOKEN_SINGLE_QUOTE);
	word_list_left->next->next = debug_new_word_list("echo", 1, WORD);
	word_list_left->next->next->next = debug_new_word_list("\'", 1, TOKEN_SINGLE_QUOTE);
	word_list_left->next->next->next->next = debug_new_word_list("aaaa", 1, WORD);
	word_list_left->next->next->next->next->next = debug_new_word_list("bat", 1, WORD);

	redirect_list_left = debug_new_redirect_list("<", 2, PS_REDIRECTING_INPUT);
	redirect_list_left->next = debug_new_redirect_list("$out", 3, PS_FILE);

	left_node = debug_new_ast(debug_new_command(word_list_left, redirect_list_left), PS_COMMAND);
	;
	word_list_right = debug_new_word_list("echo", 0, WORD);
	word_list_right->next = debug_new_word_list("ok", 0, WORD);
	word_list_right->next->next = debug_new_word_list("$", 1, WORD);
	word_list_right->next->next->next = debug_new_word_list("\"", 2, TOKEN_DOUBLE_QUOTE);
	word_list_right->next->next->next->next = debug_new_word_list("$word", 2, WORD);
	word_list_right->next->next->next->next->next = debug_new_word_list("\"", 2, TOKEN_DOUBLE_QUOTE);

	redirect_list_right = debug_new_redirect_list(">", 3, PS_REDIRECTING_OUTPUT);
	redirect_list_right->next = debug_new_redirect_list("$PATH", 4, PS_FILE);

	right_node = debug_new_ast(debug_new_command(word_list_right, redirect_list_right), PS_COMMAND);

	node = debug_new_ast(NULL, PS_PIPE);
	node->left_hand = left_node;
	node->right_hand = right_node;

	data.exit_status = 0;
	envs_init(environ, &data);
	// expansion(node, &data);

	// debug_printf_word_list(node->left_hand->command_list->word_list);
	// debug_printf_word_list(node->right_hand->command_list->word_list);

	// debug_printf_redirect(node->left_hand->command_list->redirect_list);
	// debug_printf_redirect(node->right_hand->command_list->redirect_list);

	// if (word_list_left == NULL)
	// 	printf("ok");
	// printf("%s\n", node->command_list->word_list->word);
	// debug_free_word_list(node->left_hand->command_list->word_list);
	// debug_free_word_list(node->right_hand->command_list->word_list);
	// debug_free_word_list(word_list_right);
	return (0);
}