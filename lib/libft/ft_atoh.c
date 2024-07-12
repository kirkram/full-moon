/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:55:14 by mburakow          #+#    #+#             */
/*   Updated: 2024/07/12 15:14:50 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_atoh(const char *hex_str)
{
	unsigned int	value;
	char			digit;

	if (hex_str[0] == '0' && (hex_str[1] == 'x' || hex_str[1] == 'X'))
	{
		hex_str += 2;
	}
	value = 0;
	while (*hex_str)
	{
		digit = *hex_str;
		if (ft_isdigit(digit))
			value = (value << 4) | (digit - '0');
		else if (digit >= 'a' && digit <= 'f')
			value = (value << 4) | (digit - 'a' + 10);
		else if (digit >= 'A' && digit <= 'F')
			value = (value << 4) | (digit - 'A' + 10);
		else
			break ;
		hex_str++;
	}
	return (value);
}
