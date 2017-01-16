/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smrabet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 11:59:16 by smrabet           #+#    #+#             */
/*   Updated: 2017/01/06 14:06:54 by smrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf.h"

void		menu(t_env *e)
{
	mlx_string_put(e->mlx, e->win, 800, 5, 0XFFFFFF, "Rotation Speed: T/Y");
	mlx_string_put(e->mlx, e->win, 800, 35, 0XFFFFFF, "Move Speed: S/D");
	mlx_string_put(e->mlx, e->win, 800, 70, 0XFFFFFF, "Reset: R");
}
