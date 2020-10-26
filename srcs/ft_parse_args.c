/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 12:20:37 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/26 14:57:16 by hhuhtane         ###   ########.fr       */
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

int		ft_parse_args(int argc, char **argv, t_ls *ls_cont)
{
	int		i;

	i = 1;
	if (argc == 1 || argv[1][0] != '-')
		ls_cont->options = 1 << 1;
	else
		i = ft_parse_options(argc, argv, ls_cont);
	ft_printf("i=%d\n", i);
	while (argv[i])
		ft_read_dir("", argv[i++], ls_cont);
//		ft_list_dir(argv[i++], ls_cont);
	return (1);
}
