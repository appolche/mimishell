#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*s1;

	s1 = (char *)s + (ft_strlen(s));
	while (s1 >= s)
	{
		if (*s1 == (char)c)
			return (s1);
		s1--;
	}
	return (NULL);
}
