/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_edf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykaf <ykaf@student.1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 10:41:08 by ykaf              #+#    #+#             */
/*   Updated: 2026/09/21 07:01:22 by ykaf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/codexion.h"

t_coder	*get_other_coder(t_coder *coder, t_dongle *dongle)
{
	int	n;

	n = coder->data->number_of_coders;
	if (dongle == coder->left_dongle)
		return (&coder->simu->coder[coder->id % n]);
	return (&coder->simu->coder[(coder->id - 2 + n) % n]);
}
