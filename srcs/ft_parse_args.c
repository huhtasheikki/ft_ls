/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 12:20:37 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/11/01 14:25:12 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		get_option(char c, t_ls *ls_cont)
{
	int		i;

	i = 0;
	if (!(ft_strchr(LS_OPTIONS, c)))
		return (error_ls(&c, USAGE));
	while (i < LS_OPTIONS_SIZE)
	{
		if (c == ls_cont->options_str[i])
		{
			ls_cont->options = ls_cont->options | (1ULL << i);
			return (1);
		}
		i++;
	}
	return (0);
}

static int		ft_parse_options(int argc, char **argv, t_ls *ls_cont)
{
	int		i;
	int		j;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] != '-')
			return (i);
		j = 1;
		while (argv[i][j])
		{
			get_option(argv[i][j], ls_cont);
			j++;
		}
		i++;
	}
	return (i);
}

static void		get_and_sort_args(t_ls *ls_cont, char **argv, int i)
{
	t_file		arg;
	t_stat		buf;
	t_list		*ptr;
	int			j;

	j = 0;
	ptr = ls_cont->args;
	while (argv[i])
	{
		if ((j = lstat(argv[i], &buf)) == -1)
			error_ls(argv[i], errno);
		if (j != -1)
		{
			if (!(arg.name_str = ft_strdup(argv[i])))
				error_ls(argv[i], MALLOC_ERROR);
			arg.mtime = buf.st_mtime;
			arg.atime = buf.st_atime;
			if (!(ptr->next = ft_lstnew(&arg, sizeof(t_file))))
				error_ls(NULL, MALLOC_ERROR);
			ptr = ptr->next;
		}
		i++;
	}
	ptr = ls_cont->args;
	sort_ls_lists(ptr, ls_cont);
}

void			ft_parse_args(int argc, char **argv, t_ls *ls_cont)
{
	int			i;
	t_list		*ptr;
	t_file		*args;

	i = 1;
	if (argc == 1 || argv[1][0] != '-')
		ls_cont->options = ONE_FLAG;
	else
		i = ft_parse_options(argc, argv, ls_cont);
	if (ls_cont->options & F_FLAG)
		ls_cont->options = ls_cont->options | A_FLAG;
	if ((ls_cont->options & (1 << O_FLAG_I) || (ls_cont->options & G_FLAG)))
		ls_cont->options = ls_cont->options | (1 << L_FLAG_I);
	if (!argv[i])
		ft_read_dir("", "./", ls_cont);
	else
		get_and_sort_args(ls_cont, argv, i);
	ptr = ls_cont->args;
	while (ptr->next)
	{
		ptr = ptr->next;
		args = ptr->content;
		ft_read_dir("", args->name_str, ls_cont);
	}
	sort_ls_lists(ls_cont->files->next->f_lst, ls_cont);
}
