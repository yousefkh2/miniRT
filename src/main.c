/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:42:43 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/03/21 12:00:04 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static void	init_viewport(t_data *data)
{
	t_vec3 u;
	t_vec3 v;
	t_vec3 w;
	t_vec3 world_up;

	world_up = (t_vec3){0.f, 1.f, 0.f};
	w = data->scene->camera.norm; //check if normalised when parsing and apply v_unit if not
	u = v_unit(v_cross(world_up, w));
	v = v_cross(w, u);
	data->viewport_h = 2 * data->focal_len * tanf(data->scene->camera.fov_rad
			/ 2);
	data->viewport_w = data->viewport_h * data->aspect_ratio;
	// data->viewport_u = (t_vec3){data->viewport_w, 0, 0}; //viewport_width * u
	// data->viewport_v = (t_vec3){0, -1 * data->viewport_h, 0}; // viewport_height * -v
	data->viewport_u = v_scale(u, data->viewport_w);
	data->viewport_v = v_scale(v, -1 * data->viewport_h);
	data->pixel_delta_u = v_scale(data->viewport_u, 1.f / data->w);
	data->pixel_delta_v = v_scale(data->viewport_v, 1.f / data->h);
	data->viewport_u_l = data->scene->camera.view_point;
	// v_subtract_inplace(&data->viewport_u_l, (t_vec3){0, 0, data->focal_len}); // (focal_length * w) for positioning
	v_subtract_inplace(&data->viewport_u_l, v_scale(w, data->focal_len));
	v_subtract_inplace(&data->viewport_u_l, v_scale(data->viewport_u, 0.5f));
	v_subtract_inplace(&data->viewport_u_l, v_scale(data->viewport_v, 0.5f));
	data->pixel00_loc = data->viewport_u_l;
	v_add_inplace(&data->pixel00_loc, v_scale(data->pixel_delta_u, 0.5f));
	v_add_inplace(&data->pixel00_loc, v_scale(data->pixel_delta_v, 0.5f));
}

static int	init_data(t_data *data, char *file)
{
	if (rt_file(file) != 0)
		return (error_message("Error\nwrong file extension: must be .rt"));
	//----- parsing filler ------
	data->scene = (t_scene *)calloc(1, sizeof(t_scene));
	setup_scene(data->scene);
	// --------------------------
	data->w = WIDTH;  // can be some check here actually
	data->h = HEIGHT; // can be some check here actually
	data->aspect_ratio = (float)data->w / data->h;
	data->focal_len = 1.f;
	init_viewport(data);
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 2)
		return (error_message("Error\nput .rt path after ./miniRT\n"));
	if (init_data(&data, argv[1]) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, data.w, data.h, "miniRT");
	data.img.img = mlx_new_image(data.mlx, data.w, data.h);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bpp,
			&data.img.size_l, &data.img.endian);
	put_pixels(&data);
	mlx_put_image_to_window(data.mlx, data.window, data.img.img, 0, 0);
	mlx_hook(data.window, 17, 0, clean_exit, &data);
	mlx_hook(data.window, 2, 1L << 0, key_hook, &data);
	mlx_loop(data.mlx);
	return (EXIT_SUCCESS);
}
