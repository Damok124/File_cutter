/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_inc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 00:22:28 by zharzi            #+#    #+#             */
/*   Updated: 2023/02/07 12:07:58 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stddef.h>
// #include <unistd.h>
// #include <string.h>
// #include <stdint.h>
// #include <stdlib.h>
// #include <limits.h>
// #include <stdarg.h>
// #include <fcntl.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>
// #include <stdio.h>

int	main(void)
{
	printf("%d", mkdir("./SUCCESS/", 0775));
	return (0);
}
