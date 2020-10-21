/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stats.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 18:29:52 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/21 12:53:05 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*get_modes(t_stat *buf)
{
	char			*str;

	if (!(str = (char*)malloc(sizeof(char) * 11)))
		error_ls(NULL, MALLOC_ERROR);
	buf->st_mode & S_IFREG ? (str[0] = '-') : (str[0] = ' ');
	buf->st_mode & S_IFDIR ? (str[0] = 'd') : 0;
	buf->st_mode & S_IFCHR ? (str[0] = 'c') : 0;
	buf->st_mode & S_IFBLK ? (str[0] = 'b') : 0;
	buf->st_mode & S_IFLNK ? (str[0] = 'l') : 0;
	buf->st_mode & S_IFSOCK ? (str[0] = 's') : 0;
	buf->st_mode & S_IFIFO ? (str[0] = 'p') : 0;
	buf->st_mode & S_IRUSR ? (str[1] = 'r') : (str[1] = '-');
	buf->st_mode & S_IWUSR ? (str[2] = 'w') : (str[2] = '-');
	buf->st_mode & S_IXUSR ? (str[3] = 'x') : (str[3] = '-');
	buf->st_mode & S_IRGRP ? (str[4] = 'r') : (str[4] = '-');
	buf->st_mode & S_IWGRP ? (str[5] = 'w') : (str[5] = '-');
	buf->st_mode & S_IXGRP ? (str[6] = 'x') : (str[6] = '-');
	buf->st_mode & S_IROTH ? (str[7] = 'r') : (str[7] = '-');
	buf->st_mode & S_IWOTH ? (str[8] = 'w') : (str[8] = '-');
	buf->st_mode & S_IXOTH ? (str[9] = 'x') : (str[9] = '-');
	str[10] = '\0';
	return (str);
}

char	*get_links(t_stat *buf)
{
	char			*str;

	if (!(str = ft_itoa(buf->st_nlink)))
		error_ls(NULL, MALLOC_ERROR);
	return (str);
}

char	*get_owner(t_stat *buf, char *file)
{
	t_passwd		*passwd;
	char			*str;

	errno = 0;
	if (!(passwd = getpwuid(buf->st_uid))) //is error check ok?
		error_ls(file, errno);
	if (!(str = ft_strdup(passwd->pw_name)))
		error_ls(NULL, MALLOC_ERROR);
	return (str);
}

char	*get_group(t_stat *buf, char *file)
{
	t_group			*group;
	char			*str;

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
