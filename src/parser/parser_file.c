/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_username <your_email@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by your_username    #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by your_username   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "includes/cube.h"

typedef struct s_element {
    char    *prefix;
    int     prefix_len;
    bool    is_texture;
    int     index;
} t_element;

static const t_element g_elements[] = {
    {"NO ", 3, true, 0},
    {"SO ", 3, true, 1},
    {"WE ", 3, true, 2},
    {"EA ", 3, true, 3},
    {"F ", 2, false, 4},
    {"C ", 2, false, 5}
};

char **copy_map_fixed(char *first_line, int fd, int *map_size)
{
    char **map;
    char *line;
    char *trimmed;
    int i;

    i = 0;
    map = allocate_map();
    if (!map)
        return (NULL);
    line = first_line;
    while (line && i < MAX_MAP_SIZE)
    {
        trimmed = trim_whitespace(line);
        map[i] = malloc(ft_strlen(trimmed) + 1);
        if (!map[i])
        {
            free(trimmed);
            free_map_partial(map, i);
            return (NULL);
        }
        ft_strcpy(map[i], trimmed);
        free(trimmed);
        free(line);
        line = get_next_line(fd);
        i++;
    }
    free(line);
    map[i] = NULL;
    *map_size = i;
    return (map);
}

void process_map(t_cube *cube, char *line, int fd, t_collector **collector)
{
    char **map;
    int map_size;

    map = copy_map_fixed(line, fd, &map_size);
    if (!map)
    {
        print_error(1, "Error allocating memory for map");
        exit(1);
    }
    map_to_struct(cube, map, collector);
}

static bool process_element(t_cube *cube, char *trimmed, 
                          t_collector **collector, int *found)
{
    int i;
    bool success;

    i = 0;
    while (i < 6)
    {
        if (!found[i] && ft_strncmp(trimmed, g_elements[i].prefix, 
                                  g_elements[i].prefix_len) == 0)
        {
            if (g_elements[i].is_texture)
                success = process_texture_lines(cube, trimmed, 
                                              g_elements[i].index, collector);
            else
                success = process_rgb_lines(cube, trimmed, 
                                          g_elements[i].index + 1);
            if (success)
                found[i] = 1;
            return (true);
        }
        i++;
    }
    return (false);
}

static bool find_elements(t_cube *cube, int fd, 
                         t_collector **collector, char **line_out)
{
    char *line;
    char *trimmed;
    int found[6] = {0, 0, 0, 0, 0, 0};
    int i;

    line = get_next_line(fd);
    while (line)
    {
        trimmed = trim_whitespace(line);
        if (trimmed && ft_strlen(trimmed) > 0)
        {
            process_element(cube, trimmed, collector, found);
            for (i = 0; i < 6 && found[i]; i++);
            if (i == 6)
            {
                free(trimmed);
                *line_out = get_next_line(fd);
                free(line);
                return (true);
            }
        }
        free(trimmed);
        free(line);
        line = get_next_line(fd);
    }
    return (false);
}

static bool process_elements(t_cube *cube, int fd, 
                           t_collector **collector, char **last_line)
{
    char *line;
    char *trimmed;
    bool ok;

    ok = find_elements(cube, fd, collector, &line);
    if (!ok)
    {
        print_error(1, "Missing or invalid elements");
        return (false);
    }
    trimmed = trim_whitespace(line);
    if (!trimmed || ft_strlen(trimmed) != 0)
    {
        print_error(1, "Expected blank line before map");
        if (trimmed)
            free(trimmed);
        if (line)
            free(line);
        return (false);
    }
    free(trimmed);
    *last_line = line;
    return (true);
}

bool process_file(t_cube *cube, int fd, t_collector **collector)
{
    char *line;

    if (!process_elements(cube, fd, collector, &line))
        return (false);
    process_map(cube, line, fd, collector);
    return (true);
}

bool validation_file(t_cube *cube, char *file, t_collector **collector)
{
    int fd;

    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        print_error(2, file, "Cannot open file");
        return (false);
    }
    if (!process_file(cube, fd, collector))
        return (false);
    close(fd);
    return (true);
}