#include "ht.h"

size_t		ht_probe(t_ht *table, void *key, int find_deleted);
t_ht_status	ht_resize(t_ht *table, size_t new_capacity);

static int	ht_check_load_factor(t_ht *table)
{
	return ((table->count * 4) > (table->capacity * 3));
}

t_ht_status	ht_add(t_ht *table, void *key, void *value)
{
	size_t		index;
	t_ht_status	status;

	if (!table || !key || !value)
		return (HT_INVALID_INPUT);
	if (ht_check_load_factor(table))
	{
		status = ht_resize(table, table->capacity * 2);
		if (status != HT_SUCCESS)
			return (status);
	}
	index = ht_probe(table, key, 1);
	if (table->entries[index].state == OCCUPIED)
	{
		table->entries[index].value = value;
		return (HT_SUCCESS);
	}
	table->entries[index].key = key;
	table->entries[index].value = value;
	table->entries[index].state = OCCUPIED;
	table->count++;
	return (HT_SUCCESS);
}
