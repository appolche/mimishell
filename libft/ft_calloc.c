#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*mass;

	mass = malloc(count * size);
	if (NULL == mass)
		return (NULL);
	ft_bzero (mass, count * size);
	return ((void *)mass);
}
