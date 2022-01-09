#include "libft.h"

void	*ft_memset (void *src, int c, size_t len)
{
	unsigned char	*s2;

	s2 = (unsigned char *)src;
	while (len)
	{
		*s2++ = (unsigned char) c;
		len--;
	}
	return (src);
}
