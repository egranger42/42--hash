#include "ht.h"

size_t		ht_probe(t_ht *table, void *key, int find_deleted);

static t_ht_status	ht_rehash_entries(t_ht *old_table, t_ht *new_table)
{
	size_t	i;
	size_t	index;

	i = 0;
	while (i < old_table->capacity)
	{
		if (old_table->entries[i].state == OCCUPIED)
		{
			index = ht_probe(new_table, old_table->entries[i].key, 0);
			new_table->entries[index].key = old_table->entries[i].key;
			new_table->entries[index].value = old_table->entries[i].value;
			new_table->entries[index].state = OCCUPIED;
			new_table->count++;
		}
		i++;
	}
	return (HT_SUCCESS);
}

t_ht_status	ht_resize(t_ht *table, size_t new_capacity)
{
	t_ht	new_table_data;
	t_ht	*new_table;

	if (!table || new_capacity <= table->capacity)
		return (HT_INVALID_INPUT);
	new_table = &new_table_data;
	new_table->entries = malloc(sizeof(t_ht_entry) * new_capacity);
	if (!new_table->entries)
		return (HT_ALLOC_FAILED);
	new_table->capacity = new_capacity;
	new_table->count = 0;
	new_table->hash_fn = table->hash_fn;
	new_table->cmp_fn = table->cmp_fn;
	{
		size_t j;
		j = 0;
		while (j < new_capacity)
		{
			new_table->entries[j].key = NULL;
			new_table->entries[j].value = NULL;
			new_table->entries[j].state = EMPTY;
			j++;
		}
	}
	ht_rehash_entries(table, new_table);
	free(table->entries);
	table->entries = new_table->entries;
	table->capacity = new_table->capacity;
	table->count = new_table->count;
	return (HT_SUCCESS);
}
