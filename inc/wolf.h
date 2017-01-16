/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smrabet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 15:48:30 by smrabet           #+#    #+#             */
/*   Updated: 2017/01/06 14:23:34 by smrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include "../libft/libft.h"
# include "mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <math.h>

# define MAPH 19
# define MAPW 22
# define Y 1000
# define X 1000
# define ESC 53
# define R 15
# define LEFT 123
# define RIGHT 124
# define UP 126
# define DOWN 125
# define S 1
# define D 2
# define T 17
# define YY 16

typedef struct		s_env
{
	time_t			time;
	struct tm		*timeinfo;
	int				hour;
	int				y;
	void			*mlx;
	void			*win;
	void			*img;
	char			*data_img;
	int				bpp;
	int				img_line;
	int				end;
	int				color;
	int				mapx;
	int				mapy;
	int				stepx;
	int				stepy;
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			rayposx;
	double			rayposy;
	double			raydirx;
	double			raydiry;
	double			planex;
	double			planey;
	double			camerax;
	double			sidedistx;
	double			sidedisty;
	double			deltadistx;
	double			deltadisty;
	float			move;
	float			rot;
	double			pwall;
	int				lineh;
	int				drawstart;
	int				drawend;
	int				hit;
	int				side;
	int				i;
	double			olddirx;
	double			oldplanex;
}					t_env;

void				colors(t_env *e);
void				trace_pixel(int x, int y, t_env *e);
void				trace_line(t_env *e);
int					change(t_env *e);

int					map(int x, int y);
void				ray_position(t_env *e);
void				calcul_step(t_env *e);
void				perform_dda(t_env *e);
void				distance_project(t_env *e);

void				init_env(t_env *e);
int					key(int key, t_env *e);
int					hour_result(t_env *e);
void				menu(t_env *e);
int					close_win(t_env *e);

#endif
