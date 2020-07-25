/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvirgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 17:27:32 by cvirgil           #+#    #+#             */
/*   Updated: 2020/07/23 22:27:08 by cvirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>
# define END_SYMB '\n'

int					get_next_line(int fd, char **line);
typedef	struct		s_list
{
	int				fd;
	char			*buff;
	int				end;
	struct s_list	*next;
}					t_list;
t_list				*ft_lstnew(int fd, char *s, int n);
t_list				*ft_lstfind(t_list **first_elem, int fd);
size_t				ft_strlen(char *s);
char				*ft_strchr(char *s, char c);

#endif
