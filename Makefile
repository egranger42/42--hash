NAME = libht.a

SRC_DIR = src
INC_DIR = inc
OBJ_DIR = o
BIN_DIR = bin

SRCS = ht_create.c \
		ht_hash.c \
		ht_probe.c \
		ht_get.c \
		ht_delete.c \
		ht_destroy.c \
		ht_resize.c \
		ht_add.c

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR)
AR = ar rc
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
