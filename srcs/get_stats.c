/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stats.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 18:29:52 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/30 16:00:12 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*get_links(t_stat *buf, char *str)
{
	if (!(str = ft_itoa(buf->st_nlink)))
		error_ls(NULL, MALLOC_ERROR);
	return (str);
}

char	*get_owner(t_stat *buf, char *file, t_file *f)
{
	char			*str;
	t_passwd		*passwd;

	errno = 0;
	if (!(passwd = getpwuid(buf->st_uid)))
		error_ls(file, errno);
	if (!(str = ft_strdup(passwd->pw_name)))
		error_ls(NULL, MALLOC_ERROR);
	f->owner_str = str;
	return (str);
}

char	*get_group(t_stat *buf, char *file, t_file *f)
{
	char			*str;
	t_group			*group;

	if (!(group = getgrgid(buf->st_gid)))
		error_ls(file, errno);
	if (!(str = ft_strdup(group->gr_name)))
		error_ls(NULL, MALLOC_ERROR);
	f->group_str = str;
	return (str);
}

char	*get_file_size(t_stat *buf)
{
	char			*str;

	if (!(str = ft_uintmaxtoa_base(buf->st_size, 10)))
		error_ls(NULL, MALLOC_ERROR);
	return (str);
}
