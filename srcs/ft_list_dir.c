/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 13:37:58 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/19 19:44:03 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <dirent.h>
//#include <sys/stat.h>
//#include <pwd.h>
//#include <grp.h>
//#include <time.h>
//#include "ft_ls_typedefs.h"
//#include "libft.h"
//#include "ft_printf.h"
#include "ft_ls.h"

char		*number_of_links(struct stat *buf)
{
	char	*str;

	str = ft_itoa(buf->st_nlink);
	return (str);
}

char		*permissions(struct stat *buf)
{
	char	*str;

	str = (char*)malloc(sizeof(char) * 11);
	ft_memset(str, '-', 10);
	str[10] = '\0';
	if ((buf->st_mode & S_IRUSR))
		str[1] = 'r';
	if ((buf->st_mode & S_IWUSR))
		str[2] = 'w';
	if ((buf->st_mode & S_IXUSR))
		str[3] = 'x';
	if ((buf->st_mode & S_IRGRP))
		str[4] = 'r';
	if ((buf->st_mode & S_IWGRP))
		str[5] = 'w';
	if ((buf->st_mode & S_IXGRP))
		str[6] = 'x';
	if ((buf->st_mode & S_IROTH))
		str[7] = 'r';
	if ((buf->st_mode & S_IWOTH))
		str[8] = 'w';
	if ((buf->st_mode & S_IXOTH))
		str[9] = 'x';
	return (str);
}

char		*which_type(struct stat *buf)
{
//	ft_printf("\nnum: %d\n", (buf->st_mode & S_IFMT));
	if ((buf->st_mode & S_IFMT) == S_IFREG)
		return (ft_strdup("Regular file"));
	else if ((buf->st_mode & S_IFMT) == S_IFSOCK)
		return (ft_strdup("Socket"));
	else if ((buf->st_mode & S_IFMT) == S_IFLNK)
		return (ft_strdup("Symbolic link"));
	else if ((buf->st_mode & S_IFMT) == S_IFBLK)
		return (ft_strdup("Block device"));
	else if ((buf->st_mode & S_IFMT) == S_IFDIR)
		return (ft_strdup("Directory"));
	else if ((buf->st_mode & S_IFMT) == S_IFCHR)
		return (ft_strdup("Character device"));
	else if ((buf->st_mode & S_IFMT) == S_IFIFO)
		return (ft_strdup("FIFO"));
	else
		return (ft_strdup("Error"));
}

char		*grouppi(struct stat *buf)
{
//	char	*str;
	struct group	*group;

//	group = (struct group*)malloc(sizeof(struct group));
	group = getgrgid(buf->st_gid);
//	ft_printf("\nname=|%s| passwd=|%s| gid=|%d| gr_mem=|%s|\n", group->gr_name, group->gr_passwd, group->gr_gid, group->gr_mem[1]);
	return (group->gr_name);
}

char		*owner(struct stat *buf)
{
	struct passwd	*passwd;

	passwd = getpwuid(buf->st_uid);
	return (passwd->pw_name);
}

int			file_size(struct stat *buf)
{
	return (buf->st_size);
}

char		*last_mod(struct stat *buf)
{
	return (ctime(&buf->st_mtimespec.tv_sec));
}

int			ft_inspect_file(char *file)
{
	struct stat		*buf;

	buf = (struct stat*)malloc(sizeof(struct stat));
	stat(file, buf);
	ft_printf("Name: %s\n", file);
	ft_printf("Type: %s \n", which_type(buf));
	ft_printf("Modes: %s\n", permissions(buf));
	ft_printf("Number of links: %s\n", number_of_links(buf));
	ft_printf("Owner: %s\n", owner(buf));
	ft_printf("Group: %s\n", grouppi(buf));
	ft_printf("Size: %d octets\n", file_size(buf));
	ft_printf("Last modification date: %s\n", last_mod(buf));
	ft_putendl(" ");
	return (1);
}

static void		ft_get_stats(char *file, t_stat *dst)
{
	t_stat		buf;

	if ((lstat(file, &buf)) == -1)
	{
		perror(file);
		return ;
	}
	dst->st_dev = buf.st_dev;
	dst->st_mode = buf.st_mode;
	dst->st_nlink = buf.st_nlink;
	dst->st_ino = buf.st_ino;
	dst->st_uid = buf.st_uid;
	dst->st_gid = buf.st_gid;
	dst->st_rdev = buf.st_rdev;
	dst->st_size = buf.st_size;
	dst->st_atime = buf.st_atime;
	dst->st_mtime = buf.st_mtime;

	
//	if (!(file_out = (t_file*)malloc(sizeof(t_file))))
//		return (0);
	
//	file_out->mode_str = get_modes
}

int			ft_list_dir(char *dir, t_ls *ls_cont)
{
	DIR			*dirp;
	t_dirent	*dent;
	t_stat		file_out;
	t_list		*temp;

	if (!(dirp = opendir(dir)))
		return (0);
	while ((dent = readdir(dirp)))
	{
		ft_get_stats(dent->d_name, &file_out);
		if (!(temp = ft_lstnew(&file_out, 1)))
		{
			closedir(dirp);
			return (0);
		}
		ft_lstappend(&ls_cont->file_lst, temp);
//		ft_printf("%s\n", dent->d_name);
//		ft_inspect_file(dent->d_name);
	}
	closedir(dirp);
	return (1);
}
