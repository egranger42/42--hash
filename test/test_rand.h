#ifndef TEST_RAND_H
#define TEST_RAND_H

#include <stdlib.h>
#include <stdint.h>

typedef struct s_rand_data
{
	char	*key;
	int		*value;
}	t_rand_data;

void			seed_random(unsigned int seed);
uint32_t		rand_uint32(void);
uint64_t		rand_uint64(void);
char			*rand_string(size_t len);
int				*rand_int(void);
t_rand_data		*rand_data(size_t count);
void			free_rand_data(t_rand_data *data, size_t count);
char			*rand_key(size_t id);

#endif
