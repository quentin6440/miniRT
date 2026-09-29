/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 13:31:14 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/09/29 11:33:33 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/* 1. INCLUDES */
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "vector.h"

/* 2. DEFINES & KEYCODES */
# define ESC 65307

# define EPSILON 1e-6

# define VEC_INVALID 1
# define VEC_NOT_NORMALIZED 2

/* 3. STRUCTURES */

typedef struct s_img
{
	void	*p;
	char	*data;
	int		line_len;
	int		bits_per_pixel;
	int		endian;
}	t_img;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	dir;
}	t_ray;

typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	dir;
	double	fov;
}	t_camera;

typedef struct s_ambient
{
	double	ratio;
	t_vec3	color;
}	t_ambient;

typedef struct s_light
{
	t_vec3	pos;
	double	ratio;
	t_vec3	color;
}	t_light;

typedef enum e_type
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_type;

typedef struct s_obj
{
	t_type			type;
	t_vec3			pos;
	t_vec3			dir;
	double			diameter;
	double			height;
	t_vec3			color;
	struct s_obj	*next;
}	t_obj;

/*
 * Un "hit" représente le résultat d'une intersection.
 *
 * valid = 1  -> le rayon a touché un objet
 * valid = 0  -> aucun objet touché
 *
 * t     -> distance sur le rayon
 * point -> point exact où le rayon touche l'objet
 * obj   -> objet touché
 */
typedef struct s_hit
{
	int		valid;
	double	t;
	t_vec3	point;
	t_obj	*obj;
}	t_hit;

typedef struct s_scene
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		*img_ptr;
	int			win_width;
	int			win_height;
	t_camera	camera;
	t_ambient	ambient;
	t_light		light;
	t_obj		*objects;
	int			has_ambient;
	int			has_camera;
	int			has_light;
}	t_scene;

typedef struct s_quadratic
{
	double	a;
	double	b;
	double	c;
}	t_quadratic;

typedef struct s_basis
{
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
}	t_basis;

typedef struct s_ray_view
{
	t_basis	basis;
	double	aspect_ratio;
	double	fov_adjustment;
}	t_ray_view;

typedef struct s_parse_error
{
	int			line;
	const char	*message;
}	t_parse_error;

typedef struct s_global_parser
{
	int			*seen;
	int			(*parser)(char **, t_scene *, t_parse_error *);
	const char	*duplicate_message;
}	t_global_parser;

/* --- PARSING --- */
int		ft_parse_rt(int fd, t_scene *scene, t_parse_error *error);
int		ft_parse_line(char **tokens, t_scene *scene,
			t_parse_error *error);
int		ft_parse_ambient(char **tokens, t_scene *scene,
			t_parse_error *error);
int		ft_parse_camera(char **tokens, t_scene *scene,
			t_parse_error *error);
int		ft_parse_light(char **tokens, t_scene *scene,
			t_parse_error *error);
int		ft_parse_obj(char **tokens, t_scene *scene, t_type type,
			t_parse_error *error);
int		ft_parse_direction(char *str, t_vec3 *dir, t_parse_error *error,
			const char *name);
int		ft_parse_fail(t_parse_error *error, const char *message);
void	ft_print_parse_error(const t_parse_error *error);

/* --- PARSING CONVERSIONS --- */
int		ft_str_to_float(char *str, double *out);
int		ft_str_to_vec3(char *str, t_vec3 *vec, int is_dir);
int		ft_str_to_color(char *str, t_vec3 *color);

/* mlx / render utils */
int		ft_put_img_to_window(t_scene *scene);
void	ft_mlx_pixel_put(t_scene *scene, int x, int y, int color);
void	ft_run_time(t_scene *scene);
int		ft_load_scene(char *path, t_scene **scene);
void	ft_render_scene(t_scene *scene);

/* --- EVENTS & HOOKS --- */
int		key_handler(int key, void *param);
int		ft_expose_handler(void *param);

/* --- RAYTRACING & RENDERING --- */

t_ray	ft_generate_ray(t_camera *cam, double u, double v, t_scene *scene);
t_hit	ft_intersect_scene(t_scene *scene, t_ray ray);
t_vec3	ft_get_normal(t_hit hit);
int		ft_is_shadowed(t_scene *scene, t_vec3 point);
int		ft_compute_light(t_scene *scene, t_hit hit);

double	ft_hit_sphere(t_obj *sp, t_ray ray);
double	ft_hit_plane(t_obj *pl, t_ray ray);
double	ft_hit_cylinder(t_obj *cy, t_ray ray);
double	ft_hit_cylinder_caps(t_obj *obj, t_ray ray, t_vec3 *out_norm);
double	ft_hit_cylinder_side(t_obj *obj, t_ray ray);

t_vec3	ft_color_add(t_vec3 a, t_vec3 b);
t_vec3	ft_color_mul(t_vec3 a, t_vec3 b);
t_vec3	ft_color_scale(t_vec3 color, double ratio);
double	ft_color_clamp(double value, double min, double max);

/* --- CLEAN & MEMORY UTILS --- */

void	ft_free_tab(char **tab);
void	ft_free_objects(t_obj **lst);
void	ft_free_null(void **p);

int		ft_clean_exit(void *param);
void	ft_destroy_scene(t_scene *scene);
void	ft_runtime_error(t_scene *scene, const char *message);

void	ft_print_scene_info(t_scene *scene);

#endif
