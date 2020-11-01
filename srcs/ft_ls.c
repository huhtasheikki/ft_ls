/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 11:51:15 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/11/01 14:23:00 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_start_init(t_ls *ls_cont)
{
	ls_cont->options = ONE_FLAG;
	ft_strncpy(ls_cont->options_str, LS_OPTIONS, LS_OPTIONS_SIZE + 1);
	if (!(ls_cont->dirs = (t_dirlst*)malloc(sizeof(t_dirlst))))
		error_ls(NULL, MALLOC_ERROR);
	if (!(ls_cont->files = (t_dirlst*)malloc(sizeof(t_dirlst))))
		error_ls(NULL, MALLOC_ERROR);
	ft_init_dirlst(ls_cont->files, "", "");
}

/*
** FLAGS THAT WORK WITH THIS FT_LS ARE (AT THIS POINT):
** -1	(The numeric digit ``one''.)  Force output to be one entry per line.
** 		This is the default when output is not to a terminal.
**
** -A	List all entries except for '.' and '..'.  Always set for the super-
**		user.
**
** -a	Include directory entries whose names begin with a dot (.).
**
** -f	Output is not sorted.  This option turns on the -a option.
**
** -g	This option is only available for compatibility with POSIX; it is
**		used to display the group name in the long (-l) format output (the
**		owner name is suppressed).
**
** -l	(The lowercase letter ``ell''.)  List in long format.  (See below.)
**		A total sum for all the file sizes is output on a line before the
**		long listing.
**
** -o	List in long format, but omit the group id.
**
** -R	Recursively list subdirectories encountered.
**
** -r	Reverse the order of the sort to get reverse lexicographical order
**		or the oldest entries first (or largest files last, if combined with
**		sort by size
**
** -S	Sort files by size
**
** -t	Sort by time modified (most recently modified first) before sorting
**		the operands by lexicographical order.
**
** -u	Use time of last access, instead of last modification of the file
**		for sorting (-t) or long printing (-l).
*/

int		main(int argc, char **argv)
{
	t_ls	ls_cont;

	ft_start_init(&ls_cont);
	ft_parse_args(argc, argv, &ls_cont);
	ft_print_ls(&ls_cont);
	return (0);
}
