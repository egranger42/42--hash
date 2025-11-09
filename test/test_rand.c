#include "test_rand.h"
#include <stdio.h>
#include <string.h>

static uint64_t	g_seed = 12345;

void	seed_random(unsigned int seed)
{
	g_seed = seed;
}

uint32_t	rand_uint32(void)
{
	g_seed = (g_seed * 1103515245 + 12345) & 0x7fffffff;
	return ((uint32_t)(g_seed >> 16));
}

uint64_t	rand_uint64(void)
{
	return (((uint64_t)rand_uint32() << 32) | rand_uint32());
}
