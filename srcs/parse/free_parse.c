/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 22:55:37 by tyamauch          #+#    #+#             */
/*   Updated: 2023/08/31 17:19:44 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	word_list_free(t_word_list *head)
{
	t_word_list	*node;
	t_word_list	*tmp;

	node = head;
	while (node != NULL)
	{
		tmp = node->next;
		free(node->word);
		free(node->type);
		free(node);
		node = tmp;
	}
}

static void	redirect_list_free(t_redirect_list *head)
{
	t_redirect_list	*node;
	t_redirect_list	*tmp;

	node = head;
	while (node != NULL)
	{
		tmp = node->next;
		free(node->word);
		free(node->type);
		free(node);
		node = tmp;
	}
}

static void	*ast_free_right_node(t_ast *node)
{
	word_list_free(node->command_list->word_list);
	redirect_list_free(node->command_list->redirect_list);
	free(node->command_list);
	free(node);
	return (NULL);
}

void	*ast_free_all_nodes(t_ast *node)
{
	if (node != NULL && node->left_hand != NULL)
		ast_free_all_nodes(node->left_hand);
	if (node != NULL && node->right_hand != NULL)
		ast_free_all_nodes(node->right_hand);
	if (node->type == PS_COMMAND)
	{
		word_list_free(node->command_list->word_list);
		redirect_list_free(node->command_list->redirect_list);
	}
	free(node->command_list);
	free(node);
	return (NULL);
}

void	*ast_free_right_left_nodes(t_ast *left_node, t_ast *right_node)
{
	ast_free_right_node(right_node);
	ast_free_all_nodes(left_node);
	return (NULL);
}
