#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*s2;
	unsigned int	i;
	size_t			l;

	if (!s)
		return (0);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	i = 0;
	l = ft_strlen(s) - start;
	if (l < len)
		len = l;
	s2 = malloc((len + 1) * sizeof(char));
	if (NULL == s2)
		return (NULL);
	while (i < len && s[i])
	{
		s2[i] = s[start + i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
