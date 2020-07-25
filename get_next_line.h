/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvirgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 17:27:32 by cvirgil           #+#    #+#             */
/*   Updated: 2020/07/23 22:02:02 by cvirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h> //free malloc 
# include <unistd.h>//read write size_t
# define END_SYMB '\n'
// define BUFFER_SIZE 10

int					get_next_line(int fd, char **line);
/*для возможности чтения из нескольких файлов по очереди
и хранения значения буфера разных файлов между вызовами
используем fd, чтобы знать для какого файла наша нода*/
typedef	struct		s_list
{
	int				fd;//для какого файла
	char			*buff;
	int				end;//признак конца файла. Дочитали до конца или нет. для вывода 0 или 11
	struct s_list	*next;//ссылка на следующую ноду
}					t_list;
t_list				*ft_lstnew(int fd, char *s, int n);
t_list				*ft_lstfind(t_list **first_elem, int fd);
int					ft_lstfree(t_list **first_elem, t_list *find, int flag, char *buff);
size_t				ft_strlen(char *s);
char				*ft_strchr(char *s, char c);

#endif
