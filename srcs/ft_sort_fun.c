/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_fun.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 21:26:11 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/26 22:02:48 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		sort_mtime(t_list *a, t_list *b)
{
	t_file		*af;
	t_file		*bf;

	af = a->content;
	bf = b->content;
	if (af->mtime >= bf->mtime)
		return (1);
	return (0);
}

int		sort_name(t_list *a, t_list *b)
{
	t_file		*af;
	t_file		*bf;

	af = a->content;
	bf = b->content;
	if (ft_strcmp(af->name_str, bf->name_str) < 0)
		return (1);
	return (0);
}
