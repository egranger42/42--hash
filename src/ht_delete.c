#include "ht.h"

size_t		ht_probe(t_ht *table, void *key, int find_deleted);

t_ht_status	ht_delete(t_ht *table, void *key)
{
	size_t	index;

	if (!table || !key)
		return (HT_INVALID_INPUT);
	index = ht_probe(table, key, 0);
	if (table->entries[index].state != OCCUPIED)
		return (HT_KEY_NOT_FOUND);
	table->entries[index].state = DELETED;
	table->count--;
	return (HT_SUCCESS);
}
