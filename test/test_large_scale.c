#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../inc/ht.h"
#include "test_rand.h"

#define LARGE_SCALE_SIZE 1000000
#define READ_COUNT 100000
#define DELETE_COUNT 50000

typedef struct s_test_ctx
{
	t_ht		*table;
	t_rand_data	*data;
	size_t		total;
	int			failed;
}	t_test_ctx;

static void	test_init(t_test_ctx *ctx)
{
	seed_random(time(NULL));
	ctx->table = ht_create(256, ht_hash_default, ht_cmp_default);
	ctx->data = NULL;
	ctx->total = 0;
	ctx->failed = 0;
}

static void	test_large_add(t_test_ctx *ctx)
{
	size_t	i;
	clock_t	start;
	clock_t	end;

	printf("Generating %d random entries...\n", LARGE_SCALE_SIZE);
	ctx->data = rand_data(LARGE_SCALE_SIZE);
	if (!ctx->data)
	{
		printf("FAIL: Could not generate random data\n");
		ctx->failed = 1;
		return ;
	}
	start = clock();
	printf("Adding %d entries...\n", LARGE_SCALE_SIZE);
	i = 0;
	while (i < LARGE_SCALE_SIZE)
	{
		if (ht_add(ctx->table, ctx->data[i].key, ctx->data[i].value) != HT_SUCCESS)
		{
			ctx->failed = 1;
			break ;
		}
		if ((i + 1) % 100000 == 0)
			printf("  Added %zu entries, capacity: %zu, count: %zu\n", i + 1, ctx->table->capacity, ctx->table->count);
		i++;
	}
	end = clock();
	if (!ctx->failed)
		printf("OK: Added %d entries in %.2f seconds\n", LARGE_SCALE_SIZE, (double)(end - start) / CLOCKS_PER_SEC);
}

int	main(void)
{
	t_test_ctx	ctx;

	printf("=== Hash Table Large Scale Test ===\n\n");
	test_init(&ctx);
	if (!ctx.table)
	{
		printf("FAIL: Could not create hash table\n");
		return (1);
	}
	test_large_add(&ctx);
	if (ctx.failed)
	{
		printf("FAIL: Large scale add test failed\n");
		return (1);
	}
	printf("OK: All large scale tests passed\n");
	ht_destroy(ctx.table);
	if (ctx.data)
		free_rand_data(ctx.data, LARGE_SCALE_SIZE);
	return (0);
}
