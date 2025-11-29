/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_username <your_email@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by your_username    #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by your_username   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"




bool	flood_fill(t_map *map)
{ 
    int i;
    int j;
    
    i = 0;

    while (map)
    {
        j = 0;
        while(map[i][j])
        {
            printf("%c", map[i][j]);
            j++;
        }
        i++;
    }
}