/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smrabet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 00:25:14 by smrabet           #+#    #+#             */
/*   Updated: 2017/01/06 14:14:06 by smrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf.h"

void		init_env(t_env *e)
{
	e->posx = 11;
	e->posy = 19;
	e->dirx = -1;
	e->diry = 0;
	e->planex = 0;
	e->planey = 0.60;
	e->move = 0.15;
	e->rot = 0.1;
}

int			hour_result(t_env *e)
{
	time(&e->time);
	e->timeinfo = localtime(&e->time);
	return (e->timeinfo->tm_hour);
}

int			close_win(t_env *e)
{
	(void)e->mlx;
	exit(EXIT_SUCCESS);
	return (0);
}

void		key1(int key, t_env *e)
{
	if (key == RIGHT)
	{
		e->olddirx = e->dirx;
		e->dirx = e->dirx * cos(-e->rot) - e->diry * sin(-e->rot);
		e->diry = e->olddirx * sin(-e->rot) + e->diry * cos(-e->rot);
		e->oldplanex = e->planex;
		e->planex = e->planex * cos(-e->rot) - e->planey * sin(-e->rot);
		e->planey = e->oldplanex * sin(-e->rot) + e->planey * cos(-e->rot);
	}
	if (key == LEFT)
	{
		e->olddirx = e->dirx;
		e->dirx = e->dirx * cos(e->rot) - e->diry * sin(e->rot);
		e->diry = e->olddirx * sin(e->rot) + e->diry * cos(e->rot);
		e->oldplanex = e->planex;
		e->planex = e->planex * cos(e->rot) - e->planey * sin(e->rot);
		e->planey = e->oldplanex * sin(e->rot) + e->planey * cos(e->rot);
	}
	e->move += (key == S && e->move < 0.7) ? 0.1 : 0;
	e->move -= (key == D && e->move > 0.1) ? 0.1 : 0;
	e->rot += (key == T && e->rot < 0.7) ? 0.1 : 0;
	e->rot -= (key == YY && e->rot > 0.2) ? 0.1 : 0;
}

int			key(int key, t_env *e)
{
	if (key == UP)
	{
		if ((map(((int)(e->posx + e->dirx * e->move)), ((int)(e->posy)))) == 0)
			e->posx += e->dirx * e->move;
		if ((map(((int)(e->posx)), ((int)(e->posy + e->diry * e->move)))) == 0)
			e->posy += e->diry * e->move;
	}
	if (key == DOWN)
	{
		if ((map(((int)(e->posx - e->dirx * e->move)), ((int)(e->posy)))) == 0)
			e->posx -= e->dirx * e->move;
		if ((map(((int)(e->posx)), ((int)(e->posy - e->diry * e->move)))) == 0)
			e->posy -= e->diry * e->move;
	}
	key1(key, e);
	if (key == ESC)
		close_win(e);
	if (key == R)
		init_env(e);
	return (0);
}
