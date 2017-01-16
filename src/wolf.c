/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smrabet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 12:34:39 by smrabet           #+#    #+#             */
/*   Updated: 2017/01/06 14:23:39 by smrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf.h"

int				map(int map_x, int map_y)
{
	static int	worldmap[MAPH][MAPW] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 1},
		{1, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 1},
		{1, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 1},
		{1, 0, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 4, 4, 4, 4, 4, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};

	return (worldmap[map_x][map_y]);
}

void			ray_position(t_env *e)
{
	e->camerax = 2 * e->i / (double)X - 1;
	e->rayposx = e->posx;
	e->rayposy = e->posy;
	e->raydirx = e->dirx + e->planex * e->camerax;
	e->raydiry = e->diry + e->planey * e->camerax;
	e->mapx = (int)e->rayposx;
	e->mapy = (int)e->rayposy;
	e->deltadistx = sqrt(1 + (e->raydiry * e->raydiry)
			/ (e->raydirx * e->raydirx));
	e->deltadisty = sqrt(1 + (e->raydirx * e->raydirx)
			/ (e->raydiry * e->raydiry));
	e->hit = 0;
}

void			calcul_step(t_env *e)
{
	if (e->raydirx < 0)
	{
		e->stepx = -1;
		e->sidedistx = (e->rayposx - e->mapx) * e->deltadistx;
	}
	else
	{
		e->stepx = 1;
		e->sidedistx = (e->mapx + 1.0 - e->rayposx) * e->deltadistx;
	}
	if (e->raydiry < 0)
	{
		e->stepy = -1;
		e->sidedisty = (e->rayposy - e->mapy) * e->deltadisty;
	}
	else
	{
		e->stepy = 1;
		e->sidedisty = (e->mapy + 1.0 - e->rayposy) * e->deltadisty;
	}
}

void			perform_dda(t_env *e)
{
	while (e->hit == 0)
	{
		if (e->sidedistx < e->sidedisty)
		{
			e->sidedistx += e->deltadistx;
			e->mapx += e->stepx;
			e->side = 0;
		}
		else
		{
			e->sidedisty += e->deltadisty;
			e->mapy += e->stepy;
			e->side = 1;
		}
		if ((map(e->mapx, e->mapy)) > 0)
			e->hit = 1;
	}
}

void			distance_project(t_env *e)
{
	if (e->side == 0)
	{
		e->pwall = (e->mapx - e->rayposx
			+ (1 - e->stepx) / 2) / e->raydirx;
	}
	else
	{
		e->pwall = (e->mapy - e->rayposy
			+ (1 - e->stepy) / 2) / e->raydiry;
	}
	e->lineh = (int)(Y / e->pwall);
	e->drawstart = (-1 * e->lineh) / 2 + Y / 2;
	if (e->drawstart < 0)
		e->drawstart = 0;
	e->drawend = e->lineh / 2 + Y / 2;
	if (e->drawend >= Y)
		e->drawend = Y - 1;
}
