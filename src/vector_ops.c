/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:43:15 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/03/20 13:13:07 by vvasiuko         ###   ########.fr       */
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

float	v_len(t_vec3 vec)
{
	return (sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

float	v_dot(t_vec3 vec, t_vec3 vec2)
{
	float	res;

	res = vec.x * vec2.x + vec.y * vec2.y + vec.z * vec2.z;
	return (res);
}

t_vec3	v_cross(t_vec3 vec, t_vec3 vec2)
{
	t_vec3	res;

	res.x = vec.y * vec2.z - vec.z * vec2.y;
	res.y = vec.z * vec2.x - vec.x * vec2.z;
	res.z = vec.x * vec2.y - vec.y * vec2.x;
	return (res);
}

void	v_add_inplace(t_vec3 *vec, t_vec3 vec2)
{
	vec->x += vec2.x;
	vec->y += vec2.y;
	vec->z += vec2.z;
}

void	v_subtract_inplace(t_vec3 *vec, t_vec3 vec2)
{
	vec->x -= vec2.x;
	vec->y -= vec2.y;
	vec->z -= vec2.z;
}

void	v_scale_inplace(t_vec3 *vec, float c)
{
	vec->x *= c;
	vec->y *= c;
	vec->z *= c;
}