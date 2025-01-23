# Compilador
CC = g++

# Flags de compilação
CFLAGS = -std=c++11 -Wall -I$(INCLUDEDIR)
# Diretórios
SRCDIR = src
OBJDIR = obj
BINDIR = bin
INCLUDEDIR = include

# Nome do executável
EXEC = $(BINDIR)/tp2.out

# Lista de arquivos .c na pasta src
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

# Transforma os arquivos .c em .o
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

# Regra padrão: compilar o executável
all: $(EXEC)

# Regra para compilar o executável
$(EXEC): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(OBJECTS) -o $(EXEC)

# Regra para compilar os arquivos .o a partir dos .c
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para executar os três comandos solicitados
run: all
	$(EXEC)

# Limpar os arquivos compilados
clean:
	rm -rf $(OBJDIR)/*.o $(EXEC)

# Phony targets
.PHONY: all clean run
