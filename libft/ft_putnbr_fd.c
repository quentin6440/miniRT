/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 18:27:39 by qcyril-a          #+#    #+#             */
/*   Updated: 2025/10/11 18:41:12 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	i;
	int	buf[11];

	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
	}
	i = 0;
	while (n > 0 || i == 0)
	{
		buf[i++] = n % 10 + 48;
		n /= 10;
	}
	while (--i >= 0)
		ft_putchar_fd(buf[i], fd);
}
