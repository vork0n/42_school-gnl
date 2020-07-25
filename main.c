/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvirgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 14:53:46 by gjessica          #+#    #+#             */
/*   Updated: 2020/07/23 18:58:24 by cvirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
# include <fcntl.h>
# include <stdio.h>

int main()
{
	char *line = "";
	int id = 0;

	int fd = open("test.txt", O_RDONLY);
	int fd2 = open("test2.txt", O_RDONLY);
	//int fd = open("test.txt", O_RDONLY);
	//fd = 1;
	//fd =-3;
	int last = 1;
	while ((id = get_next_line(last == 1? fd: fd2, &line))>0)
	{
		printf("|  %2d  | |  %2d  | %s\n", id, last, line);
		if (last == 1)
			last = 2;
		else
			last = 1;
		free(line);
	}
	printf("|%4s%2d%4s| %s\n","", id,"", line);
		free(line);
	sleep(15);
}
