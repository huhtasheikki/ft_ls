/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 12:35:04 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/30 13:24:40 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_get_stats(char *path, char *file, t_dirlst *cur, \
				t_ls *ls_cont)
{
	t_file		*temp;
	t_list		*lst;

	if (!(ls_cont->options & A_FLAG) && file[0] == '.')
	{
		if (!(ls_cont->options & UPA_FLAG))
			return ;
		else if ((file[1] == '.') || (file[1] == '\0'))
			return ;
	}
	if (!(temp = (t_file*)malloc(sizeof(t_file))))
		error_ls(NULL, MALLOC_ERROR);
	copy_stat(path, file, temp, cur);
	lst = ft_lstnew(temp, sizeof(t_file));
	if (!lst)
		error_ls(NULL, MALLOC_ERROR);
	free(temp);
	ft_lstappend(&cur->f_lst, lst);
}

static void		read_dirs_rec(t_dirlst *current, t_ls *ls_cont)
{
	t_list		*temp;
	t_file		*file;

	temp = current->f_lst;
	while (temp->next)
	{
		temp = temp->next;
		file = temp->content;
		if (((file->st_mode & S_IFMT) == S_IFDIR) && \
		(file->name_str[0] != '.' || \
		((file->name_str[1] != '.') && \
		(file->name_str[1] != '\0'))))
		{
			ft_read_dir(current->d_name, file->name_str, ls_cont);
		}
	}
}

int				ft_read_dir(char *subdir, char *dir, t_ls *ls_cont)
{
	DIR			*dirp;
	t_dirent	*dent;
	t_dirlst	*current;

	current = ft_init_dirlst(ls_cont->dirs, subdir, dir);
	if (!(dirp = opendir(current->d_name)))
		return (error_ls(dir, OPEN_ERROR));
	while ((dent = readdir(dirp)))
	{
		ft_get_stats(current->d_name, dent->d_name, current, ls_cont);
	}
	closedir(dirp);
	sort_ls_lists(current->f_lst, ls_cont);
	if ((ls_cont->options >> RECURSIVE) & 1)
		read_dirs_rec(current, ls_cont);
	return (1);
}
