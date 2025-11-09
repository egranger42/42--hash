# 42--hash

A generic hash table library implementation in C with dynamic resizing and customizable hash/compare functions.

## Build

```bash
make
make clean
make fclean
make re
```

Produces `libht.a` static library.

## API

- `ht_create(capacity, hash_fn, cmp_fn)` - Create hash table
- `ht_add(table, key, value)` - Insert or update entry
- `ht_get(table, key, value)` - Retrieve value by key
- `ht_delete(table, key)` - Remove entry by key
- `ht_destroy(table)` - Free hash table

Default hash and compare functions provided: `ht_hash_default()`, `ht_cmp_default()`.

## Status Codes

- `HT_SUCCESS` - Operation completed
- `HT_KEY_NOT_FOUND` - Key not found in table
- `HT_KEY_EXISTS` - Key already exists
- `HT_ALLOC_FAILED` - Memory allocation failed
- `HT_INVALID_INPUT` - Invalid parameters

## Testing

```bash
cd test && make
```

Includes stress tests for growth, large-scale operations, and randomized scenarios.
