#include "test_rand.h"
#include <stdio.h>
#include <string.h>

uint32_t	rand_uint32(void);

char	*rand_string(size_t len)
{
	char	*str;
	size_t	i;

	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = 33 + (rand_uint32() % 94);
		i++;
	}
	str[len] = '\0';
	return (str);
}

char	*rand_key(size_t id)
{
	char	buffer[32];

	snprintf(buffer, sizeof(buffer), "key_%zu_%u", id, rand_uint32());
	return (strdup(buffer));
}
