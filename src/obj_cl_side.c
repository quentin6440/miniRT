/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cl_side.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 18:13:51 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/09/28 18:13:52 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static int	ft_check_height(t_obj *obj, t_ray ray, double t)
{
	t_vec3	point;
	t_vec3	relative;
	double	projection;
	double	half_height;

	if (t <= EPSILON)
		return (0);
	point = vec_add(ray.origin, vec_scale(ray.dir, t));
	relative = vec_sub(point, obj->pos);
	projection = vec_dot(relative, obj->dir);
	half_height = obj->height / 2.0;
	if (projection < -half_height || projection > half_height)
		return (0);
	return (1);
}

static t_quadratic	ft_cylinder_equation(t_obj *obj, t_ray ray)
{
	t_quadratic	equation;
	t_vec3		relative;
	double		axis_ray;
	double		axis_origin;
	double		radius;

	relative = vec_sub(ray.origin, obj->pos);
	axis_ray = vec_dot(ray.dir, obj->dir);
	axis_origin = vec_dot(relative, obj->dir);
	radius = obj->diameter / 2.0;
	equation.a = vec_dot(ray.dir, ray.dir)
		- axis_ray * axis_ray;
	equation.b = 2.0 * (vec_dot(ray.dir, relative)
			- axis_ray * axis_origin);
	equation.c = vec_dot(relative, relative)
		- axis_origin * axis_origin
		- radius * radius;
	return (equation);
}

static double	ft_nearest_valid_t(t_obj *obj, t_ray ray,
		double t1, double t2)
{
	if (ft_check_height(obj, ray, t1)
		&& ft_check_height(obj, ray, t2))
	{
		if (t1 < t2)
			return (t1);
		return (t2);
	}
	if (ft_check_height(obj, ray, t1))
		return (t1);
	if (ft_check_height(obj, ray, t2))
		return (t2);
	return (-1.0);
}

double	ft_hit_cylinder_side(t_obj *obj, t_ray ray)
{
	t_quadratic	equation;
	double		discriminant;
	double		t1;
	double		t2;

	equation = ft_cylinder_equation(obj, ray);
	if (fabs(equation.a) < EPSILON)
		return (-1.0);
	discriminant = equation.b * equation.b
		- 4.0 * equation.a * equation.c;
	if (discriminant < 0.0)
		return (-1.0);
	t1 = (-equation.b - sqrt(discriminant))
		/ (2.0 * equation.a);
	t2 = (-equation.b + sqrt(discriminant))
		/ (2.0 * equation.a);
	return (ft_nearest_valid_t(obj, ray, t1, t2));
}
