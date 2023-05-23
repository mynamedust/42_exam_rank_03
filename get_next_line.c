# include<stdlib.h>
# include<unistd.h>
# include<stddef.h>
# include<fcntl.h>
# include<limits.h>

int	ft_strlen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *str, int c)
{
	char	i;

	if (!str)
		return (NULL);
	i = (char)c;
	while (*str)
	{
		if (*str == i)
			return ((char *)str);
		str++;
	}
	if (*str == i)
		return ((char *)str);
	return (0);
}

char	*ft_strdup(char *str)
{
	char	*arr;
	int		j;
	int		i;

	j = ft_strlen(str);
	arr = malloc(j + 1);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < j)
	{
		arr[i] = str[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*str;
	int		c;

	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	c = len;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	while (*s && start > 0)
	{
		s++;
		start--;
	}
	while (*s && len > 0)
	{
		*str++ = *s++;
		len--;
	}
	*str = '\0';
	str -= c;
	return (str);
}

char	*ft_join(char *s1, char *s2)
{
	char	*newstr;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	newstr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!newstr)
		return (newstr);
	while (*s1)
		newstr[i++] = *s1++;
	while (*s2)
		newstr[i++] = *s2++;
	newstr[i] = '\0';
	return (newstr);
}

char	*ft_stcjoin(char *stc, char *buff)
{
	char	*str;

	if (!stc)
	{
		stc = malloc(1);
		stc[0] = '\0';
	}
	str = stc;
	stc = ft_join(stc, buff);
	free(str);
	return (stc);
}

char	*ft_read(int fd, char *stc)
{
	char	*buff;
	int		n;

	n = 1;
	buff = malloc(BUFFER_SIZE + 1);
	while (!ft_strchr(stc, '\n') && n != 0)
	{
		n = read(fd, buff, BUFFER_SIZE);
		if ((ft_strlen(stc) == 0 && n == 0) || n < 0)
		{
			free(buff);
			free(stc);
			return (NULL);
		}
		buff[n] = '\0';
		stc = ft_stcjoin(stc, buff);
	}
	free(buff);
	return (stc);
}

char	*ft_newline(char *stc)
{
	char	*newline;
	int		i;

	i = 0;
	while (stc[i] && stc[i] != '\n')
		i++;
	if (stc[i] == '\n')
		i++;
	newline = malloc(i + 1);
	if (!newline)
		return (NULL);
	newline[i] = '\0';
	i--;
	while (i >= 0)
	{
		newline[i] = stc[i];
		i--;
	}
	return (newline);
}

char	*ft_ncut(char *stc)
{
	char	*temp;
	int		len;

	if (ft_strchr(stc, '\n'))
	{
		temp = stc;
		len = ft_strlen(ft_strchr(stc, '\n') + 1);
		stc = ft_substr(stc, ft_strlen(stc) - len, len);
		free (temp);
	}
	else
	{
		free(stc);
		return (NULL);
	}
	return (stc);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stc;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0))
		return (NULL);
	stc = ft_read(fd, stc);
	if (!stc)
		return (NULL);
	line = ft_newline(stc);
	stc = ft_ncut(stc);
	return (line);
}