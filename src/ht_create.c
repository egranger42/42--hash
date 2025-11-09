#include "ht.h"

static t_ht	*ht_create_init(size_t capacity)
{
	t_ht	*table;

	table = malloc(sizeof(t_ht));
	if (!table)
		return (NULL);
	table->entries = malloc(sizeof(t_ht_entry) * capacity);
	if (!table->entries)
	{
		free(table);
		return (NULL);
	}
	return (table);
}

t_ht	*ht_create(size_t capacity, t_ht_hash_fn hash_fn, t_ht_cmp_fn cmp_fn)
{
	t_ht		*table;
	size_t		i;

	if (capacity == 0 || !hash_fn || !cmp_fn)
		return (NULL);
	table = ht_create_init(capacity);
	if (!table)
		return (NULL);
	i = 0;
	while (i < capacity)
	{
		table->entries[i].key = NULL;
		table->entries[i].value = NULL;
		table->entries[i].state = EMPTY;
		i++;
	}
	table->capacity = capacity;
	table->count = 0;
	table->hash_fn = hash_fn;
	table->cmp_fn = cmp_fn;
	return (table);
}
