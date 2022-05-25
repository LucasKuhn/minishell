/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:28:39 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/05/25 13:28:40 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	str_equal(const char *str1, const char *str2)
{
	size_t	size;

	if (!str1 || !str2)
		return (0);
	size = ft_strlen(str1);
	if (size != ft_strlen(str2))
		return (0);
	return (ft_strncmp(str1, str2, size) == 0);
}

char	*name_only(char *key_pair)
{
	int	i;

	i = 0;
	while (key_pair[i] != '=' && key_pair[i])
		i++;
	if (!key_pair[i])
		return (NULL);
	return (ft_substr(key_pair, 0, i));
}

char	*value_only(char *key_pair)
{
	int	i;

	i = 0;
	while (key_pair[i] != '=' && key_pair[i])
		i++;
	if (!key_pair[i])
		return (NULL);
	return (&key_pair[i + 1]);
}

// Adds 3 strings to a base string that was previously allocated
void	strs_cat(char base[], char *str1, char *str2, char *str3)
{
	ft_strlcat(base, str1, PATH_MAX);
	ft_strlcat(base, str2, PATH_MAX);
	ft_strlcat(base, str3, PATH_MAX);
}

// void	ft_strjoin_free(char **str1, char *str2)
// {
// 	char    *aux;

// 	aux = ft_strjoin(*str1, str2);
// 	if (*str1 != NULL)
// 		free(*str1);
// 	*str1 = aux;
// }

// char	*ft_strsjoin(int n, char *str1, ...)
// {
// 	va_list	strs;
// 	int		i;
// 	char	*s;
// 	char	*aux;

// 	aux = ft_strdup(str1);
// 	if (!aux)
// 		return (NULL);
// 	va_start(strs, str1);
// 	i = 1;
// 	while (i < n)
// 	{
// 		s = va_arg(strs, char *);
// 		ft_strjoin_free(&aux, s);
// 		i++;
// 		if (!aux)
// 			i = n;
// 	}
// 	va_end(strs);
// 	return (aux);
// }
