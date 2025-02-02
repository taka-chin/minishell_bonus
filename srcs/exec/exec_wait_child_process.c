/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wait_child_process.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:41:12 by tterao            #+#    #+#             */
/*   Updated: 2023/08/31 09:24:01 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_command.h"
#include "library.h"
#define SIGNAL_EXITSTATUS 128
#define SIGINT_EXITSTATUS 130
#define SIGQUIT_EXITSTATUS 131

void	put_sigquit_line(t_data *d)
{
	const char	*msg = "Quit: 3\n";

	try_write(STDERR_FILENO, msg, ft_strlen(msg), d);
}

static void	exec_wait_child_node(t_ast *node, t_data *d)
{
	if (node->left_hand != NULL && node->type != PS_LOGICAL_AND
		&& node->type != PS_LOGICAL_OR)
		exec_wait_child_process(node->left_hand, d);
	if (node->right_hand != NULL)
		exec_wait_child_process(node->right_hand, d);
}

/**
 * @brief この関数は、第一引数で与えられたnodeより下のnodeの子プロセスを待ち、終了ステータスを取得する。
 *
 * 第一引数で与えられたnode以下のコマンドをwaitpid()で待ち、終了ステータスを取得する。
 * &&, ||のnodeが出現した場合、そのnodeより左下のnodeは待たない。（既にそれらの子プロセスは終了しているため）
 *
 * @param node 構文木のnode
 */
void	exec_wait_child_process(t_ast *node, t_data *d)
{
	int		status;

	exec_wait_child_node(node, d);
	if (node->type != PS_COMMAND)
		return ;
	if (node->command_list->pid == -1 && d->exit_status != SIGINT_EXITSTATUS
		&& d->exit_status != SIGQUIT_EXITSTATUS)
		d->exit_status = EXIT_FAILURE;
	else if (node->command_list->pid != -1)
	{
		if (try_waitpid(node->command_list->pid, &status, 0, d) == -1)
			return ;
		if (WIFSIGNALED(status))
			d->exit_status = SIGNAL_EXITSTATUS + WTERMSIG(status);
		else if (WIFEXITED(status))
			d->exit_status = WEXITSTATUS(status);
	}
	if (d->exit_status == SIGINT_EXITSTATUS)
		d->sigint_flag = true;
}
