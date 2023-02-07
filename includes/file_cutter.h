/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_cutter.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:47:31 by zharzi            #+#    #+#             */
/*   Updated: 2023/02/06 17:12:43 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_CUTTER_H
# define FILE_CUTTER_H

# include "libft.h"
# include "ft_printf.h"
# include <stdio.h>

int		ft_cutter_parsing(int ac, char **argv, int *err_no);
void	ft_cutter_perror(int err_no);
void	ft_file_cutter(char **argv);

#endif
