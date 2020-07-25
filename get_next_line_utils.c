/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvirgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 17:25:02 by cvirgil           #+#    #+#             */
/*   Updated: 2020/07/23 21:20:13 by cvirgil          ###   ########.fr       */
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

//подаем первую ноду и ищем по списку нужный fd
t_list	*ft_lstfind(t_list **first_elem, int fd)
{
	t_list *lst;
	t_list *prev;

	prev = NULL;
	lst = *first_elem;
	while (lst)
	{
		if (lst->fd == fd)
			return (lst);//возвращаем ноду
		prev = lst;
		lst = lst->next;
	}
	lst = ft_lstnew(fd, NULL, 0);//создаем ноду, если не нашли фд
	if (prev)
		prev->next = lst;
	else
		*first_elem = lst;
	return (lst);
}

//очищаем ноду и удаляем ее, когда закончили читать и все почистили
int		ft_lstfree(t_list **first_elem, t_list *string, int flag, char *buff)
{
	t_list	*lst;
	t_list	*prev;

	if (buff)
		free(buff);
	if (!flag || !string || !first_elem)
		return (-1);
	lst = *first_elem;
	prev = *first_elem;
	while (lst && lst != string)
	{
		prev = lst;
		lst = lst->next;
	}
	if (!lst)
		return (-1);
	if (prev == lst)
		*first_elem = lst->next;//объединяем, чтобы не потерять следующую за удаляемой
	else
		prev->next = lst->next;
	free(lst->buff);
	free(lst);
	lst = NULL;
	return (-1);
}
