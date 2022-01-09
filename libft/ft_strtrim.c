#include "libft.h"

static int	ft_cmp(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (0);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_cmp(s1[start], set))
		start++;
	while (end > start && ft_cmp(s1[end - 1], set))
		end--;
	str = malloc ((end - start + 1) * sizeof(*s1));
	if (NULL == str)
		return (NULL);
	i = 0;
	while (start != end)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}
