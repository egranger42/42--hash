#include "ht.h"
#include <string.h>
#include <stdio.h>

uint64_t	ht_hash_default(const void *key)
{
	const unsigned char	*str;
	uint64_t			hash;

	str = (const unsigned char *)key;
	hash = 5381;
	while (*str)
		hash = ((hash << 5) + hash) + *str++;
	return (hash);
}

int	ht_cmp_default(const void *key1, const void *key2)
{
	return (strcmp((const char *)key1, (const char *)key2));
}

const char	*ht_status_msg(t_ht_status status)
{
	if (status == HT_SUCCESS)
		return ("Success");
	if (status == HT_ALLOC_FAILED)
		return ("Memory allocation failed");
	if (status == HT_KEY_NOT_FOUND)
		return ("Key not found");
	if (status == HT_KEY_EXISTS)
		return ("Key already exists");
	if (status == HT_INVALID_INPUT)
		return ("Invalid input");
	return ("Unknown error");
}
