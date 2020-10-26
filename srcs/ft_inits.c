/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 12:38:58 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/26 15:31:21 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dirlst	*ft_init_dirlst(t_dirlst *lst, char *subdir, char *dir)
{
	t_dirlst	*ptr;
	size_t		len;

	ptr = lst;
	while (ptr->next)
		ptr = ptr->next;
	if (!(ptr->next = (t_dirlst*)malloc(sizeof(t_dirlst))))
		error_ls(NULL, MALLOC_ERROR);
	ptr = ptr->next;
	ptr->next = NULL;

	len = ft_strlen(subdir) + ft_strlen(dir) + 2;
	if (!(ptr->d_name = (char*)malloc(sizeof(char) * len)))
		error_ls(NULL, MALLOC_ERROR);
	ft_strcat(ptr->d_name, subdir);
	ft_strcat(ptr->d_name, dir);
	ft_strcat(ptr->d_name, "/");
	if (!(ptr->f_lst = ft_lstnew(NULL, 0)))
		error_ls(NULL, MALLOC_ERROR);
	return (ptr);
}
