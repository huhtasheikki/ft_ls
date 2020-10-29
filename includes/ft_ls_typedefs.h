/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_typedefs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 13:48:03 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/28 17:26:39 by hhuhtane         ###   ########.fr       */
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
**					"	00			10		20			30
** 					"0123456789012345678901234567890123456789"
*/
# define USAGE 16
# define MALLOC_ERROR 4
# define OPEN_ERROR 8
# define LS_OPTIONS "@1AaBbCcdeFfGgHhikLlmnOoPpqRrSsTtuUvWwx%"
# define LS_OPTIONS_SIZE 40
# define RECURSIVE 27

# define ONE_FLAG 2
# define AA_FLAGS 12
# define A_FLAG 8
# define UPA_FLAG 4
# define F_FLAG 2048
# define G_FLAG 8192
# define L_FLAG_I 19
# define O_FLAG_I 23
# define R_FLAG_I 28
# define T_FLAG_I 32
# define U_FLAG_I 33

/*
**************
** TYPEDEFS **
**************
*/

typedef struct dirent		t_dirent;
typedef struct stat			t_stat;
typedef struct passwd		t_passwd;
typedef struct group		t_group;

typedef struct s_file
{
	t_stat					*f_stat;
// copy these instead of t_stat;
	char					*path;
	char					file_str[257];
	dev_t					st_dev;
	ino_t					st_ino;
	mode_t					st_mode;
	size_t					st_mode2;
	nlink_t					st_nlink;
	uid_t					st_uid;
	gid_t					st_gid;
	dev_t					st_rdev;
	time_t					mtime;
	time_t					atime;
	off_t					st_size;
	blkcnt_t				st_blocks;

	t_passwd				*f_passwd;
	t_group					*f_group;
	char					*name_str;
	char					mode_str[11];
	char					*links_str;
	char					*owner_str;
	char					*group_str;
	char					*size_str;
	char					*lastmod_str;
}							t_file;

typedef struct s_dirlst
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

typedef struct s_ls
{
	t_dirent				*dirent; // no need?
	t_stat					*t_stat; // no need?
	t_passwd				*t_passwd; // no need?
	char					options_str[LS_OPTIONS_SIZE + 1];
	t_u64					options;
	int						error_code;
	t_list					*args_output; // no need?
	t_list					*file_lst; // no need?
	t_dirlst				*dirs;
}							t_ls;



#endif
