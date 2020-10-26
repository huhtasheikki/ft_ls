/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_utilities.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 09:59:51 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/26 19:47:43 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_copy_stat(char *path, char *file, t_file *dst)
{
	t_stat		buf;
//	char		*path2;

//	if (!(path2 = ft_strjoin(path, "/")))
//		error_ls(file, MALLOC_ERROR);
	if (!(dst->path = ft_strjoin(path, file)))
		error_ls(file, MALLOC_ERROR);
	if (stat(dst->path, &buf) == -1)
		error_ls(path, errno);
//	printf("STAT:%s\n", dst->path);
//	free(path2);
	if (!(dst->name_str = ft_strdup(file)))
		error_ls(NULL, MALLOC_ERROR);
	dst->st_dev = buf.st_dev;
	dst->st_ino = buf.st_ino;
	dst->st_mode = buf.st_mode;
//	dst->st_mode2 = buf.st_mode;
	dst->st_nlink = buf.st_nlink;
	dst->st_uid = buf.st_uid;
	dst->st_gid = buf.st_gid;
	dst->st_rdev = buf.st_rdev;
	dst->mtime = buf.st_mtime;
	dst->st_size = buf.st_size;
	dst->st_blocks = buf.st_blocks;
}
