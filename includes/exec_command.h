/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:26 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/28 22:55:54 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_COMMAND_H
# define EXEC_COMMAND_H

# include <stdbool.h>
# include "init.h"
# include "parse.h"

typedef enum e_operator
{
	EXEC_START,
	EXEC_END,
	EXEC_PIPE,
	EXEC_LOGICAL_AND,
	EXEC_LOGICAL_OR,
}	t_operator;

enum e_pipefd
{
	R = 0,
	W = 1,
};

enum e_exit_status
{
	COMMAND_NOT_EXECUTABLE = 126,
	COMMAND_NOT_FOUND = 127,
};

/**
 * @brief この関数はコマンドを実行する
 *
 * 第一引数の構文木nodeのタイプがコマンドの場合、node->command_listをコマンドとして、実行する
 * 第二引数のoperatorはコマンドの出力先を指定する。left_handにはnode->typeを渡し、
 * right_handには上のnodeから引き継いだoperatorを渡す
 * 一番初めのnode（初めにcommand_executionを呼ぶとき）は、operatorはEXEC_STARTになる
 * 一番最後に実行されるnodeのoperatorはEXEC_ENDになる
 * 第三引数のdは環境変数と終了ステータスを管理する
 *
 * @param node 構文木のnode
 * @param operator 構文木nodeの一つ上のnodeから引き継ぐoperator
 * @param d 環境変数と終了ステータス
 */
void	exec_command(t_ast *node, t_operator operator, t_data *d);

/**
 * @brief この関数はredirectionを実行する
 *
 * node->command_list->redirect_listを実行する
 * heredocの場合、heredocの文字列を標準入力に設定する
 * outputの場合、node->command_list->fdにopenしたfdを設定する
 * inputの場合、fileをopenし、readした文字列を標準入力に設定する
 *
 * @param operator
 * @param node 構文木のnode
 * @param d 環境変数と終了ステータス
 * @return true すべてのredirectionが問題なく成功した場合、trueを返す
 * @return false redirectionを失敗したタイミングで、この関数の処理を終了し、falseを返す
 *
 */
bool	exec_do_redirection(t_ast *node, t_data *d);

/**
 * @brief この関数はforkを実行し、子プロセスを生成する。
 *
 * 子プロセスのidをnode->command_list->pidに代入する。
 *
 * @param node 構文木のnode
 * @param d 環境変数と終了ステータス
 */
void	exec_fork(t_ast *node, t_data *d);

/**
 * @brief この関数はforkを実行し、子プロセスを生成する。親プロセスは子プロセスの実行結果を受け取る。
 *
 * pipe関数を使用して、プロセス間通信を行うための、fdを二つ用意する。
 * pipefdを通じて、子プロセスの実行結果を親プロセスの標準入力に設定する。
 * 親プロセスで、pipefdをcloseする。
 * 子プロセスのidをnode->command_list->pidに代入する。
 *
 * @param node 構文木のnode
 * @param d 環境変数と終了ステータス
 */
void	exec_pipe(t_ast *node, t_data *d);

/**
 * @brief この関数は子プロセス内でコマンドを実行する。
 *
 * node->command_list->fdに、コマンドを出力する。
 * pipefdがNULL出ないとき、かつfd_typeがSTDOUTの場合、pipefd[W]にコマンドを出力する。
 *
 * @param node 構文木のnode
 * @param pipefd pipeがない場合は、NULLが与えられる
 * @param d 環境変数と終了ステータス
 */
void	exec_child_process(t_ast *node, int *pipefd, t_data *d);

/**
 * 	@brief この関数は、commandのpathを取得する。
 *
 * commandの絶対pathを取得する。
 *
 * @param node 構文木のnode
 * @param d 環境変数と終了ステータス
 * @return char* commandのpath
 */
char	*exec_make_filepath(t_ast *node, t_data *d);

/**
 * @brief この関数はコマンド実行の二次元配列（argv）を作成する。
 *
 * node->command_list->word_listからコマンドを作成する。
 *
 * @param node 構文木のnode
 * @return char** コマンド実行の二次元配列（argv）
 */
char	**exec_make_argv(t_ast *node);

/**
 * @brief この関数は、第一引数で与えられたnodeより下のnodeの子プロセスを待ち、終了ステータスを取得する。
 *
 * 第一引数で与えられたnode以下のコマンドをwaitpid()で待ち、終了ステータスを取得する。
 * &&, ||のnodeが出現した場合、そのnodeとそのnodeより下のnodeは待たない。（既にそれらのプロセスは終了しているため）
 *
 * @param node 構文木のnode
 */
void	exec_wait_child_process(t_ast *node, t_data *d);

/**
 * @brief この関数は、コマンドがbuiltinか判定する
 *
 * node->command_list->word_listがbuiltinか判定する。
 *
 * @param node 構文木のnode
 * @param d 環境変数と終了ステータス
 * @return true builtinの場合、trueを返す
 * @return false builtinde出ない場合、falseを返す
 */
bool	exec_is_builtin(t_ast *node);

void	exec_free_argv(char **argv);

#endif
