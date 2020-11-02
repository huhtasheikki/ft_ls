/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_typedefs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 13:48:03 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/11/02 16:31:06 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_TYPEDEFS_H
# define FT_LS_TYPEDEFS_H

# include "libft.h"
# include "libft_shorthand.h"

/*
************
** MACROS **
************
*/
# define USAGE 16
# define MALLOC_ERROR 4
# define OPEN_ERROR 8
# define LS_OPTIONS "1AafgloRrStu"
# define LS_OPTIONS_SIZE 12
# define RECURSIVE 7

# define ONE_FLAG 1
# define AA_FLAGS 6
# define A_FLAG 4
# define UPA_FLAG 2
# define F_FLAG 8
# define G_FLAG 16
# define L_FLAG 32
# define O_FLAG 64
# define R_FLAG 256
# define UPS_FLAG 512
# define T_FLAG 1024
# define U_FLAG 2048
# define L_FLAG_I 5
# define O_FLAG_I 6
# define R_FLAG_I 8
# define UPS_FLAG_I 9
# define T_FLAG_I 10
# define U_FLAG_I 11

# define STICKY_BIT 512
# define GUID_BIT 1024
# define SUID_BIT 2048

/*
**************
** TYPEDEFS **
**************
*/

typedef struct dirent		t_dirent;
typedef struct stat			t_stat;
typedef struct passwd		t_passwd;
typedef struct group		t_group;

typedef struct				s_file
{
	char					*path;
	dev_t					st_dev;
	ino_t					st_ino;
	mode_t					st_mode;
	nlink_t					st_nlink;
	uid_t					st_uid;
	gid_t					st_gid;
	dev_t					st_rdev;
	time_t					mtime;
	time_t					atime;
	off_t					st_size;
	blkcnt_t				st_blocks;
	char					*name_str;
	char					mode_str[11];
	char					*owner_str;
	char					*group_str;
	char					*size_str;
}							t_file;

typedef struct				s_dirlst
{
	char					*d_name;
	t_list					*f_lst;
	blkcnt_t				d_blocks;
	size_t					nl_size;
	size_t					o_size;
	size_t					g_size;
	size_t					s_size;
	struct s_dirlst			*next;
}							t_dirlst;

typedef struct				s_ls
{
	char					options_str[LS_OPTIONS_SIZE + 1];
	t_ul64					options;
	int						error_code;
	t_dirlst				*dirs;
	t_dirlst				*files;
	t_list					*args;
}							t_ls;

#endif
