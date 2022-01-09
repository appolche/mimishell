#include "libft.h"

static char	**malloc_free(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}

static unsigned int	str_count(char const *s, char c)
{
	unsigned int	i;
	unsigned int	nb_strs;

	if (!s[0])
		return (0);
	i = 0;
	nb_strs = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			nb_strs++;
			while (s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		nb_strs++;
	return (nb_strs);
}

static unsigned int	each_str_len(char **n_str, unsigned int *n_str_len, char c)
{
	unsigned int	i;

	*n_str += *n_str_len;
	*n_str_len = 0;
	i = 0;
	while (**n_str && (**n_str == c))
		(*n_str)++;
	while ((*n_str)[i] && (*n_str)[i] != c)
	{
		(*n_str_len)++;
		i++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char			**tab;
	char			*next_str;
	unsigned int	next_str_len;
	unsigned int	i;

	tab = malloc(sizeof(char *) * (str_count(s, c) + 1));
	if (NULL == tab || !s)
		return (NULL);
	i = 0;
	next_str = (char *)s;
	next_str_len = 0;
	while (i < str_count(s, c))
	{
		each_str_len(&next_str, &next_str_len, c);
		tab[i] = malloc(sizeof(char) * (next_str_len + 1));
		if (NULL == tab[i])
			return (malloc_free(tab));
		ft_strlcpy(tab[i], next_str, next_str_len + 1);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
