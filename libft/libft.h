#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

int		ft_isalnum(int c);
int     ft_isdigit(int c);
int     ft_atoi(const char *str);
char	**ft_split(char const *s, char c);
int 	ft_strchr(char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
