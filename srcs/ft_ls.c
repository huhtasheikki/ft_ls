/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 11:51:15 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/30 12:03:37 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_start_init(t_ls *ls_cont)
{
	ls_cont->options = 0;
	ft_strncpy(ls_cont->options_str, LS_OPTIONS, LS_OPTIONS_SIZE + 1);
	if (!(ls_cont->dirs = (t_dirlst*)malloc(sizeof(t_dirlst))))
		error_ls(NULL, MALLOC_ERROR);
}

int		main(int argc, char **argv)
{
	t_ls	ls_cont;

	ft_start_init(&ls_cont);
	ft_parse_args(argc, argv, &ls_cont);
	ft_print_ls(&ls_cont);
	return (0);
}
