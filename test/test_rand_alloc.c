#include "test_rand.h"
#include <string.h>

uint32_t	rand_uint32(void);
char		*rand_key(size_t id);

int	*rand_int(void)
{
	int	*val;

	val = malloc(sizeof(int));
	if (!val)
		return (NULL);
	*val = (int)rand_uint32();
	return (val);
}

t_rand_data	*rand_data(size_t count)
{
	t_rand_data	*data;
	size_t		i;

	data = malloc(sizeof(t_rand_data) * count);
	if (!data)
		return (NULL);
	i = 0;
	while (i < count)
	{
		data[i].key = rand_key(i);
		data[i].value = rand_int();
		if (!data[i].key || !data[i].value)
			return (NULL);
		i++;
	}
	return (data);
}

void	free_rand_data(t_rand_data *data, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(data[i].key);
		free(data[i].value);
		i++;
	}
	free(data);
}
