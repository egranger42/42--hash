#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../inc/ht.h"
#include "test_rand.h"

#define GROWTH_INITIAL 4
#define GROWTH_TARGET 100000

typedef struct s_growth_ctx
{
	t_ht		*table;
	t_rand_data	*data;
	size_t		data_count;
	int			failed;
}	t_growth_ctx;

static void	growth_init(t_growth_ctx *ctx)
{
	seed_random(time(NULL));
	ctx->table = ht_create(GROWTH_INITIAL, ht_hash_default, ht_cmp_default);
	ctx->data = rand_data(GROWTH_TARGET);
	ctx->data_count = GROWTH_TARGET;
	ctx->failed = 0;
}

static void	growth_add_phase(t_growth_ctx *ctx)
{
	size_t	i;

	printf("Adding %zu entries to grow table...\n", ctx->data_count);
	i = 0;
	while (i < ctx->data_count)
	{
		if (ht_add(ctx->table, ctx->data[i].key, ctx->data[i].value) != HT_SUCCESS)
		{
			printf("FAIL: Could not add entry %zu\n", i);
			ctx->failed = 1;
			return ;
		}
		if ((i + 1) % 10000 == 0)
			printf("  Added %zu, capacity: %zu, count: %zu\n", i + 1, ctx->table->capacity, ctx->table->count);
		i++;
	}
	printf("OK: Growth phase completed\n");
}

static void	growth_verify_phase(t_growth_ctx *ctx)
{
	size_t	i;
	void	*value;

	printf("Verifying all entries are retrievable...\n");
	i = 0;
	while (i < ctx->data_count)
	{
		if (ht_get(ctx->table, ctx->data[i].key, &value) != HT_SUCCESS)
		{
			printf("FAIL: Could not retrieve entry %zu\n", i);
			ctx->failed = 1;
			return ;
		}
		if (*(int *)value != *(ctx->data[i].value))
		{
			printf("FAIL: Value mismatch at %zu\n", i);
			ctx->failed = 1;
			return ;
		}
		if ((i + 1) % 10000 == 0)
			printf("  Verified %zu entries\n", i + 1);
		i++;
	}
	printf("OK: All entries verified\n");
}

static void	growth_delete_phase(t_growth_ctx *ctx)
{
	size_t	i;
	size_t	delete_count;

	delete_count = ctx->data_count / 2;
	printf("Deleting %zu entries...\n", delete_count);
	i = 0;
	while (i < delete_count)
	{
		ht_delete(ctx->table, ctx->data[i].key);
		i++;
	}
	printf("OK: Deleted %zu entries, remaining: %zu\n", delete_count, ctx->table->count);
}

static void	growth_readd_phase(t_growth_ctx *ctx)
{
	size_t	i;
	size_t	readd_count;

	readd_count = ctx->data_count / 4;
	printf("Re-adding %zu entries...\n", readd_count);
	i = 0;
	while (i < readd_count)
	{
		ht_add(ctx->table, ctx->data[i].key, ctx->data[i].value);
		i++;
	}
	printf("OK: Re-added %zu entries\n", readd_count);
}

int	main(void)
{
	t_growth_ctx	ctx;

	printf("=== Hash Table Growth Test ===\n\n");
	growth_init(&ctx);
	if (!ctx.table || !ctx.data)
	{
		printf("FAIL: Could not initialize growth test\n");
		return (1);
	}
	growth_add_phase(&ctx);
	if (ctx.failed)
		return (1);
	growth_verify_phase(&ctx);
	if (ctx.failed)
		return (1);
	growth_delete_phase(&ctx);
	growth_readd_phase(&ctx);
	printf("OK: Growth test completed\n");
	ht_destroy(ctx.table);
	free_rand_data(ctx.data, ctx.data_count);
	return (0);
}
