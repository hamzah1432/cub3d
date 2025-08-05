/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halmuhis <halmuhis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:19:39 by halmuhis          #+#    #+#             */
/*   Updated: 2025/07/22 15:22:31 by halmuhis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main()
{
    void *mlx = mlx_init();
    if (!mlx) return 1;

    void *win = mlx_new_window(mlx, 800, 600, "Pixel Test");
    if (!win) return 1;

    // Draw a white pixel at (100, 100)
    mlx_pixel_put(mlx, win, 0, 0, 0xFFFFFF);
	for (int dx = 0; dx < 30; dx++)
    for (int dy = 0; dy < 50; dy++)
        mlx_pixel_put(mlx, win, 100 + dx, 100 + dy, 0xFFFFFF);

    mlx_loop(mlx);

    return 0;
}