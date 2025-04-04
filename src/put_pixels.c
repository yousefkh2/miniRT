/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:43:07 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/03/23 15:49:04 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_ray	send_cam_ray(t_data *data, int x, int y)
{
	t_ray	ray;
	t_vec3	pixel_center;

	ray.start = data->scene->camera.view_point;
	pixel_center = data->pixel00_loc;
	v_add_inplace(&pixel_center, v_scale(data->pixel_delta_u, (float)x));
	v_add_inplace(&pixel_center, v_scale(data->pixel_delta_v, (float)y));
	ray.dir = v_subtract(pixel_center, ray.start);
	return (ray);
}

void	put_pixel_to_img(t_img *img, int x, int y, int colour)
{
	char	*dst;

	dst = img->addr + (y * img->size_l + x * (img->bpp / 8));
	*(unsigned int *)dst = colour;
}

static t_hit	hit_object(t_ray ray, t_obj *curr)
{
	t_hit	hit;

	if (curr->type == SPHERE)
		hit = hit_sphere(ray, curr);
	else if (curr->type == PLANE)
		hit = hit_plane(ray, curr);
	// else if (curr->type == CYLINDER)
	// 	hit = hit_cylinder(ray, curr);
	hit.front_face = v_dot(ray.dir, hit.normal) < 0;
	if (!hit.front_face)
		v_scale_inplace(&hit.normal, -1.f); //remove this thing to make plane not render from the back
	hit.colour = curr->colour;
	return (hit);
}

static bool	in_shadow(t_data *data, t_vec3 point, t_light light)
{
	t_ray	shadow_ray;
	t_obj	*curr;
	float	light_distance;
	float	t;

	shadow_ray.start = point;
	shadow_ray.dir = v_unit(v_subtract(light.pos, point));
	light_distance = v_len(v_subtract(light.pos, point));

	curr = data->scene->objects;
	while (curr)
	{
		t = hit_object(shadow_ray, curr).t;
		if (!isnan(t) && t > 0.001f && t < light_distance)
			return (true);
		curr = curr->next;
	}
	return (false);
}

static t_colour	hit_objects(t_data *data, t_ray ray)
{
	t_hit	hit;
	t_hit	closest_hit;
	t_obj	*curr;

	closest_hit.t = INFINITY;
	closest_hit.colour = (t_colour){0, 0, 0, 0.f}; //background colour
	curr = data->scene->objects;
	while (curr)
	{
		hit = hit_object(ray, curr);
		if (!isnan(hit.t) && hit.t >= 1e-6)
		{
			if (hit.t < closest_hit.t)
				closest_hit = hit;
		}
		curr = curr->next;
	}
	if (closest_hit.t != INFINITY)
	{
		t_vec3 light_dir = v_unit(v_subtract(data->scene->light.pos, v_at(ray, closest_hit.t)));
		float light_intensity = fmax(0.0f, v_dot(closest_hit.normal, light_dir)) * data->scene->light.colour.ratio;
		if (!in_shadow(data, v_at(ray, closest_hit.t), data->scene->light))
			closest_hit.colour = c_scale(closest_hit.colour, light_intensity);
		else
			closest_hit.colour = c_scale(closest_hit.colour, light_intensity * 0.2f);
		add_ambient(&closest_hit.colour, data->scene->a_light);
	}
	return (closest_hit.colour);
}

void	put_pixels(t_data *data)
{
	t_colour	colour;
	t_ray		ray;
	int			x;
	int			y;

	y = 0;
	while (y < data->h)
	// while (y < 10)
	{
		x = 0;
		while (x < data->w)
		// while (x < 2)
		{
			ray = send_cam_ray(data, x, y);
			colour = hit_objects(data, ray);
			put_pixel_to_img(&data->img, x, y, rgb_to_int(colour));
			x++;
		}
		y++;
	}
}
