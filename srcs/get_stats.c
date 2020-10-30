/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stats.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 18:29:52 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/30 11:20:12 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*get_modes(t_stat *buf, char *str)
{
	ft_memset(str, '-', 10);
	(buf->st_mode & S_IFMT) == S_IFREG ? (str[0] = '-') : 0;
	(buf->st_mode & S_IFMT) == S_IFDIR ? (str[0] = 'd') : 0;
	(buf->st_mode & S_IFMT) == S_IFCHR ? (str[0] = 'c') : 0;
	(buf->st_mode & S_IFMT) == S_IFBLK ? (str[0] = 'b') : 0;
	(buf->st_mode & S_IFMT) == S_IFLNK ? (str[0] = 'l') : 0;
	(buf->st_mode & S_IFMT) == S_IFSOCK ? (str[0] = 's') : 0;
	(buf->st_mode & S_IFMT) == S_IFIFO ? (str[0] = 'p') : 0;
	buf->st_mode & S_IRUSR ? (str[1] = 'r') : 0;
	buf->st_mode & S_IWUSR ? (str[2] = 'w') : 0;
	buf->st_mode & S_IXUSR ? (str[3] = 'x') : 0;
	buf->st_mode & S_IRGRP ? (str[4] = 'r') : 0;
	buf->st_mode & S_IWGRP ? (str[5] = 'w') : 0;
	buf->st_mode & S_IXGRP ? (str[6] = 'x') : 0;
	buf->st_mode & S_IROTH ? (str[7] = 'r') : 0;
	buf->st_mode & S_IWOTH ? (str[8] = 'w') : 0;
	buf->st_mode & S_IXOTH ? (str[9] = 'x') : 0;
	str[10] = '\0';
	return (str);
}

char	*get_links(t_stat *buf, char *str)
{
	if (!(str = ft_itoa(buf->st_nlink)))
		error_ls(NULL, MALLOC_ERROR);
	return (str);
}

char	*get_owner(t_stat *buf, char *file, char *str)
{
	t_passwd		*passwd;

	errno = 0;
	if (!(passwd = getpwuid(buf->st_uid)))
		error_ls(file, errno);
	if (!(str = ft_strdup(passwd->pw_name)))
		error_ls(NULL, MALLOC_ERROR);
	return (str);
}

char	*get_group(t_stat *buf, char *file, char *str)
{
	t_group			*group;

	if (!(group = getgrgid(buf->st_gid)))
		error_ls(file, errno);
	if (!(str = ft_strdup(group->gr_name)))
		error_ls(NULL, MALLOC_ERROR);
	return (str);
}

char	*get_file_size(t_stat *buf)
{
	char			*str;

	if (!(str = ft_uintmaxtoa_base(buf->st_size, 10)))
		error_ls(NULL, MALLOC_ERROR);
	return (str);
}
