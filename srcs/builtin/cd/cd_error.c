/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:37:30 by tterao            #+#    #+#             */
/*   Updated: 2023/08/29 20:40:23 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "library.h"
#include <stdlib.h>
#define ARGS_NUM 2

bool	cd_iserror(char **argv)
{
	size_t	size;

	size = 0;
	while (argv[size] != NULL)
		size++;
	return (size > ARGS_NUM);
}

void	cd_put_error_too_many_args(t_data *d)
{
	const char	*msg = "cd: too many arguments\n";

	d->exit_status = EXIT_FAILURE;
	try_write(STDERR_FILENO, msg, ft_strlen(msg), d);
}

void	cd_put_error_no_pwd(char *path, t_data *d)
{
	char	*msg;

	d->exit_status = EXIT_FAILURE;
	msg = try_strdup("chdir: error retrieving current directory: getcwd: "
			"cannot access parent directories: Permission denied\ncd: ");
	msg = try_strjoin_free(msg, path);
	msg = try_strjoin_free(msg, ": Permission denied\n");
	free(path);
	try_write(STDERR_FILENO, msg, ft_strlen(msg), d);
	free(msg);
}

void	cd_put_error_file(const char *og_path, t_data *d)
{
	char	*msg;

	msg = try_strjoin("cd: ", og_path);
	msg = try_strjoin_free(msg, ": Not a directory\n");
	try_write(STDERR_FILENO, msg, ft_strlen(msg), d);
	free(msg);
}

void	cd_put_error_file_dir(const char *og_path, t_data *d)
{
	char	*msg;

	msg = try_strjoin("cd: ", og_path);
	msg = try_strjoin_free(msg, ": No such file or directory\n");
	try_write(STDERR_FILENO, msg, ft_strlen(msg), d);
	free(msg);
}
