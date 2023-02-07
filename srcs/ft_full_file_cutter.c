/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_full_file_cutter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:50:00 by zharzi            #+#    #+#             */
/*   Updated: 2023/02/07 12:27:50 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_cutter.h"

typedef struct s_seq {
	char			*line;
	struct s_seq	*next;
}					t_seq;

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
		ft_true_free((void **)&buffer);
		buffer = get_next_line(fd);
	}
	close (fd);
	return (n);
}

t_seq	*ft_new_seq(char *line)
{
	t_seq	*new;

	new = (t_seq *)malloc(sizeof(t_seq));
	if (!new)
		return (NULL);
	new->line = ft_strdup(line);
	new->next = NULL;
	return (new);
}

void	ft_to_end_of_seq(t_seq **includes, char *buffer)
{
	t_seq	*lst;
	t_seq	*tmp;

	lst = *includes;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
	}
	tmp->next = ft_new_seq(buffer);
}

t_seq	*ft_get_includes(char *filename)
{
	t_seq	*includes;
	int		fd;
	char	*buffer;

	includes = NULL;
	fd = open(filename, O_RDONLY);
	if (fd)
	{
		buffer = get_next_line(fd);
		while (buffer)
		{
			if (!ft_strncmp(buffer, "#include ", ft_strlen("#include ")))
			{
				if (!includes)
					includes = ft_new_seq(buffer);
				else
					ft_to_end_of_seq(&includes, buffer);
			}
			ft_true_free((void **)&buffer);
			buffer = get_next_line(fd);
		}
		close (fd);
	}
	return (includes);
}

void	ft_show_seq(t_seq *seq)
{
	int	i;

	i = 0;
	while (seq)
	{
		i++;
		printf("%-3d : %s", i, seq->line);
		seq = seq->next;
	}
	printf("\n");
}

void	ft_free_lst(t_seq *seq)
{
	t_seq	*tmp;

	while (seq)
	{
		ft_true_free((void **)&seq->line);
		tmp = seq;
		seq = seq->next;
		ft_true_free((void **)&tmp);
	}
}

t_seq	**ft_init_functions(int nb)
{
	t_seq	**fun;
	int		i;

	i = -1;
	fun = (t_seq **)malloc(sizeof(t_seq *) * (nb + 1));
	if (!fun)
		return (NULL);
	while (++i <= nb)
		fun[i] = NULL;
	return (fun);
}

int	ft_set_fd_position(char *filename, t_seq *inc, char **buffer)
{
	int		fd;
	char	*tmp;

	fd = open(filename, O_RDONLY);
	tmp = get_next_line(fd);
	while (inc)
	{
		while (tmp && ft_strncmp(tmp, inc->line, ft_strlen(inc->line)))
		{
			ft_true_free((void **)&tmp);
			tmp = get_next_line(fd);
		}
		inc = inc->next;
	}
	if (tmp)
	{
		ft_true_free((void **)&tmp);
		tmp = get_next_line(fd);
		*buffer = tmp;
		return (fd);
	}
	close(fd);
	return (-1);
}

void	ft_put_inc_to_fun(t_seq **new, t_seq *inc)
{
	while (inc)
	{
		ft_to_end_of_seq(new, inc->line);
		inc = inc->next;
	}
}

t_seq	*ft_get_function(int fd, t_seq *inc, char **buffer)
{
	t_seq	*new;
	char	*buff;

	buff = ft_strdup(*buffer);
	free(*buffer);
	new = ft_new_seq(inc->line);
	ft_put_inc_to_fun(&new, inc->next);
	while (buff && buff[0] != '}')
	{
		ft_to_end_of_seq(&new, buff);
		ft_true_free((void **)&buff);
		buff = get_next_line(fd);
	}
	if (buff && buff[0] == '}')
	{
		ft_to_end_of_seq(&new, buff);
		ft_true_free((void **)&buff);
		*buffer = get_next_line(fd);
	}
	return (new);
}

void	ft_get_file_content(char *filename, t_seq **fun, t_seq *inc, int nb)
{
	int		i;
	int		fd;
	char	*buffer;

	fd = -1;
	i = 0;
	buffer = NULL;
	if (inc && inc->line[0] != '\0')
		fd = ft_set_fd_position(filename, inc, &buffer);
	if (fd < 0)
		exit(1);
	while (i < nb)
	{
		fun[i] = ft_get_function(fd, inc, &buffer);
		ft_show_seq(fun[i]);///////////////////////////////////////
		i++;
	}
}

char	*ft_get_name(t_seq *fun)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	while (fun && !ft_isalpha(fun->line[0]))
		fun = fun->next;
	if (fun && ft_isalpha(fun->line[0]))
	{
		tmp = fun->line;
		while (tmp && tmp[0] && ft_isalpha(tmp[0]))
			tmp += 1;
		while (tmp && tmp[0] && ft_strchr("\t *", tmp[0]))
			tmp += 1;
		if (tmp && tmp[0] && ft_isalpha(tmp[0]))
			while (tmp && tmp[i] && tmp[i] != '(')
				i++;
		if (tmp && tmp[i] && tmp[i] == '(')
		{
			tmp[i] = '.';
			tmp[i + 1] = 'c';
			if (tmp[i + 2])
				tmp[i + 2] = '\0';
			tmp = ft_strdup(tmp);
			return (tmp);
		}
	}
	return (NULL);
}

char	**ft_get_fun_names(t_seq **fun, int nb)
{
	char	**names;
	int		i;

	i = 0;
	names = (char **)malloc(sizeof(char *) * (nb + 1));
	if (!names)
		return (NULL);
	names[nb] = NULL;
	while (i < nb)
	{
		names[i] = ft_get_name(fun[i]);
		i++;
	}
	return (names);
}

void	ft_file_cutter(char **argv)
{
	t_seq	**fun;
	t_seq	*includes;
	int		nb;
	char	**fun_names;

	nb = ft_count_functions(argv[1]);
	printf("Number of functions : %d\n", nb);
	includes = ft_get_includes(argv[1]);
	if (!includes)
		includes = ft_new_seq("");
	printf("List of includes :\n");
	ft_show_seq(includes);////////////////////////////////////
	fun = ft_init_functions(nb);
	if (fun)
	{
		ft_get_file_content(argv[1], fun, includes, nb);
		fun_names = ft_get_fun_names(fun, nb);
		ft_show_strs(fun_names);
	}
	ft_free_lst(includes);
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
