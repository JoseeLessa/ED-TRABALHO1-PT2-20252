# Nome do executável
TARGET = programa_groner_jose

# Compilador
CC = gcc

# Flags
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

# Pastas
SRC_DIR = src
OBJ_DIR = obj

# Fontes
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/time.c \
       $(SRC_DIR)/bdtimes.c \
       $(SRC_DIR)/partida.c \
       $(SRC_DIR)/bdpartidas.c \
       $(SRC_DIR)/menu.c

# Objetos
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Regra padrão
all: $(TARGET)

# Linkagem
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Compilação
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Rodar
run: all
	./$(TARGET)
