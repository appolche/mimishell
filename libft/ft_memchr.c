#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*src;
	unsigned char	b;
	size_t			i;

	i = 0;
	src = (unsigned char *)s;
	b = (unsigned char) c;
	while (n > i)
	{
		if (src[i] == b)
			return (&src[i]);
		i++;
	}
	return (NULL);
}
