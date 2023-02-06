/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_full_file_cutter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:50:00 by zharzi            #+#    #+#             */
/*   Updated: 2023/02/06 16:22:52 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_cutter.h"

typedef struct s_inc {
	char			*line;
	struct s_inc	*next;
}					t_inc;

int	ft_count_functions(char *filename)
{
	int		n;
	int		fd;
	char	*buffer;

	n = 0;
	fd = open(filename, O_RDONLY);
	printf("%s on fd %d\n", filename, fd);
	buffer = get_next_line(fd);
	while (buffer)
	{
		if (buffer[0] == '}')
			n++;
		buffer = get_next_line(fd);
	}
	close (fd);
	return (n);
}

t_inc	*ft_new_includes(char *line)
{
	t_inc	*new;

	new = (t_inc *)malloc(sizeof(t_inc));
	if (!new)
		return (NULL);
	new->line = ft_strdup(line);
	new->next = NULL;
	return (new);
}

void	ft_includes_to_end(t_inc **includes, char *buffer)
{
	t_inc	*lst;
	t_inc	*tmp;

	lst = *includes;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
	}
	tmp->next = ft_new_includes(buffer);
}

t_inc	*ft_get_includes(char *filename)
{
	t_inc	*includes;
	int		fd;
	char	*buffer;

	includes = NULL;
	fd = open(filename, O_RDONLY);
	if (fd)
	{
		buffer = get_next_line(fd);
		if (ft_strncmp(buffer, "#include ", ft_strlen("#include ")))
			includes = ft_new_includes(buffer);
		while (buffer)
		{
			if (ft_strncmp(buffer, "#include ", ft_strlen("#include ")))
			{
				if (!includes)
					includes = ft_new_includes(buffer);
				else
					ft_includes_to_end(&includes, buffer);
			}
			ft_true_free((void **)&buffer);
			buffer = get_next_line(fd);
		}
		close (fd);
	}
	else
		printf("Bad fd.\n");
	return (includes);
}

char	**ft_init_all(int size)
{
	char	**all;

	all = (char **)malloc(sizeof(char *) * (size + 1));
	if (!all)
		return (NULL);
	all[size] = NULL;
	return (all);
}

void	ft_show_includes(t_inc *includes)
{
	int	i;

	i = 0;
	while (includes)
	{
		i++;
		printf("%d : [%s]\n", i, includes->line);
		includes = includes->next;
	}
}

void	ft_cutter(char **argv)
{
	char	**all;
	t_inc	*includes;
	int		nb;

	nb = ft_count_functions(argv[1]);
	printf("%d\n", nb);
	all = ft_init_all(nb);
	includes = ft_get_includes(argv[1]);
	ft_show_includes(includes);
	if (all)
	{
		ft_full_free((void **)all);
	}
	else
		printf("Error. Malloc failed.\n");
}

void	ft_cutter_perror(int err_no)
{
	printf("Error. ");
	if (err_no == 1)
		printf("Wrong number of arguments\n");
	if (err_no == 2)
		printf("Wrong arguments extension.\n");
	if (err_no == 3)
		printf("C file not found\n");
	if (err_no == 4)
		printf("No access to C file\n");
}

int	ft_cutter_parsing(int ac, char **argv, int *err_no)
{
	int	err;
	int	check;

	err = 0;
	check = 1;
	if (++err && ac != 2)
		check = 0;
	if (check && ++err && (!ft_check_extension(argv[1], ".c")))
		check = 0;
	if (check && ++err && access(argv[1], F_OK))
		check = 0;
	if (check && ++err && access(argv[1], R_OK))
		check = 0;
	*err_no = err;
	return (check);
}
