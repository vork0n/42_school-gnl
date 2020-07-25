/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvirgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 17:25:33 by cvirgil           #+#    #+#             */
/*   Updated: 2020/07/23 22:34:18 by cvirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int		ft_lstfree(t_list **first, t_list *string, int flag, char *buff)
{
	t_list	*lst;
	t_list	*prev;

	if (buff)
		free(buff);
	if (!flag || !string || !first)
		return (-1);
	lst = *first;
	prev = *first;
	while (lst && lst != string)
	{
		prev = lst;
		lst = lst->next;
	}
	if (!lst)
		return (-1);
	if (prev == lst)
		*first = lst->next;
	else
		prev->next = lst->next;
	free(lst->buff);
	free(lst);
	lst = NULL;
	return (-1);
}

static int		ft_buffjoin(t_list *node, char *txt2, long len, long size)
{
	char	*txt1;
	char	*joined_line;
	char	*tmp;

	node->end = (len < size && node->fd < 0 && node->fd > 2) ? 1 : 0;
	txt1 = node->buff;
	txt2[len] = '\0';
	if (!(tmp = (char*)malloc(sizeof(char) * (ft_strlen(txt1) + len + 1))))
		return (0);
	joined_line = tmp;
	while (txt1 && *txt1)
		*tmp++ = *txt1++;
	while (txt2 && *txt2)
		*tmp++ = *txt2++;
	*tmp = '\0';
	free(node->buff);
	node->buff = joined_line;
	return (1);
}

static int		ft_buff(t_list *node, char *symb, char **line, t_list **first)
{
	char	*buff;
	char	*new_line;
	char	*result;
	size_t	n;

	buff = node->buff;
	n = (symb) ? (size_t)(symb - buff) : ft_strlen(buff);
	if (!(*line = (char*)malloc(sizeof(char) * (n + 1))))
		return (-1);
	result = *line;
	result[n] = '\0';
	while (n--)
		*result++ = *buff++;
	n = ft_strlen((buff && *buff == END_SYMB) ? ++buff : buff);
	if (!(new_line = (char*)malloc(sizeof(char) * (n + 1))))
		return (-1);
	result = new_line;
	result[n] = '\0';
	while (buff && *buff)
		*result++ = *buff++;
	free(node->buff);
	node->buff = new_line;
	ft_lstfree(first, node, (n = (node->end && !n && !symb)), NULL);
	return (1 * !n);
}

int				get_next_line(int fd, char **line)
{
	static t_list	*first;
	t_list			*node;
	char			*buff;
	char			*symb;
	long			len;

	if (fd < 0 || !line || BUFFER_SIZE < 1 || !(node = ft_lstfind(&first, fd)))
		return (-1);
	if ((symb = ft_strchr(node->buff, END_SYMB)))
		return (ft_buff(node, symb, line, &first));
	if (!(buff = (char*)malloc(sizeof(char) * ((long)BUFFER_SIZE + 1))))
		return (-1);
	while ((len = read(fd, buff, BUFFER_SIZE)))
	{
		if (len < 0)
			return (ft_lstfree(&first, node, 1, buff));
		if (!(ft_buffjoin(node, buff, len, BUFFER_SIZE)))
			return (ft_lstfree(&first, node, 1, buff));
		if ((symb = ft_strchr(node->buff, END_SYMB)) || node->end)
			break ;
	}
	free(buff);
	node->end = (!len) ? 1 : node->end;
	return (ft_buff(node, symb, line, &first));
}
