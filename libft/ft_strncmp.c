#include "libft.h"

int	ft_strncmp(const char *dst, const char *src, size_t n)
{	
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)dst;
	s2 = (unsigned char *)src;
	while (n > 0 && *s1 == *s2 && *s1 && *s2)
	{
		s1++;
		s2++;
		n--;
	}
	if (n <= 0)
		return (0);
	else
		return (*s1 - *s2);
}
