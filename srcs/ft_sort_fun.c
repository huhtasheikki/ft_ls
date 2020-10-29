/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_fun.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 21:26:11 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/29 10:54:10 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			sort_mtime(t_list *a, t_list *b)
{
	t_file		*af;
	t_file		*bf;

	af = a->content;
	bf = b->content;
	if (af->mtime > bf->mtime)
		return (1);
	else if (af->mtime == bf->mtime)
		return (ft_strcmp(bf->name_str, af->name_str));
	return (-1);
}

int			sort_name(t_list *a, t_list *b)
{
	t_file		*af;
	t_file		*bf;

	af = a->content;
	bf = b->content;
	return (ft_strcmp(bf->name_str, af->name_str));
}

t_list		*reverse_list(t_list *a)
{
	t_list		*old_last;
	t_list		*new_last;

	old_last = a;
	while (old_last->next)
		old_last = old_last->next;
	new_last = old_last;
	while (a != old_last)
	{
		new_last->next = a;
		new_last = new_last->next;
		a = a->next;
	}
	new_last->next = NULL;
	return (old_last);
}

void		sort_ls_lists(t_list *start, t_ls *ls_cont)
{
	t_list		*t1;

	t1 = start->next;
	if (ls_cont->options & F_FLAG)
		return ;
	if (ls_cont->options & (1ULL << T_FLAG_I))
		mergesort_ls(&t1, &sort_mtime);
	else
		mergesort_ls(&t1, &sort_name);
	if (ls_cont->options & (1ULL << R_FLAG_I))
		ft_lstrev(&t1);
	start->next = t1;
}
