/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 11:57:08 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/21 12:29:23 by hhuhtane         ###   ########.fr       */
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

char	*get_modes(t_stat *buf);
char	*get_links(t_stat *buf);
char	*get_owner(t_stat *buf, char *file);
char	*get_group(t_stat *buf, char *file);
char	*get_file_size(t_stat *buf);

#endif
