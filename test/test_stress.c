#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../inc/ht.h"
#include "test_rand.h"

#define STRESS_BASE_SIZE 1000
#define STRESS_OPS 30000
#define OP_ADD 0
#define OP_GET 1
#define OP_DELETE 2

typedef struct s_stress_ctx
{
	t_ht		*table;
	t_rand_data	*data;
	size_t		data_count;
	size_t		adds;
	size_t		gets;
	size_t		deletes;
	int			failed;
}	t_stress_ctx;

static void	stress_init(t_stress_ctx *ctx)
{
	seed_random(time(NULL));
	ctx->table = ht_create(32, ht_hash_default, ht_cmp_default);
	ctx->data = rand_data(STRESS_BASE_SIZE);
	ctx->data_count = STRESS_BASE_SIZE;
	ctx->adds = 0;
	ctx->gets = 0;
	ctx->deletes = 0;
	ctx->failed = 0;
}

static void	stress_random_op(t_stress_ctx *ctx)
{
	size_t		idx;
	int			op;
	void		*value;

	idx = rand_uint32() % ctx->data_count;
	op = rand_uint32() % 3;
	if (op == OP_ADD)
	{
		ht_add(ctx->table, ctx->data[idx].key, ctx->data[idx].value);
		ctx->adds++;
	}
	else if (op == OP_GET)
	{
		ht_get(ctx->table, ctx->data[idx].key, &value);
		ctx->gets++;
	}
	else if (op == OP_DELETE)
	{
		ht_delete(ctx->table, ctx->data[idx].key);
		ctx->deletes++;
	}
}

static void	stress_run(t_stress_ctx *ctx)
{
	size_t	i;
	clock_t	start;
	clock_t	end;

	printf("Running %d random operations...\n", STRESS_OPS);
	start = clock();
	i = 0;
	while (i < STRESS_OPS)
	{
		stress_random_op(ctx);
		if ((i + 1) % 5000 == 0)
			printf("  %zu ops, capacity: %zu, count: %zu\n", i + 1, ctx->table->capacity, ctx->table->count);
		i++;
	}
	end = clock();
	printf("OK: Completed %d operations in %.2f seconds\n", STRESS_OPS, (double)(end - start) / CLOCKS_PER_SEC);
	printf("  Adds: %zu, Gets: %zu, Deletes: %zu\n", ctx->adds, ctx->gets, ctx->deletes);
}

int	main(void)
{
	t_stress_ctx	ctx;

	printf("=== Hash Table Stress Test ===\n\n");
	stress_init(&ctx);
	if (!ctx.table || !ctx.data)
	{
		printf("FAIL: Could not initialize stress test\n");
		return (1);
	}
	stress_run(&ctx);
	printf("OK: Stress test completed\n");
	ht_destroy(ctx.table);
	free_rand_data(ctx.data, ctx.data_count);
	return (0);
}
