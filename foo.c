/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 20:12:00 by archid-           #+#    #+#             */
/*   Updated: 2019/11/16 00:54:53 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ABOUT: implementation of binary search, O(nlogn) complexity
 *
 * given array of N elements, a pair<low, high> representing
 * the boudry-indecies of the array. the idea is to:
 *
 *   1. find the array[mid] index, where mid is (low + high) / 2
 *   2. if array[mid] is what we're looking for, set found as true
 *   3. if array[mid]
 *
 * NOTE: clean code is better.
 * NOTE: array should be sorted
 */

#include "ft_printf.h"

#define SIZE							(10)
#define TARGET							(1 << SIZE)
#define MID(u, v)						(((u) + (v)) / 2)

size_t	binary_search_rot(int value, int *array, size_t size)
{
	size_t i = 0, low = 0, high = size - 1;
	size_t mid;
	bool found = false;

	while (!found && low <= high)
	{
		if (array[mid = MID(low, high)] == value)
			found = true;
		else if (array[low] <= array[mid])
		{
			if (array[low] <= value &&  array[mid] > value)
				high = mid - 1;
			else
				low = mid + 1;
		}
		else {
			if (array[mid + 1] <= value && array[high] > value)
				low = mid + 1;
			else
				high = mid - 1;
		}
		i++;
	}
	return (!found ? (size_t)-1 : mid);
}

size_t	binary_search(int value, int *array, size_t size)
{
	size_t low = 0, high = size - 1,
		mid = MID(low, high);
	bool found = false;

	/* NOTE: keep going until low and high meet or we found it */
	while (!found && low < high)
	{
		if (array[mid] == value)
			found = true;
		else if (array[mid] < value)
			low = mid;
		else
			high = mid;
	}
	return (!found ? (size_t)-1 : mid);
}

void test_binary_search(int value, int *array, size_t size)
{
	size_t i;
	size_t index;

	i = 0;
	while (i < size)
	{
		ft_printf("[%d] -> %d\n", array[i] = (1 << i));
		i++;
	}
	index = binary_search(value, array, size);
	ft_printf("\n[%d] -> %d\n", index, array[index]);
}

void test_binary_search_rot(int value, int *array, size_t size)
{
	size_t index;

	index = binary_search_rot(value, array, size);
	ft_printf("\n[%d] -> %d\n", index, array[index]);
}

int		*shifted_mid(int shift, size_t)
{
	return
}

int		main(void)
{
	int array[SIZE], array2[SIZE];

	int mid = MID(0, SIZE - 1) + 2;
	size_t i = 0;


	test_binary_search(TARGET, shifted_mid(0, SIZE), SIZE);
	test_binary_search_rot(TARGET, shifted_mid(3, SIZE), SIZE);
	return (0);
}
