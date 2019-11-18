/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 20:12:00 by archid-           #+#    #+#             */
/*   Updated: 2019/11/18 05:43:26 by archid-          ###   ########.fr       */
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

#include "libft.h"

#define SIZE							(10)
#define TARGET							(1 << SIZE)
#define MID(u, v)						(((u) + (v)) / 2)

void print_array(int *array, size_t size)
{
	size_t i = 0;

	ft_printf("\n");
	while (i < size)
	{
		ft_printf("[%d] = %d ", i, array[i]);
		i++;
	}
}

/* on ascending order first, the descending order */
size_t	binar_search_rot_recu(int value, int *array, size_t low, size_t high)
{
	size_t mid;

	/*
	 * we have a normal array: 0 1 [2] 3 4 5
	 * and its rotation(ra+1): 1 2 [3] 4 5 0
	 *
	 * -> small to back, and since we're in ascending order, means that
	 * while [low] > [high]. left is sorted due to insertion sort, and holds
	 * true because the split is in the right also because [mid] >
	 *
	 * rotated(rra+1): 5 0 [1] 2 3 4
	 *
	 * now the split is on the left. we have [low] > [high]. but this time,
	 * so we are looking for [low] < [mid] and [mid] < [high] to check order.
	 * also, we need to compare the order of [mid] and value, since we need
	 * to have the following property
	 *
	 *		[low] < value < [mid]	or	 [high] > value > [mid]
	 *			=> just as ascending order
	 *
	 * so while this is not true, we shall keep looking. but how to find
	 * where to go. this is done [low]
	 *
	 */

	mid = (high + low) / 2;
	if (array[mid] == value)
		return (mid);
	else if (array[low] > array[high]) /* left is sorted */
	{
		if (array[mid] < array[high] && array[mid] > value)
		{
			/*  */
		}
	}
	else
	{

	}
	return (0);
}

/* iterative approach is not good, recursive one will work */
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

void	test_binary_search(int value, int *array, size_t size)
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

/*
  NOTE: this gives ascending order
  FIXME: working on shift less than ((size - 1) / 2)

  ABS(shift) <= ((size - 1) / 2)
*/

int		*shifted_mid(int shift, size_t size)
{
	int		*arr;				/* from 1 to size */
	size_t	index;
	size_t	mid;

	if (!size)
		return (NULL);
	if (shift < 0 && ((int)size / 2) - shift < 0)
		return (NULL);
	else if (shift > 0 && ((int)size / 2) + shift >= (int)size)
		return (NULL);

	mid = ((size - 1) / 2);
	arr = ALLOC(int *, size, sizeof(int));

	/* start by placing the mid at it's place, go from there
	 * to the end, then continue  */
	index = 0;
	/* A: |1|2|3|4|5|6|7|8| mid not shifted */
	if (shift == 0)
		while (index++ < size)
			arr[index - 1] = index;
	else
	{
		ft_printf("\nindex is %{yellow_fg}[%d] = %d%{reset}\n",
				  mid, mid + shift);
		/* A: |7|8|1|2|3|4|5|6|  mid shifted to the right (rra) */
		if (shift > 0)
		{
			/* place things after the mid in array */
			/* index should be starting at mid shifted n times */
			index = mid + shift;
			while (index < size)
			{
				arr[index] = index;
				ft_printf("%{green_fg}[%d] = %d %{reset} ",
							index, arr[index]);
				index++;
			}
			ft_printf("\n");

			/* print_array(arr, size); */
			/* place things still above mid */
			index = 0;
			while (index + mid < size)
			{
				arr[index] = index + 1;
				ft_printf("%{blue_fg}[%d] = %d %{reset} ",
							index, arr[index]);
				index++;
			}
			ft_printf("\n");

			/* print_array(arr, size); */
			/* int last = index; */
			/* while (index <= mid) */
			/* { */
			/* 	arr[index] = index - last + 1; */
			/* 	ft_printf("%{red_fg}[%d] = %d %{reset} ", */
			/* 			  index, arr[index]); */
			/* 	index++; */
			/* } */
			/* print_array(arr, size); */
		}
		/* A: |3|4|5|6|7|8|1|2| this is to the left (ra) */
		else
		{
			while (index < size)
			{
				arr[index] = index + 1;
				index++;
			}
		}
	}
	return (arr);
}

void	find_split(int *arr, size_t size, size_t *alow, size_t *ahigh)
{
	size_t	i = 1;
	int		low = 0;
	int		high = size - 1;

	while (i < size - 1)
	{
		ft_printf("[%d] = %d ", i, arr[i]);

		/* track boundries of the normal array */
		if (arr[i] > arr[high])
			high = i;
		if (arr[i] < arr[low])
			low = i;
		i++;
	}
	ft_printf("\nA[low: %d] = %d    A[high: %d] = %d\n\n",
				low, arr[low], high, arr[high]);
	if (alow && ahigh)
	{
		*alow = low;
		*ahigh = high;
	}
	/* if (arr[low] < arr[high] && low > high) */
	/* 	reversed_order(); */
}

void	check_sort_order(int *arr, size_t size)
{

}

int		main(void)
{
	/* test_binary_search(TARGET, shifted_mid(0, SIZE), SIZE); */
	/* int *foobar[] = { */
	/* 	shifted_mid(2, SIZE),	/\* this is weird *\/ */
	/* 	shifted_mid(3, SIZE),	/\* this is working *\/ */
	/* 	shifted_mid(4, SIZE)	/\* this is weird *\/ */
	/* }; */
	/* int *arr = shifted_mid(0, SIZE); */

	/* /\* ft_printf("\n------- normal -------\n"); *\/ */
	/* print_array(arr, SIZE); */
	/* /\* ft_printf("\n------- shifted -------\n"); *\/ */
	/* print_array(foobar[0], SIZE); */
	/* print_array(foobar[1], SIZE); */
	/* print_array(foobar[2], SIZE); */

	/* ft_putendl("\n"); */

	int arr_ascending_left_to_right[SIZE] = {4,5,6,7,8,9,1,2,3};
	int arr_disending_right_to_left[SIZE] = {5,4,3,2,1,9,8,7,6};
	size_t low, high;

	find_split(arr_ascending_left_to_right, SIZE, &low, &high);
	find_split(arr_disending_right_to_left, SIZE, &low, &high);

	/* test(foobar[0], SIZE); */
	/* test(foobar[1], SIZE); */
	/* test(foobar[2], SIZE); */

	/* test_binary_search_rot(TARGET, shifted_mid(3, SIZE), SIZE); */
	return (0);
}
