#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/ht.h"

int	main(void)
{
	t_ht	*table;
	void	*value;
	int		*num1;
	int		*num2;
	int		*num3;

	printf("=== Hash Table Test ===\n\n");

	printf("Creating hash table with capacity 16...\n");
	table = ht_create(16, ht_hash_default, ht_cmp_default);
	if (!table)
	{
		printf("FAIL: Could not create hash table\n");
		return (1);
	}
	printf("OK: Hash table created\n\n");

	num1 = malloc(sizeof(int));
	num2 = malloc(sizeof(int));
	num3 = malloc(sizeof(int));
	*num1 = 100;
	*num2 = 200;
	*num3 = 300;

	printf("Adding key1=100...\n");
	if (ht_add(table, "key1", num1) != HT_SUCCESS)
	{
		printf("FAIL: Could not add key1\n");
		return (1);
	}
	printf("OK: key1 added\n\n");

	printf("Adding key2=200...\n");
	if (ht_add(table, "key2", num2) != HT_SUCCESS)
	{
		printf("FAIL: Could not add key2\n");
		return (1);
	}
	printf("OK: key2 added\n\n");

	printf("Adding key3=300...\n");
	if (ht_add(table, "key3", num3) != HT_SUCCESS)
	{
		printf("FAIL: Could not add key3\n");
		return (1);
	}
	printf("OK: key3 added\n\n");

	printf("Retrieving key1...\n");
	if (ht_get(table, "key1", &value) != HT_SUCCESS)
	{
		printf("FAIL: Could not get key1\n");
		return (1);
	}
	if (*(int *)value != 100)
	{
		printf("FAIL: key1 value mismatch\n");
		return (1);
	}
	printf("OK: key1 retrieved, value=%d\n\n", *(int *)value);

	printf("Retrieving key2...\n");
	if (ht_get(table, "key2", &value) != HT_SUCCESS)
	{
		printf("FAIL: Could not get key2\n");
		return (1);
	}
	if (*(int *)value != 200)
	{
		printf("FAIL: key2 value mismatch\n");
		return (1);
	}
	printf("OK: key2 retrieved, value=%d\n\n", *(int *)value);

	printf("Updating key1 to 150...\n");
	*num1 = 150;
	if (ht_add(table, "key1", num1) != HT_SUCCESS)
	{
		printf("FAIL: Could not update key1\n");
		return (1);
	}
	printf("OK: key1 updated\n");

	if (ht_get(table, "key1", &value) != HT_SUCCESS)
	{
		printf("FAIL: Could not get updated key1\n");
		return (1);
	}
	if (*(int *)value != 150)
	{
		printf("FAIL: key1 updated value mismatch\n");
		return (1);
	}
	printf("OK: key1 verified, new value=%d\n\n", *(int *)value);

	printf("Deleting key2...\n");
	if (ht_delete(table, "key2") != HT_SUCCESS)
	{
		printf("FAIL: Could not delete key2\n");
		return (1);
	}
	printf("OK: key2 deleted\n\n");

	printf("Attempting to retrieve deleted key2...\n");
	if (ht_get(table, "key2", &value) == HT_KEY_NOT_FOUND)
	{
		printf("OK: key2 correctly returns KEY_NOT_FOUND\n\n");
	}
	else
	{
		printf("FAIL: deleted key2 still found\n");
		return (1);
	}

	printf("Attempting to retrieve non-existent key...\n");
	if (ht_get(table, "nonexistent", &value) == HT_KEY_NOT_FOUND)
	{
		printf("OK: non-existent key returns KEY_NOT_FOUND\n\n");
	}
	else
	{
		printf("FAIL: non-existent key found\n");
		return (1);
	}

	printf("Destroying hash table...\n");
	ht_destroy(table);
	printf("OK: Hash table destroyed\n\n");

	free(num1);
	free(num2);
	free(num3);

	printf("=== All tests passed! ===\n");
	return (0);
}
