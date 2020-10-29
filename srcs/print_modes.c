/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_modes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:04:06 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/28 17:09:09 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		entry_type_char(mode_t st_mode)
{
	if ((st_mode & S_IFMT) == S_IFREG)
		return ('-');
	if ((st_mode & S_IFMT) == S_IFDIR)
		return ('d');
	if ((st_mode & S_IFMT) == S_IFCHR)
		return ('c');
	if ((st_mode & S_IFMT) == S_IFBLK)
		return ('b');
	if ((st_mode & S_IFMT) == S_IFLNK)
		return ('l');
	if ((st_mode & S_IFMT) == S_IFSOCK)
		return ('s');
	if ((st_mode & S_IFMT) == S_IFIFO)
		return ('p');
	return (' ');
}

void	print_modes(mode_t st_mode)
{
	char		c;

	ft_printf("%c", entry_type_char(st_mode));
	(st_mode & S_IRUSR) ? (c = 'r') : (c = '-');
	ft_printf("%c", c);
	(st_mode & S_IWUSR) ? (c = 'w') : (c = '-');
	ft_printf("%c", c);
	(st_mode & S_IXUSR) ? (c = 'x') : (c = '-');
	ft_printf("%c", c);
	(st_mode & S_IRGRP) ? (c = 'r') : (c = '-');
	ft_printf("%c", c);
	(st_mode & S_IWGRP) ? (c = 'w') : (c = '-');
	ft_printf("%c", c);
	(st_mode & S_IXGRP) ? (c = 'x') : (c = '-');
	ft_printf("%c", c);
	(st_mode & S_IROTH) ? (c = 'r') : (c = '-');
	ft_printf("%c", c);
	(st_mode & S_IWOTH) ? (c = 'w') : (c = '-');
	ft_printf("%c", c);
	(st_mode & S_IXOTH) ? (c = 'x') : (c = '-');
	ft_printf("%c", c);
	ft_printf(" "); // ACL HERE?
}

char	*print_owner(uid_t st_uid, char *file)
{
	t_passwd	*passwd;

	errno = 0;
	if (!(passwd = getpwuid(st_uid)))
		error_ls(file, errno);
	return (passwd->pw_name);
}

char	*print_group(gid_t st_gid, char *file)
{
	t_group		*group;

	if (!(group = getgrgid(st_gid)))
		error_ls(file, errno);
	return (group->gr_name);
}

void	print_mtime(time_t mtime, char *file)
{
	time_t		now;
	char		*str;

	if ((now = time(&now)) == -1)
		error_ls(file, errno);
	str = ctime(&mtime);
	if ((now - mtime) < 15778463) //six months in seconds
		ft_printf("%.12s ", (str + 4));
	else
		ft_printf("%.7s %.4s ", (str + 4), (str + 20));
}
