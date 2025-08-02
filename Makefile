# Colors
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
NC = \033[0m

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 -march=native -ffast-math -flto -fno-trapping-math -funroll-loops 
RM = rm -f

# Directories
SRCDIR = src
INCDIR = includes
LIBFTDIR = libraries/libft
MLX42DIR = libraries/MLX42
OBJDIR = obj

# Include paths
INCLUDES = -I$(INCDIR) -I$(LIBFTDIR) -I$(MLX42DIR)/include -I.

# Target
NAME = cube

# Libraries
LIBFT = $(LIBFTDIR)/libft.a
MLX42_LIB = $(MLX42DIR)/build/libmlx42.a

# MLX42 flags (detecta automáticamente el sistema)
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    MLX42_FLAGS = -lglfw -ldl -lm
endif
ifeq ($(UNAME_S),Darwin)
    MLX42_FLAGS = -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/"
endif

# Source files
MAIN_SRC = 		main.c
INIT_SRC =		$(SRCDIR)/init/cube_init.c \
				$(SRCDIR)/init/game_init.c

PARSER_SRC =	$(SRCDIR)/parser/parser.c \
            	$(SRCDIR)/parser/parser_file.c \
            	$(SRCDIR)/parser/parser_textures.c \
            	$(SRCDIR)/parser/parser_rgb.c \
            	$(SRCDIR)/parser/parser_map.c \
            	$(SRCDIR)/parser/flood_fill.c \
            	$(SRCDIR)/parser/flood_fill_utils.c \
            	$(SRCDIR)/parser/parser_utils.c

RAYCASTING_SRC =$(SRCDIR)/raycasting/render.c

UTILS_SRC =		$(SRCDIR)/utils/collector.c \
				$(SRCDIR)/utils/utils.c

# All source files
SRC = $(MAIN_SRC) $(PARSER_SRC) $(INIT_SRC) $(RENDER_SRC) $(RAYCASTING_SRC) $(UTILS_SRC)

# Object files - CORREGIDO
MAIN_OBJ = $(OBJDIR)/main.o
OTHER_SRC = $(PARSER_SRC) $(INIT_SRC) $(RENDER_SRC) $(RAYCASTING_SRC) $(UTILS_SRC)
OTHER_OBJ = $(OTHER_SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJ = $(MAIN_OBJ) $(OTHER_OBJ)

# Headers
HEADERS = $(INCDIR)/cube.h $(LIBFTDIR)/libft.h

# Rules
.PHONY: all clean fclean re info

all: $(NAME)

$(NAME): $(LIBFT) $(MLX42_LIB) $(OBJ) Makefile
	@echo "$(CYAN)Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJ) -L$(LIBFTDIR) -lft -L$(MLX42DIR)/build -lmlx42 $(MLX42_FLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) creado con éxito!$(NC)"

$(LIBFT): $(shell find $(LIBFTDIR) -name "*.c" -o -name "*.h")
	@echo "$(CYAN)[LIBFT] Building libft...$(NC)"
	@$(MAKE) -C $(LIBFTDIR) --no-print-directory

$(MLX42_LIB):
	@echo "$(CYAN)[MLX42] Building MLX42...$(NC)"
	@cd $(MLX42DIR) && cmake -B build && make -C build --no-print-directory

# Regla específica para main.c - NUEVA
$(OBJDIR)/main.o: main.c $(HEADERS) Makefile | $(OBJDIR)
	@printf "$(CYAN)[MAIN]$(NC) $(WHITE)main.c$(NC)\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Regla para archivos en src/
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS) Makefile | $(OBJDIR)
	@mkdir -p $(dir $@)
	@if echo "$<" | grep -q "/init/"; then \
		printf "$(CYAN)[INIT]$(NC) "; \
	elif echo "$<" | grep -q "/parser/"; then \
		printf "$(BLUE)[PARSER]$(NC) "; \
	elif echo "$<" | grep -q "/minimap/"; then \
		printf "$(MAGENTA)[MINIMAP]$(NC) "; \
	fi; \
	printf "$(WHITE)$<$(NC)\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/init
	@mkdir -p $(OBJDIR)/parser
	@mkdir -p $(OBJDIR)/minimap

clean:
	@echo "$(YELLOW)Cleaning object files...$(NC)"
	@$(MAKE) clean -C $(LIBFTDIR) --no-print-directory
	@if [ -d "$(MLX42DIR)/build" ]; then \
		echo "$(YELLOW)Cleaning MLX42...$(NC)"; \
		$(MAKE) clean -C $(MLX42DIR)/build --no-print-directory 2>/dev/null || true; \
	fi
	@$(RM) -r $(OBJDIR)

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(NC)"
	@$(RM) $(NAME)
	@$(MAKE) fclean -C $(LIBFTDIR) --no-print-directory
	@if [ -d "$(MLX42DIR)/build" ]; then \
		echo "$(RED)Removing MLX42 build...$(NC)"; \
		$(RM) -r $(MLX42DIR)/build; \
	fi

re: fclean all

# Debug info
info:
	@echo "$(YELLOW)Project structure:$(NC)"
	@echo "Source files: $(words $(SRC))"
	@echo "Object files: $(words $(OBJ))"
	@echo "Include paths: $(INCLUDES)"
	@echo ""
	@echo "$(YELLOW)Modules breakdown:$(NC)"
	@echo "$(CYAN)  MAIN:$(NC) $(words $(MAIN_SRC)) files"
	@echo "$(BLUE)  PARSER:$(NC) $(words $(PARSER_SRC)) files"
	@echo "$(CYAN)  INIT:$(NC) $(words $(INIT_SRC)) files"
	@echo "$(MAGENTA)  MINIMAP:$(NC) $(words $(RENDER_SRC)) files"
	@echo ""
	@echo "$(YELLOW)Libraries:$(NC)"
	@echo "$(CYAN)  LIBFT:$(NC) $(LIBFT)"
	@echo "$(MAGENTA)  MLX42:$(NC) $(MLX42_LIB)"