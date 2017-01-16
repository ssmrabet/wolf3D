/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smrabet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 22:42:47 by smrabet           #+#    #+#             */
/*   Updated: 2017/01/06 14:11:37 by smrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf.h"

void		trace_pixel(int x, int y, t_env *e)
{
	int		t;
	int		*i;

	if (y < Y && x < X && x > 0 && y > 0)
	{
		t = x * 4 + y * e->img_line;
		i = (int *)&e->data_img[t];
		*i = e->color;
	}
}

void		colors(t_env *e)
{
	if (e->hour < 18)
	{
		if (e->side == 0 && e->raydirx > 0)
			e->color = 0x5B1042;
		if (e->side == 0 && e->raydirx < 0)
			e->color = 0xC70039;
		if (e->side == 1 && e->raydiry < 0)
			e->color = 0x900C3E;
		if (e->side == 1 && e->raydiry > 0)
			e->color = 0xFF5733;
	}
	else
	{
		if (e->side == 0 && e->raydirx > 0)
			e->color = 0x210518;
		if (e->side == 0 && e->raydirx < 0)
			e->color = 0x4F0017;
		if (e->side == 1 && e->raydiry < 0)
			e->color = 0x330416;
		if (e->side == 1 && e->raydiry > 0)
			e->color = 0x91311D;
	}
}

void		trace_line(t_env *e)
{
	while (e->y < e->drawstart)
	{
		e->color = (e->hour < 18) ? 0x00FFFFF : 0x001848;
		trace_pixel(e->i, e->y, e);
		e->y++;
	}
	e->y = e->drawstart;
	while (e->y < e->drawend)
	{
		colors(e);
		trace_pixel(e->i, e->y, e);
		e->y++;
	}
	e->y = e->drawend;
	while (e->y < Y)
	{
		e->color = (e->hour < 18) ? 0xEEEEEE : 0x605F5F;
		trace_pixel(e->i, e->y, e);
		e->y++;
	}
}

int			change(t_env *e)
{
	e->hour = hour_result(e);
	e->i = 0;
	while (e->i < X)
	{
		ray_position(e);
		calcul_step(e);
		perform_dda(e);
		distance_project(e);
		e->y = 0;
		trace_line(e);
		e->i++;
	}
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	menu(e);
	return (0);
}

int			main(int ac, char **av)
{
	t_env	e;

	if (ac == 1)
	{
		e.mlx = mlx_init();
		e.win = mlx_new_window(e.mlx, X, Y, "WOLF3D");
		e.img = NULL;
		init_env(&e);
		e.img = mlx_new_image(e.mlx, X, Y);
		e.data_img = mlx_get_data_addr(e.img, &(e.bpp),
			&(e.img_line), &(e.end));
		mlx_loop_hook(e.mlx, change, &e);
		mlx_hook(e.win, 2, 3, &key, &e);
		mlx_hook(e.win, 17, 18, close_win, e.mlx);
		mlx_loop(e.mlx);
		mlx_destroy_window(e.mlx, e.win);
	}
	else
		ft_putstr_fd("./wolf\n", 2);
	return (0);
}
