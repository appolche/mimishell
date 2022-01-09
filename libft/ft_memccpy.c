#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	unsigned char	b;
	size_t			i;

	if (!dst && !src)
		return (0);
	i = 0;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	b = (unsigned char) c;
	while (n > i)
	{
		d[i] = s[i];
		if (s[i] == b)
			return (&(d[i + 1]));
		i++;
	}
	return (0);
}
