/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 01:17:53 by sabra             #+#    #+#             */
/*   Updated: 2021/03/21 21:51:20 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	ft_env(char **ev)
{
	size_t i;
	
	i = 0;
	if (!ev)
		return (0);
	while(ev[i])
	{
		if (ft_strchr(ev[i], '='))
			ft_printf("%s\n", ev[i]);
		i++;
	}
	return (1);
}
