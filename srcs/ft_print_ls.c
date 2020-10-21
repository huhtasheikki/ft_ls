/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 14:27:49 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/21 17:15:31 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		get_sizes(t_list *files)
{
	t_list		*temp;
	t_file		*file;
//	t_stat		*buf;
	int			ret;

	ret = 0;
	temp = files->next;
	while (temp->next)
	{
		file = temp->content;
		ret += file->f_stat->st_blocks;
		temp = temp->next;
	}
	return (ret);
}

void	print_file_info(t_ls *ls_cont)
{
	t_list		*temp;
	t_file		*file;

	temp = ls_cont->dirs->next->f_lst;
	file = temp->content;
	while (temp->next)
	{
		temp = temp->next;
		file = temp->content;
		ft_printf("%s ", get_modes(file->f_stat));
		ft_printf(" %s ", get_links(file->f_stat));
		ft_printf("%s ", get_owner(file->f_stat, file->name_str));
		ft_printf("%s ", get_group(file->f_stat, file->name_str));
		ft_printf("%s ", get_file_size(file->f_stat));
		ft_printf("%.12s ", ctime(&file->f_stat->st_mtime) + 4);
		ft_printf("%s", file->name_str);
		ft_printf("\n");
	}
}

void	ft_long_format(t_ls *ls_cont)
{
	t_dirlst	*dirs;

	dirs = ls_cont->dirs->next;
	while (dirs)
	{
		ft_printf("%s:\n", dirs->d_name);
		ft_printf("total %d\n", get_sizes(dirs->f_lst));
		print_file_info(ls_cont);
		dirs = dirs->next;
	}
}

void	ft_print_ls(t_ls *ls_cont)
{
//	t_file		*f;

//	f = ls_cont->dirs->next->f_lst->next->content;
//	ft_printf("print_ls size:%d\n", f->f_stat->st_size);
	if ((ls_cont->options >> 19) & 1)
		ft_long_format(ls_cont);
//	ft_printf("testi\n");
}
