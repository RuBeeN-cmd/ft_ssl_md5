# ------------ COLORS --------------

_END="\033[0m"
_RED="\033[0;31m"
_GREEN="\033[0;32m"
_YELLOW="\033[0;33m"
_CYAN="\033[0;36m"

# ----------------------------------

NAME = ft_ssl

SRC_DIR = srcs
OBJ_DIR = objs

SRC = main.c \
	utils/ansi_color.c \
	utils/log.c \
	parsing/args.c \
	parsing/dbg.c \
	md5.c \
	sha256.c \
	block.c

CC = clang
CFLAGS = -Wall -Werror -Wextra
INC = -Iincludes

# ------------- LIBS ----------------

LIBFT_DIR = libft
LIBFT_INCLUDE = $(LIBFT_DIR)/includes
LIBFT = $(LIBFT_DIR)/libft.a

LIB = $(LIBFT)
LIBFLAGS = -L$(dir $(LIBFT))
LIBFLAGS += -Wl,-rpath,$(dir $(LIBFT))
LIBFLAGS += -lft
LIBFLAGS += -lm
INC += -I$(LIBFT_INCLUDE)
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# ----------------------------------

all: $(NAME)

$(NAME): $(LIB) $(OBJ_DIR) $(OBJ)
	@echo $(_GREEN)Compiling $(OBJ)...$(_END)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFLAGS) -o $@

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo $(_CYAN)Compiling $<...$(_END)
	@$(CC) -o $@ -c $< $(CFLAGS) $(INC)

# ------- LIBFT -------

%.a:
	@make -C $(dir $@)
	
# ---------- Public targets ----------

libft: $(LIBFT)
libft_clean:
	@make -C $(LIBFT_DIR) fclean
clean:
	@echo $(_YELLOW)Cleaning $(OBJ)...$(_END)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo $(_RED)Cleaning $(NAME)...$(_END)
	@rm -f $(NAME)

ffclean: fclean libft_clean

re: fclean all

.PHONY: all clean fclean re ffclean libft libft_clean