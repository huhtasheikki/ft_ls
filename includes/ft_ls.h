/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 11:57:08 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/30 13:00:34 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <errno.h>
# include <string.h>
# include "libft.h"
# include "libft_shorthand.h"
# include "ft_printf.h"
# include "ft_ls_typedefs.h"

/*
****************
** PROTOTYPES **
****************
*/

int			ft_parse_args(int argc, char **argv, t_ls *ls_cont);
int			error_ls(char *str, int error_code);

char		*get_modes(t_stat *buf, char *str);
char		*get_links(t_stat *buf, char *str);
char		*get_owner(t_stat *buf, char *file, char *str);
char		*get_group(t_stat *buf, char *file, char *str);
char		*get_file_size(t_stat *buf);

void		ft_print_ls(t_ls *ls_cont);
void		copy_stat(char *path, char *file, t_file *dst, t_dirlst *cur);
void		print_modes(mode_t st_mode);

t_dirlst	*ft_init_dirlst(t_dirlst *lst, char *subdir, char *dir);
int			ft_read_dir(char *subdir, char *dir, t_ls *ls_cont);

void		mergesort_ls(t_list **lst, int (*listsort)(t_list *, t_list *));

void		sort_ls_lists(t_list *start, t_ls *ls_cont);
//int			sort_mtime(t_list *a, t_list *b);
//int			sort_name(t_list *a, t_list *b);

char		*print_owner(uid_t st_uid, char *file);
char		*print_group(gid_t st_gid, char *file);
void		print_mtime(time_t mtime, char *file);
#endif
