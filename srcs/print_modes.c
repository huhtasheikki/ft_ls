/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_modes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:04:06 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/30 16:37:28 by hhuhtane         ###   ########.fr       */
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

static int		get_xors(mode_t st_mode, int sbit, int xbit)
{
	if (st_mode & sbit)
	{
		if (st_mode & xbit)
			return ('s');
		else
			return ('S');
	}
	if (st_mode & xbit)
		return ('x');
	else
		return ('-');
}

void			print_modes(mode_t st_mode)
{
	ft_printf("%c", entry_type_char(st_mode));
	(st_mode & S_IRUSR) ? ft_printf("r") : ft_printf("-");
	(st_mode & S_IWUSR) ? ft_printf("w") : ft_printf("-");
	ft_printf("%c", get_xors(st_mode, SUID_BIT, S_IXUSR));
	(st_mode & S_IRGRP) ? ft_printf("r") : ft_printf("-");
	(st_mode & S_IWGRP) ? ft_printf("w") : ft_printf("-");
	ft_printf("%c", get_xors(st_mode, GUID_BIT, S_IXGRP));
	(st_mode & S_IROTH) ? ft_printf("r") : ft_printf("-");
	(st_mode & S_IWOTH) ? ft_printf("w") : ft_printf("-");
	if (st_mode & STICKY_BIT)
	{
		if (st_mode & S_IXOTH)
			ft_printf("t");
		else
			ft_printf("T");
	}
	else
		(st_mode & S_IXOTH) ? ft_printf("x") : ft_printf("-");
	ft_printf(" ");
}

char			*print_owner(uid_t st_uid, char *file)
{
	t_passwd	*passwd;

	errno = 0;
	if (!(passwd = getpwuid(st_uid)))
		error_ls(file, errno);
	return (passwd->pw_name);
}

void			print_mtime(time_t mtime, char *file)
{
	time_t		now;
	char		*str;

	if ((now = time(&now)) == -1)
		error_ls(file, errno);
	str = ctime(&mtime);
	if ((now - mtime) < 15778463)
		ft_printf("%.12s ", (str + 4));
	else
		ft_printf("%.7s %.4s ", (str + 4), (str + 20));
}
