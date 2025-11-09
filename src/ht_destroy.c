#include "ht.h"

void	ht_destroy(t_ht *table)
{
	if (!table)
		return ;
	free(table->entries);
	free(table);
}
