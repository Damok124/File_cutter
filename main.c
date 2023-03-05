/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:30:42 by zharzi            #+#    #+#             */
/*   Updated: 2023/03/05 22:58:53 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_cutter.h"

int	main(int ac, char **argv)
{
	int	err_no;

	if (ft_cutter_parsing(ac, argv, &err_no))
		ft_file_cutter(argv);
	else
		ft_cutter_perror(err_no);
	return (0);
}
