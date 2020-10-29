/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 11:51:15 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/29 10:53:24 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_start_init(t_ls *ls_cont)
{
	ls_cont->options = 0;
	ft_strncpy(ls_cont->options_str, LS_OPTIONS, LS_OPTIONS_SIZE + 1);
	if (!(ls_cont->file_lst = ft_lstnew(NULL, 0)))
		error_ls(NULL, MALLOC_ERROR);
	if (!(ls_cont->dirs = (t_dirlst*)malloc(sizeof(t_dirlst))))
		error_ls(NULL, MALLOC_ERROR);
}

int		main(int argc, char **argv)
{
	t_ls	ls_cont;
//	t_dirlst	*temp;
//	t_list		*t1;
//	t_file		*f1;

	ft_start_init(&ls_cont);
	ft_parse_args(argc, argv, &ls_cont);

//	sort_ls_lists(&ls_cont);
	ft_print_ls(&ls_cont);

/*
	temp = ls_cont.dirs;
	while (temp->next)
	{
		temp = temp->next;
		ft_printf("%s:\n", temp->d_name);
		ft_printf("total %d\n", temp->d_blocks);
		t1 = temp->f_lst;
		while(t1->next)
		{
			t1 = t1->next;
			f1 = t1->content;
			print_modes(f1->st_mode);
			ft_printf("%s ", f1->mode_str);
			ft_printf("%*d ", temp->nl_size, f1->st_nlink);
			ft_printf("%-*s  ", temp->o_size, print_owner(f1->st_uid, f1->name_str));
			ft_printf("%-*s  ", temp->g_size, print_group(f1->st_gid, f1->name_str));
			ft_printf("%*d ", temp->s_size, f1->st_size);
			print_mtime(f1->mtime, f1->name_str);
			ft_printf("%s\n", f1->name_str);
		}
	}
*/

//	ft_print_ls(&ls_cont);
//	ft_printf("options=%ld\n", ls_cont.options);
	return (0);
}
