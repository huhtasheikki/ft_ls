/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_typedefs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 13:48:03 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/19 19:39:54 by hhuhtane         ###   ########.fr       */
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
# define LS_OPTIONS "@1AaBbCcdeFfGgHhikLlmnOoPpqRrSsTtuUvWwx%"
# define LS_OPTIONS_SIZE 40

/*
**************
** TYPEDEFS **
**************
*/

typedef struct dirent		t_dirent;
typedef struct stat			t_stat;
typedef struct passwd		t_passwd;

typedef struct s_file
{
	t_stat					file_stat;
	char					mode_str[11];
	char					*links_str;
	char					*owner_str;
	char					*group_str;
	char					*size_str;
	char					*lastmod_str;
	char					*name_str;
}							t_file;

typedef struct s_ls
{
	t_dirent				*dirent;
	t_stat					*t_stat;
	t_passwd				*t_passwd;
	char					options_str[LS_OPTIONS_SIZE + 1];
	t_u64					options;
	int						error_code;
	t_list					*args_output;
	t_list					*file_lst;
}							t_ls;



#endif
