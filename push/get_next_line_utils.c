/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvirgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 17:25:02 by cvirgil           #+#    #+#             */
/*   Updated: 2020/07/23 22:27:23 by cvirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t i;

	i = 0;
	while (s && *s++)
		i++;
	return (i);
}

char	*ft_strchr(char *s, char c)
{
	if (!s)
		return (0);
	while (*s)
		if (*s++ == c)
			return (--s);
	return ((*s == c) ? s : 0);
}

t_list	*ft_lstnew(int fd, char *s, int n)
{
	t_list	*new;

	new = (t_list*)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->fd = fd;
	new->buff = s;
	new->end = n;
	return (new);
}

t_list	*ft_lstfind(t_list **first_elem, int fd)
{
	t_list *lst;
	t_list *prev;

	prev = NULL;
	lst = *first_elem;
	while (lst)
	{
		if (lst->fd == fd)
			return (lst);
		prev = lst;
		lst = lst->next;
	}
	lst = ft_lstnew(fd, NULL, 0);
	if (prev)
		prev->next = lst;
	else
		*first_elem = lst;
	return (lst);
}
