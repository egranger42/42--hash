#include "ht.h"

size_t		ht_probe(t_ht *table, void *key, int find_deleted);

t_ht_status	ht_get(t_ht *table, void *key, void **value)
{
	size_t	index;

	if (!table || !key || !value)
		return (HT_INVALID_INPUT);
	index = ht_probe(table, key, 0);
	if (table->entries[index].state != OCCUPIED)
		return (HT_KEY_NOT_FOUND);
	*value = table->entries[index].value;
	return (HT_SUCCESS);
}
