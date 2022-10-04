/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testprogram.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 02:33:52 by coder             #+#    #+#             */
/*   Updated: 2022/10/02 22:04:52 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	main (int argc, char *argv[])
{
	int i = 0;
	printf ("argc: %d\n", argc);
	while (argv[i])
	{
		printf ("arg[%d]: %s\n", i, argv[i]);
		i++;
	}
	printf ("Saindo com exit code [%d].\n", i);
	printf ("Há tanta suavidade em nada dizer e tudo entender...\n");
	exit (i);
}
