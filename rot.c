/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:48:55 by archid-           #+#    #+#             */
/*   Updated: 2019/11/24 18:27:04 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* gcc -g rot.c -o rot -Llibft -Ilibft -lft */
/* ./rot 68 13 51 1 */
/* expected -1 */
/* it might be that the number of elements is odd or even!! */

int main(int argc, char *argv[])
{
    int *arr;
	int i;

	if (argc < 3)
		return -1;

	i = 0;
	arr = ALLOC(int *, argc - 2, sizeof(int));
	while (i < argc - 2)
	{
		arr[i] = ft_atoi(argv[i + 2]);
		ft_printf("[%d] -> %d\n", i, arr[i]);
		i++;
	}

	int n_rots = binary_search_range(ft_atoi(argv[1]), arr,
									 0, i - 1, ascending_order);
	int min_index = binary_search_find_min(arr, 0, i - 1, ascending_order);

	ft_printf(" >> %d %d\n", min_index,  n_rots);

    return 0;
}
