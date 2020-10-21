/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_typedefs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 13:48:03 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/21 12:11:40 by hhuhtane         ###   ########.fr       */
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
# define USAGE 2
# define MALLOC_ERROR 4
# define OPEN_ERROR 8
# define LS_OPTIONS "@1AaBbCcdeFfGgHhikLlmnOoPpqRrSsTtuUvWwx%"
# define LS_OPTIONS_SIZE 40
# define RECURSIVE 27

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
	t_passwd				*f_passwd;
	t_group					*f_group;
	char					*name_str;
	char					*mode_str;
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
