/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_sp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 18:12:44 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/09/28 18:13:04 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static t_quadratic	ft_sphere_equation(t_obj *sp, t_ray ray)
{
	t_quadratic	equation;
	t_vec3		oc;
	double		radius;

	radius = sp->diameter / 2.0;
	oc = vec_sub(ray.origin, sp->pos);
	equation.a = vec_dot(ray.dir, ray.dir);
	equation.b = 2.0 * vec_dot(oc, ray.dir);
	equation.c = vec_dot(oc, oc) - radius * radius;
	return (equation);
}

static double	ft_sphere_discriminant(t_quadratic equation)
{
	return (equation.b * equation.b
		- 4.0 * equation.a * equation.c);
}

static double	ft_nearest_sphere_t(t_quadratic equation,
		double discriminant)
{
	double	t1;
	double	t2;

	t1 = (-equation.b - sqrt(discriminant))
		/ (2.0 * equation.a);
	t2 = (-equation.b + sqrt(discriminant))
		/ (2.0 * equation.a);
	if (t1 > EPSILON)
		return (t1);
	if (t2 > EPSILON)
		return (t2);
	return (-1.0);
}

double	ft_hit_sphere(t_obj *sp, t_ray ray)
{
	t_quadratic	equation;
	double		discriminant;

	equation = ft_sphere_equation(sp, ray);
	discriminant = ft_sphere_discriminant(equation);
	if (discriminant < 0.0 || fabs(equation.a) < EPSILON)
		return (-1.0);
	return (ft_nearest_sphere_t(equation, discriminant));
}
