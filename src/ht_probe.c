#include "ht.h"

size_t	ht_probe(t_ht *table, void *key, int find_deleted)
{
	size_t	hash;
	size_t	index;
	size_t	i;

	if (!table || !key)
		return (0);
	hash = table->hash_fn(key) % table->capacity;
	index = hash;
	i = 0;
	while (i < table->capacity)
	{
		if (table->entries[index].state == EMPTY)
			return (index);
		if (table->entries[index].state == DELETED && find_deleted)
			return (index);
		if (table->entries[index].state == OCCUPIED)
		{
			if (table->cmp_fn(table->entries[index].key, key) == 0)
				return (index);
		}
		i++;
		index = (hash + (i * (i + 1) / 2)) % table->capacity;
	}
	return (hash);
}
