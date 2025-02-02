/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:54:13 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/31 12:01:53 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void	redirect_free(t_redirect_list *redirect)
{
	free(redirect);
}

void	redirect_delete_head(t_redirect_list **head)
{
	t_redirect_list	*node;
	t_redirect_list	*tmp;

	node = *head;
	if (node == NULL)
		return ;
	tmp = node->next;
	redirect_free(node);
	*head = tmp;
}

void	redirect_delete_tail(t_redirect_list **head)
{
	t_redirect_list	*node;

	node = *head;
	if (node == NULL || node->next == NULL)
		return ;
	while (node->next->next != NULL)
		node = node->next;
	redirect_free(node->next);
	node->next = NULL;
}

void	redirect_delete_target(t_redirect_list **head, t_redirect_list *target)
{
	t_redirect_list	*tmp;
	t_redirect_list	*node;

	node = *head;
	while (node->next != NULL && ft_strcmp(node->next->word, target->word))
		node = node->next;
	if (node->next != NULL)
	{
		tmp = node->next->next;
		redirect_free(node->next);
		node->next = tmp;
	}
}
