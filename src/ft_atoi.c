/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:43:59 by ansimonn          #+#    #+#             */
/*   Updated: 2026/03/30 16:16:19 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	add_digits(const char *digits, int *res)
{
	int		i;

	i = 0;
	while (digits[i] >= '0' && digits[i] <= '9')
	{
		if (*res > 214748364 || (*res == 214748364 && digits[i] > '7'))
		{
			*res = -2;
			return ;
		}
		*res = *res * 10 + digits[i] - '0';
		i++;
	}
	if (digits[i])
		*res = -2;
}

int	ft_atoi(const char *nptr)
{
	int		res;

	res = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '+')
		nptr++;
	while (*nptr == '0')
		nptr++;
	if (*nptr >= '0' && *nptr <= '9')
	{
		add_digits(nptr, &res);
		return (res);
	}
	if (*nptr)
		return (-2);
	return (0);
}
