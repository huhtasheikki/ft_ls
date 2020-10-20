/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 11:57:08 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/19 19:37:19 by hhuhtane         ###   ########.fr       */
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
# include <string.h> //strerror
# include <stdio.h> //perror
# include "libft.h"
# include "libft_shorthand.h"
# include "ft_printf.h"
# include "ft_ls_typedefs.h"

/*
****************
** PROTOTYPES **
****************
*/

int		ft_parse_args(int argc, char **argv, t_ls *ls_cont);
int		ft_list_dir(char *dir, t_ls *ls_cont);
int		error_ls(char *str, int error_code);

#endif
