/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:58:27 by tterao            #+#    #+#             */
/*   Updated: 2023/08/29 16:15:08 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void	signal_put_error(const char *f, t_data *d);

void	set_signal_exec(t_data *d)
{
	struct sigaction	act;

	act.sa_handler = SIG_DFL;
	act.sa_flags = 0;
	if (sigemptyset(&act.sa_mask) == -1)
		return (signal_put_error("sigemptyset", d));
	if (sigaddset(&act.sa_mask, SIGINT))
		return (signal_put_error("sigaddset", d));
	if (sigaddset(&act.sa_mask, SIGQUIT))
		return (signal_put_error("sigaddset", d));
	if (try_sigaction(SIGINT, &act, NULL, d) == -1)
		return ;
	if (try_sigaction(SIGQUIT, &act, NULL, d) == -1)
		return ;
}
