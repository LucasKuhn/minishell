#include "minishell.h"

int str_equal(const char* str1, const char* str2)
{
	int size;
	size = ft_strlen(str1);
	if (size != ft_strlen(str2))
		return 0;
	return (ft_strncmp(str1, str2, size) == 0);
}

char	*name_only(char *key_pair)
{
	int i;

	i = 0;
	while (key_pair[i] != '=' && key_pair[i])
		i++;
	if (!key_pair[i])
		return (NULL);
	return (ft_substr(key_pair, 0, i));
}

char	*value_only(char *key_pair)
{
	int i;

	i = 0;
	while (key_pair[i] != '=' && key_pair[i])
		i++;
	if (!key_pair[i])
		return (NULL);
	return (&key_pair[i+1]);
}