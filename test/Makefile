BIN_DIR = ../bin
OBJ_DIR = o
SRC_DIR = .

TEST_BINS = $(BIN_DIR)/test_large_scale \
			$(BIN_DIR)/test_stress \
			$(BIN_DIR)/test_growth

RAND_SRCS = test_rand.c test_rand_str.c test_rand_alloc.c
RAND_OBJS = $(addprefix $(OBJ_DIR)/, $(RAND_SRCS:.c=.o))

TEST_LARGE_SCALE_SRCS = test_large_scale.c
TEST_LARGE_SCALE_OBJS = $(addprefix $(OBJ_DIR)/, $(TEST_LARGE_SCALE_SRCS:.c=.o))

TEST_STRESS_SRCS = test_stress.c
TEST_STRESS_OBJS = $(addprefix $(OBJ_DIR)/, $(TEST_STRESS_SRCS:.c=.o))

TEST_GROWTH_SRCS = test_growth.c
TEST_GROWTH_OBJS = $(addprefix $(OBJ_DIR)/, $(TEST_GROWTH_SRCS:.c=.o))

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I../inc
LIB = ../libht.a
RM = rm -f

all: $(TEST_BINS)

$(BIN_DIR)/test_large_scale: $(TEST_LARGE_SCALE_OBJS) $(RAND_OBJS) $(LIB)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(TEST_LARGE_SCALE_OBJS) $(RAND_OBJS) $(LIB) -o $@

$(BIN_DIR)/test_stress: $(TEST_STRESS_OBJS) $(RAND_OBJS) $(LIB)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(TEST_STRESS_OBJS) $(RAND_OBJS) $(LIB) -o $@

$(BIN_DIR)/test_growth: $(TEST_GROWTH_OBJS) $(RAND_OBJS) $(LIB)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(TEST_GROWTH_OBJS) $(RAND_OBJS) $(LIB) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(TEST_BINS)

re: fclean all

.PHONY: all clean fclean re
