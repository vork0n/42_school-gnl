/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvirgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 17:25:33 by cvirgil           #+#    #+#             */
/*   Updated: 2020/07/25 16:21:34 by cvirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
# include <fcntl.h>

//склеивает буфер если есть остаток после предыдушего вызова
//старую память очищаем и присваиваем новую для совместного буфера
static int		ft_buffjoin(t_list *node, char *text2, long len_read, long size)
{
	char	*text1;
	char	*joined_line;
	char	*tmp;

	node->end = (len_read < size && node->fd < 0 && node->fd > 2) ? 1 : 0;
	text1 = node->buff;
	text2[len_read] = '\0';
	if (!(tmp = (char*)malloc(sizeof(char) * (ft_strlen(text1) + len_read + 1))))
		return (0);//выделяем память под общий буфер
	joined_line = tmp;//почему здесь? чтобы не потерять первую ячейку
	while (text1 && *text1)
		*tmp++ = *text1++;//добавляем старый буфер
	while (text2 && *text2)
		*tmp++ = *text2++;//добавляем новый буфер
	*tmp = '\0';
	free(node->buff);//очищаем, что было в буфере до этого
	node->buff = joined_line;//присваиваем буферу ссылку на новую строку
	return (1);
}

//работаем с той строкой, которую нужно отдать и уменьшаем буфер
//заканчивает нашу программу
static int		ft_get_buff(t_list *node, char *symbol, char **line, t_list **first_elem)
{
	char	*buff;
	char	*new_line;
	char	*result;
	size_t	n;

	buff = node->buff;
	n = (symbol) ? (size_t)(symbol - buff) : ft_strlen(buff);//определяем место разделителя
	if (!(*line = (char*)malloc(sizeof(char) * (n + 1))))
		return (-1);
	result = *line;
	result[n] = '\0';//ставим разделитель
	while (n--)
		*result++ = *buff++;//записываем до разделителя
	n = ft_strlen((buff && *buff == END_SYMB) ? ++buff : buff);
	if (!(new_line = (char*)malloc(sizeof(char) * (n + 1))))
		return (-1);
	result = new_line;
	result[n] = '\0';
	while (buff && *buff)
		*result++ = *buff++;
	free(node->buff);
	node->buff = new_line;
	ft_lstfree(first_elem, node, (n = (node->end && !n && !symbol)), NULL);
	//n = для того, чтоб ыопределить, что нам нужно вернуьть 1 или 2 (нужно ли еще читать или файл закончился)
	//буфпер пустой, конец файла пришел - в озвращаем ноль
	//удаляем ноду, если она нам больше не нужна, все прочитано и тд
	return (1 * !n);
}

int				get_next_line(int fd, char **line)
{
	static t_list	*first_elem;//статические автоматически инициализируется 0
	t_list			*node;//с которой будем работать
	char			*buff;
	char			*symbol;//адрес места до куда возвращаем /n
	long			len_read;
//если находим фд, работаем с этой нодой, нет - создаем новую, не удается - выводим ошибку
	if (fd < 0 || !line || BUFFER_SIZE < 1 || !(node = ft_lstfind(&first_elem, fd)))
		return (-1);
	if ((symbol = ft_strchr(node->buff, END_SYMB)))
	//проверяем есть ли конец строки в буфере. если прочитали болшой буфер в предыдущий раз, в котором много строк
		return (ft_get_buff(node, symbol, line, &first_elem));//не читаем новую порцию, если есть конец строки
	if (!(buff = (char*)malloc(sizeof(char) * ((long)BUFFER_SIZE + 1))))//еденица для знака конца строки
		return (-1);//создаем буфер, если не нашли, куда будем считывать из файла
	while ((len_read = read(fd, buff, BUFFER_SIZE))) //читаем  из файла размера буфера и записываем 
	{
		//printf ("l%d", len_read);
		if (len_read < 0)//то что вернули меньрше нуляБ то проблемы, файл крашится и тд
			return (ft_lstfree(&first_elem, node, 1, buff));
		if (!(ft_buffjoin(node, buff, len_read, BUFFER_SIZE)))//объединяем старый буфер с прочитанным сейчас
			return (ft_lstfree(&first_elem, node, 1, buff));
		if ((symbol = ft_strchr(node->buff, END_SYMB)) || node->end)
		//проверяем, есть ли в новом буфере конец строки
			break ;//завершаем цикл. читаем пока не найдем конец строки в последующих чтениях
	}
	free(buff);
	node->end = (!len_read) ? 1 : node->end;
	return (ft_get_buff(node, symbol, line, &first_elem));
}

int main(void)
{
	char	*line;
	int		fd;
	int		fd2;
	
	fd = open("test.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);

get_next_line(fd, &line);
		printf("%s\n", line);
get_next_line(fd2, &line);		
		printf("%s\n", line);
	get_next_line(fd, &line);	
	printf("%s\n", line);
	
}