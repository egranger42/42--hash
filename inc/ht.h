#ifndef HT_H
#define HT_H

#include <stdlib.h>
#include <stdint.h>

typedef enum s_ht_status
{
	HT_SUCCESS = 0,
	HT_ALLOC_FAILED = 1,
	HT_KEY_NOT_FOUND = 2,
	HT_KEY_EXISTS = 3,
	HT_INVALID_INPUT = 4
}	t_ht_status;

typedef enum s_ht_entry_state
{
	EMPTY = 0,
	OCCUPIED = 1,
	DELETED = 2
}	t_ht_entry_state;

typedef struct s_ht_entry
{
	void				*key;
	void				*value;
	t_ht_entry_state	state;
}	t_ht_entry;

typedef uint64_t (*t_ht_hash_fn)(const void *key);
typedef int (*t_ht_cmp_fn)(const void *key1, const void *key2);

typedef struct s_ht
{
	t_ht_entry	*entries;
	size_t		capacity;
	size_t		count;
	t_ht_hash_fn	hash_fn;
	t_ht_cmp_fn	cmp_fn;
}	t_ht;

t_ht			*ht_create(size_t capacity, t_ht_hash_fn hash_fn, t_ht_cmp_fn cmp_fn);
t_ht_status		ht_add(t_ht *table, void *key, void *value);
t_ht_status		ht_get(t_ht *table, void *key, void **value);
t_ht_status		ht_delete(t_ht *table, void *key);
void			ht_destroy(t_ht *table);

uint64_t		ht_hash_default(const void *key);
int				ht_cmp_default(const void *key1, const void *key2);
const char		*ht_status_msg(t_ht_status status);

#endif
