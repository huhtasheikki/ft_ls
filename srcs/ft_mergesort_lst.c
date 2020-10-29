/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mergesort_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 20:37:04 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/28 12:03:40 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_list	*mergesorted(t_list *a, t_list *b, int (*listsort)(t_list *, t_list *))
{
	t_list		*sorted;

	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (listsort(a, b) > 0)
	{
		sorted = a;
		sorted->next = mergesorted(a->next, b, listsort);
	}
	else
	{
		sorted = b;
		sorted->next = mergesorted(a, b->next, listsort);
	}
	return (sorted);
}

void			ft_split_list(t_list *src, t_list **a, t_list **b)
{
	t_list		*slow;
	t_list		*fast;

	slow = src;
	fast = src->next;
	while (fast->next)
	{
		fast = fast->next;
		if (fast->next)
		{
			fast = fast->next;
			slow = slow->next;
		}
	}
	*a = src;
	*b = slow->next;
	slow->next = NULL;
}

void	mergesort_ls(t_list **lst, int (*listsort)(t_list *, t_list *))
{
	t_list		*head;
	t_list		*a;
	t_list		*b;

	head = *lst;
	if (head == NULL || head->next == NULL)
		return ;
	ft_split_list(head, &a, &b);
	mergesort_ls(&a, listsort);
	mergesort_ls(&b, listsort);
	*lst = mergesorted(a, b, listsort);
}
