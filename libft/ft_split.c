/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:23:01 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/22 01:56:58 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_free(char **arr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (0);
}

static size_t	ft_count_words(const char *s, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static size_t	ft_count_till_c(const char *s, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (s[i] && s[i] != c)
	{
		count++;
		i++;
	}
	return (count);
}

static int	ft_write_words(const char *s, char c, char **arr)
{
	size_t	i;
	size_t	j;
	size_t	word_len;

	i = 0;
	j = 0;
	word_len = 0;
	while (*s)
	{
		if (*s != c)
		{
			word_len = ft_count_till_c(s, c);
			arr[j] = malloc ((word_len + 1) * sizeof (char));
			if (!arr[j])
				return (ft_free(arr, j));
			i = 0;
			while (i < word_len)
				arr[j][i++] = *(s++);
			arr[j++][i] = '\0';
		}
		else
			s++;
	}
	arr[j] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**res_arr;
	size_t	count;

	if (!s)
		return (NULL);
	count = ft_count_words(s, c);
	if (count == 0)
		return (NULL);
	res_arr = malloc ((ft_count_words(s, c) + 1) * sizeof (char *));
	if (!res_arr || !ft_write_words(s, c, res_arr))
		return (NULL);
	return (res_arr);
}
