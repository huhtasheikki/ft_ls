/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 19:36:04 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/19 20:22:41 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		error_ls(char *str, int error_code)
{
	if (error_code == USAGE)
	{
		ft_printf("ft_ls: illegal option -- %c\n", *str);
		ft_printf("usage: ft_ls [-%s] [file ...]\n", LS_OPTIONS);
		exit(EXIT_FAILURE);
	}
	if (error_code == MALLOC_ERROR)
	{
		ft_printf("ft_ls: %s: %s", str, strerror(errno));
		exit(EXIT_FAILURE);
	}
	ft_printf("ft_ls: %s: %s", str, strerror(errno));
	return (0);
}
