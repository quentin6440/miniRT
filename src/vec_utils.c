/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 13:35:25 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/09/28 18:16:23 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vector.h"
#include <math.h>

/* Norme au carre (evite sqrt) */
double	vec_length_sq(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

/* Norme / Longueur du vecteur */
double	vec_length(t_vec3 v)
{
	return (sqrt(vec_length_sq(v)));
}

/* Normalisation : rend le vecteur unitaire (longueur == 1) */
t_vec3	vec_normalize(t_vec3 v)
{
	double	len;

	len = vec_length(v);
	if (len == 0.0)
		return (vec_new(0, 0, 0));
	return (vec_scale(v, 1.0 / len));
}
