/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 14:27:49 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/11/02 15:10:09 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			*print_group(gid_t st_gid, char *file)
{
	t_group		*group;

	if (!(group = getgrgid(st_gid)))
		error_ls(file, errno);
	return (group->gr_name);
}

void			print_l_format(t_file *f, t_dirlst *dir, t_ls *ls_cont)
{
	char		*str;

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
	ft_printf("%s", f->name_str);
	if ((f->st_mode & S_IFMT) == S_IFLNK)
	{
		if (!(str = ft_strnew(256)))
			error_ls(f->name_str, MALLOC_ERROR);
		readlink(f->path, str, 256);
		ft_printf(" -> %s", str);
		free(str);
	}
	ft_printf("\n");
}

static void		print_directory(t_dirlst *dir, t_ls *ls_cont)
{
	t_list		*lst;
	t_file		*file;

	lst = dir->f_lst;
	file = lst->content;
	if (lst->next && (ls_cont->options & (1ULL << L_FLAG_I)))
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

static int		print_files(t_ls *ls_cont)
{
	t_list		*lst;
	t_file		*file;
	int			i;

	i = 0;
	lst = ls_cont->files->next->f_lst;
	while (lst->next)
	{
		i++;
		lst = lst->next;
		file = lst->content;
		if (ls_cont->options & (1ULL << L_FLAG_I))
			print_l_format(file, ls_cont->files->next, ls_cont);
		else if (ls_cont->options & ONE_FLAG)
			ft_printf("%s\n", file->name_str);
	}
	return (i);
}

void			ft_print_ls(t_ls *ls_cont)
{
	t_dirlst	*dirs;
	t_list		*lst;

	dirs = ls_cont->files->next;
	if (print_files(ls_cont))
	{
		dirs = ls_cont->dirs->next;
		lst = dirs->f_lst->next;
		if (lst)
			ft_printf("\n%s:\n", dirs->d_name);
	}
	dirs = ls_cont->dirs->next;
	while (dirs)
	{
		print_directory(dirs, ls_cont);
		dirs = dirs->next;
		if (dirs)
		{
			lst = dirs->f_lst;
			if (lst->next)
				ft_printf("\n%s:\n", dirs->d_name);
		}
	}
}
