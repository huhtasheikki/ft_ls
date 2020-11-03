/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_utilities.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 09:59:51 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/11/03 13:24:54 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static size_t	get_column_size(size_t num)
{
	size_t		size;

	size = 1;
	while (num > 9)
	{
		num /= 10;
		size++;
	}
	return (size);
}

static void		get_csizes(t_stat *buf, char *file, t_file *dst, t_dirlst *cur)
{
	size_t		size;

	if ((size = get_column_size(dst->st_nlink)) > cur->nl_size)
		cur->nl_size = size;
	if ((size = get_column_size(dst->st_size)) > cur->s_size)
		cur->s_size = size;
	get_owner(buf, file, dst);
	get_group(buf, file, dst);
	size = ft_strlen(dst->group_str);
	if (size > cur->g_size)
		cur->g_size = size;
	size = ft_strlen(dst->owner_str);
	if (size > cur->o_size)
		cur->o_size = size;
	free(dst->owner_str);
	free(dst->group_str);
}

void			copy_stat(char *path, char *file, t_file *dst, t_dirlst *cur)
{
	t_stat		buf;

	if (!(dst->path = ft_strjoin(path, file)))
		error_ls(file, MALLOC_ERROR);
	if (lstat(dst->path, &buf) == -1)
		error_ls(path, errno);
	if (!(dst->name_str = ft_strdup(file)))
		error_ls(NULL, MALLOC_ERROR);
	dst->st_dev = buf.st_dev;
	dst->st_ino = buf.st_ino;
	dst->st_mode = buf.st_mode;
	dst->st_nlink = buf.st_nlink;
	dst->st_uid = buf.st_uid;
	dst->st_gid = buf.st_gid;
	dst->st_rdev = buf.st_rdev;
	dst->mtime = buf.st_mtime;
	dst->atime = buf.st_atime;
	dst->st_size = buf.st_size;
	dst->st_blocks = buf.st_blocks;
	cur->d_blocks += buf.st_blocks;
	get_csizes(&buf, file, dst, cur);
}
