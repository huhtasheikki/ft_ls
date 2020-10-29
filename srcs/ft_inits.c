/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 12:38:58 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/29 10:43:59 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		*create_path_str(char *path, char *subdir, char *dir)
{
	size_t		len;

	len = ft_strlen(dir);
	if (subdir[0] == '\0')
	{
		if (dir[len - 1] == '/')
		{
			if (!(path = ft_strdup(dir)))
				error_ls(NULL, MALLOC_ERROR);
		}
		else
		{
			if (!(path = ft_strjoin(dir, "/")))
				error_ls(NULL, MALLOC_ERROR);
		}
	}
	else
	{
		if (!(path = ft_strnew(len + ft_strlen(subdir) + 2)))
			error_ls(NULL, MALLOC_ERROR);
		ft_strcat(path, subdir);
		ft_strcat(path, dir);
		ft_strcat(path, "/");
	}
	return (path);
}

t_dirlst		*ft_init_dirlst(t_dirlst *lst, char *subdir, char *dir)
{
	t_dirlst	*ptr;

	ptr = lst;
	while (ptr->next)
		ptr = ptr->next;
	if (!(ptr->next = (t_dirlst*)malloc(sizeof(t_dirlst))))
		error_ls(NULL, MALLOC_ERROR);
	ptr = ptr->next;
	ptr->next = NULL;
	ptr->d_name = create_path_str(ptr->d_name, subdir, dir);
	ptr->d_blocks = 0;
	ptr->nl_size = 0;
	ptr->o_size = 0;
	ptr->g_size = 0;
	ptr->s_size = 0;
	if (!(ptr->f_lst = ft_lstnew(NULL, 0)))
		error_ls(NULL, MALLOC_ERROR);
	return (ptr);
}
