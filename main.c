/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:30:42 by zharzi            #+#    #+#             */
/*   Updated: 2023/02/06 17:10:37 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_cutter.h"

//prend en parametre 1 le nom du fichier a decouper avec check .c				done
//doit lire un fichier,
//doit detecter l'include et le strdup
//doit stocker les char *suivant l'include jusqu'a l'acc fermante dans un char **
//lorsqu'il detecte l'accolade fermante il recupere le nom de la fonction et join .c
//stock le nom de toutes les fonctions
//check si un nom du lot existe deja dans le dossier et exit si oui
//si RAS, relire fichier
//lorsqu'il detecte le nom de l'include, il ouvre un fichier au nom prevu,
//puis il putstr fd dans le fichier jusqu'a detectection du prochain include
//doit close le fichier
//

int	main(int ac, char **argv)
{
	int	err_no;

	if (ft_cutter_parsing(ac, argv, &err_no))
		ft_file_cutter(argv);
	else
		ft_cutter_perror(err_no);
	return (0);
}
