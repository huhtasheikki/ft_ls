/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 11:51:15 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/26 22:01:25 by hhuhtane         ###   ########.fr       */
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
	t_dirlst	*temp;
	t_list		*t1;
	t_file		*f1;

	ft_start_init(&ls_cont);
	ft_parse_args(argc, argv, &ls_cont);
	temp = ls_cont.dirs;
	ft_putendl("While alkaa:");
	while (temp->next)
	{
		temp = temp->next;
		ft_printf("%s:\n", temp->d_name);
		t1 = temp->f_lst;
		mergesort_ls(&t1->next, &sort_name);
//		mergesort_ls(&t1->next, &sort_mtime);
		while(t1->next)
		{
			t1 = t1->next;
			f1 = t1->content;
//			ft_printf("%d ", (f1->st_mode & S_IFDIR));
			print_modes(f1->st_mode);
			ft_printf("%s ", f1->mode_str);
			ft_printf("%d ", f1->st_nlink);
			ft_printf("%s ", f1->owner_str);
			ft_printf("%s ", f1->group_str);
			ft_printf("%d ", f1->st_size);
			ft_printf("%s ", f1->lastmod_str);
//			ft_printf("%.12s ", ctime(&f1->f_stat->st_mtime) + 4);
			ft_printf(" %s\n", f1->name_str);
		}
	}
	ft_print_ls(&ls_cont);
	ft_printf("options=%ld\n", ls_cont.options);
	while(1);
	return (0);
}
