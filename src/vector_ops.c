/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:43:15 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/03/23 11:15:40 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_vec3	v_add(t_vec3 vec, t_vec3 vec2)
{
	t_vec3	res;

	res = vec;
	res.x += vec2.x;
	res.y += vec2.y;
	res.z += vec2.z;
	return (res);
}

t_vec3	v_subtract(t_vec3 vec, t_vec3 vec2)
{
	t_vec3	res;

	res = vec;
	res.x -= vec2.x;
	res.y -= vec2.y;
	res.z -= vec2.z;
	return (res);
}

t_vec3	v_scale(t_vec3 vec, float c)
{
	t_vec3	res;

	res.x = vec.x * c;
	res.y = vec.y * c;
	res.z = vec.z * c;
	return (res);
}
