/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 13:37:58 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/21 17:17:50 by hhuhtane         ###   ########.fr       */
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

static t_file	*get_stats(char *file, t_ls *ls_cont)
{
//	t_stat		*buf;
//	t_passwd	*passwd;
//	t_group		*group;
	t_file		*temp;
	

//	if (!(buf = (t_stat*)malloc(sizeof(t_stat))))
//		error_ls(NULL, MALLOC_ERROR);
	if (!(temp = (t_file*)malloc(sizeof(t_file))))
		error_ls(NULL, MALLOC_ERROR);
//	temp->file_stat = buf;
	if (!(temp->name_str = ft_strdup(file)))
		error_ls(NULL, MALLOC_ERROR);
	if (!(temp->f_stat = (t_stat*)malloc(sizeof(t_stat))))
		error_ls(NULL, MALLOC_ERROR);
//	if (!(temp->f_passwd = (t_passwd*)malloc(sizeof(t_passwd))))
//		error_ls(NULL, MALLOC_ERROR);
//	if (!(temp->f_group = (t_group*)malloc(sizeof(t_group))))
//		error_ls(NULL, MALLOC_ERROR);
	
	if ((stat(file, temp->f_stat)) == -1)
		error_ls(file, errno); //is this ok?
//	if (!(temp->f_passwd = getpwuid(temp->f_stat->st_uid)))
//		error_ls(file, errno); //is this ok? maybe not here?
//	if (!(temp->f_group = getgrgid(temp->f_stat->st_gid)))
//		error_ls(file, errno); //is this ok? maybe not here?
	if (((ls_cont->options >> RECURSIVE) & 1) && (temp->f_stat->st_mode & S_IFDIR))
		ft_list_dir(file, ls_cont);
	return (temp);
/*
NOT YET HERE
	temp->name_str = ft_strdup(file);
	temp->mode_str = get_modes(buf);
	temp->links_str = get_links(buf);
	temp->owner_str = get_owner(buf, file);
	temp->group_str = get_group(buf, file);
	temp->size_str = get_file_size(buf);

THIS ARE USELESS
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
*/

	
//	if (!(file_out = (t_file*)malloc(sizeof(t_file))))
//		return (0);
	
//	file_out->mode_str = get_modes
}

/*
static void		lst_delete(void *data, size_t i)
{
//	while (1);
//	ft_bzero(data, i);
//	while (1);
	ft_printf("%u\n", sizeof(t_dirlst));
	free(data);
	(void)i;
	while (1);
}
*/

t_dirlst	*ft_init_dir_lst(t_dirlst *lst, char *dir)
{
	t_dirlst	*ptr;

	ptr = lst;
	while (ptr->next)
		ptr = ptr->next;
	if (!(ptr->next = (t_dirlst*)malloc(sizeof(t_dirlst))))
		error_ls(NULL, MALLOC_ERROR);
	ptr = ptr->next;
	ptr->next = NULL;
	if (!(ptr->d_name = ft_strdup(dir)))
		error_ls(NULL, MALLOC_ERROR);
	if (!(ptr->f_lst = ft_lstnew(NULL, 0)))
		error_ls(NULL, MALLOC_ERROR);
	return (ptr);
}

int			ft_list_dir(char *dir, t_ls *ls_cont)
{
	DIR			*dirp;
	t_dirent	*dent;
	t_list		*temp;
	t_file		*f;
	t_dirlst	*current;

	current = ft_init_dir_lst(ls_cont->dirs, dir);
	if (!(dirp = opendir(dir)))
		return (error_ls(dir, OPEN_ERROR));
	while ((dent = readdir(dirp)))
	{
		f = get_stats(dent->d_name, ls_cont);
		temp = ft_lstnew(f, sizeof(t_file));
//		temp = ft_lstnew(get_stats(dent->d_name, ls_cont), sizeof(t_file));
		if (!temp)
			error_ls(NULL, MALLOC_ERROR);
//		ft_get_stats(dent->d_name, f_temp, ls_cont); //FILEOUT VAI CURRENT
//		if (!(temp = ft_lstnew(f_temp, 1)))
//		{
//			error_ls(NULL, MALLOC_ERROR);
//			closedir(dirp);
//			return (0);
//		}
		ft_lstappend(&current->f_lst, temp);
		free(f);
//		ft_lstappend(&ls_cont->dirs->f_lst, temp);
//		ft_printf("%s\n", dent->d_name);
//		ft_inspect_file(dent->d_name);
	}
	closedir(dirp);
//	ft_printf("current->d_name |%s|\n", current->d_name);
//	f = ls_cont->dirs->next->f_lst->next->next->next->content;
//	ft_printf("listdir f =%d\n", f->f_stat->st_size);
	return (1);
}
