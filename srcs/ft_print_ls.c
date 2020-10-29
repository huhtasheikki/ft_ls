/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 14:27:49 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/28 17:41:30 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
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
	t_file		*f;

	temp = ls_cont->dirs->next->f_lst;
	f = temp->content;
	while (temp->next)
	{
		temp = temp->next;
		f = temp->content;
		ft_printf("%s ", f->mode_str);
//		ft_printf("%s ", get_modes(f->f_stat, f->mode_str));
//		f->links_str = get_links(f->f_stat, f->links_str);
		ft_printf(" %s ", f->links_str);
//		f->owner_str = get_owner(f->f_stat, f->name_str, f->owner_str);
		ft_printf("%s ", f->owner_str);
//		f->group_str = get_group(f->f_stat, f->name_str, f->group_str);
		ft_printf("%s ", f->group_str);
//		f->size_str = get_file_size(f->f_stat);
		ft_printf("%s ", f->size_str);
		ft_printf("%.12s ", ctime(&f->f_stat->st_mtime) + 4);
		ft_printf("%s", f->name_str);
		ft_printf("\n");
	}
}
*/

void	print_l_format(t_file *f, t_dirlst *dir, t_ls *ls_cont)
{
	print_modes(f->st_mode);
	ft_printf(" %*d ", dir->nl_size, f->st_nlink);
	if (!(ls_cont->options & G_FLAG))
		ft_printf("%-*s  ", dir->o_size, print_owner(f->st_uid, f->name_str));
	if (!(ls_cont->options & (1ULL << O_FLAG_I)))
		ft_printf("%-*s  ", dir->g_size, print_group(f->st_gid, f->name_str));
	ft_printf("%*d ", dir->s_size, f->st_size);
	if (ls_cont->options & (1ULL << U_FLAG_I))
		print_mtime(f->atime, f->name_str);
	else
		print_mtime(f->mtime, f->name_str);
	ft_printf("%s\n", f->name_str);
}

static void		print_directory(t_dirlst *dir, t_ls *ls_cont)
{
	t_list		*lst;
	t_file		*file;

	lst = dir->f_lst;
	file = lst->content;
	if (ls_cont->options & (1ULL << L_FLAG_I))
		ft_printf("total %d\n", dir->d_blocks);
	while (lst->next)
	{
		lst = lst->next;
		file = lst->content;
		if (ls_cont->options & (1ULL << L_FLAG_I))
			print_l_format(file, dir, ls_cont);
		else if (ls_cont->options & ONE_FLAG)
			ft_printf("%s\n", file->name_str);
	}
}


void	ft_print_ls(t_ls *ls_cont)
{
	t_dirlst	*dirs;

	dirs = ls_cont->dirs->next;
	while (dirs)
	{
//		ft_printf("%s:\n", dirs->d_name);
//		ft_printf("total %d\n", dirs->d_blocks);
		print_directory(dirs, ls_cont);
		dirs = dirs->next;
		if (dirs)
			ft_printf("\n%s:\n", dirs->d_name);
	}

}
