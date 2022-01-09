#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c <= 90 && c >= 65) || (c <= 122 && c >= 97) || (c >= 48 && c <= 57))
		return (1);
	else
		return (0);
}
