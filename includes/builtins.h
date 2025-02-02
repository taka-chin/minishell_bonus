/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:42:06 by tterao            #+#    #+#             */
/*   Updated: 2023/08/27 15:39:11 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "init.h"
# include "parse.h"

void	builtin(t_ast *node, int *pipefd, bool is_parent_process, t_data *d);
void	builtin_echo(char **argv, t_data *d);
char	**builtin_cd(char **argv, t_data *d);
void	builtin_pwd(t_data *d);
void	builtin_export(char **argv, t_data *d);
void	builtin_unset(char **argv, t_data *d);
void	builtin_env(char **argv, t_data *d);
void	builtin_exit(char **argv, t_data *d);

#endif
