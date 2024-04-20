# ---------------------------------------------------------------------------- #
#                                   VARIABLES                                  #
# ---------------------------------------------------------------------------- #

# Make
MAKE = make

# Compilateur
CC      = gcc
CFLAGS  = -std=c11 -Wall -Wextra -g -pedantic -O3
LDFLAGS = -ll

# LEX - YACC
LEX    = lex
YACC   = bison
YFLAGS = -d -Wcounterexamples

# Exécutables
EXEC = brainfuck

# Répertoires
SRC_DIR = ./src
INC_DIR = ./inc
OBJ_DIR = ./obj

## Parser
PAR_DIR  = ./par
LSRC_DIR = $(PAR_DIR)/lsrc
YSRC_DIR = $(PAR_DIR)/ysrc
POBJ_DIR = $(PAR_DIR)/pobj

# Fichiers
SRC = $(shell find $(SRC_DIR) -name "*.c")
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
INC = -I$(INC_DIR) -I$(YSRC_DIR)

## Lex
LSRC = $(shell find $(LSRC_DIR) -name "*.l")
LOUT = $(LSRC:$(LSRC_DIR)/%.l=$(LSRC_DIR)/%.yy.c)
LOBJ = $(LOUT:$(LSRC_DIR)/%.yy.c=$(POBJ_DIR)/%.yy.o)

## Yacc
YSRC = $(shell find $(YSRC_DIR) -name "*.y")
YOUT = $(YSRC:$(YSRC_DIR)/%.y=$(YSRC_DIR)/%.tab.c)
YOBJ = $(YOUT:$(YSRC_DIR)/%.tab.c=$(POBJ_DIR)/%.tab.o)

# Affichage
VERBOSE ?= 1
OUTPUT  ?= $(if $(filter $(VERBOSE), 0), /dev/null, /dev/stdout)

# ---------------------------------------------------------------------------- #
#                                   FONCTIONS                                  #
# ---------------------------------------------------------------------------- #

.PHONY: build rebuild clean help .all .directories
.PRECIOUS: $(OBJ) $(LOUT) $(YOUT) $(LOBJ)

# ---------------------------------------------------------------------------- #

build:
	@echo "- Building..." > $(OUTPUT)
	@$(MAKE) .directories --no-print-directory
	@$(MAKE) .all --no-print-directory
	@echo "- Building done !" > $(OUTPUT)

rebuild:
	@$(MAKE) clean --no-print-directory
	@$(MAKE) build --no-print-directory

clean:
	@echo "- Cleaning..." > $(OUTPUT)
	@rm -rf $(SRC_DIR)/*~ $(OBJ_DIR) $(EXEC) $(POBJ_DIR)
	@rm -rf $(shell find $(PAR_DIR) -type f ! \( -name "*.l" -o -name "*.y" \))
	@echo "- Cleaning done !" > $(OUTPUT)

help:
	@echo "- Availables targets :\n"
	@echo "- + build       - Build the project."
	@echo "- + rebuild     - Clean and build the project."
	@echo "- + clean       - Remove build elements."
	@echo "- + help        - Display this help notice."

# ---------------------------------------------------------------------------- #

.directories:
	@echo "+ - Creating directories..." > $(OUTPUT)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(POBJ_DIR)
	@echo "+ - Creating directories done !" > $(OUTPUT)

.all: $(EXEC)

# ---------------------------------------------------------------------------- #
#                                  COMPILATION                                 #
# ---------------------------------------------------------------------------- #

# Exécutable

$(EXEC): $(YOBJ) $(LOBJ) $(OBJ)
	@echo "+ - Linking \"$(notdir $@)\"..."
	@$(CC) $^ $(INC) -o $@ $(LDFLAGS)
	@echo "+ - Linking done"

## LEX - YACC

$(POBJ_DIR)/%.tab.o: $(YSRC_DIR)/%.tab.c
	@echo "+ - Compiling \"$(notdir $<)\""
	@$(CC) -o $@ -c $^ $(INC)

$(YSRC_DIR)/%.tab.c: $(YSRC_DIR)/%.y
	@echo "+ - Compiling \"$(notdir $<)\""
	@$(YACC) -o $@ $(YFLAGS) $^

$(POBJ_DIR)/%.yy.o: $(LSRC_DIR)/%.yy.c
	@echo "+ - Compiling \"$(notdir $<)\""
	@$(CC) -o $@ -c $^ $(INC)

$(LSRC_DIR)/%.yy.c: $(LSRC_DIR)/%.l
	@echo "+ - Compiling \"$(notdir $<)\""
	@$(LEX) -o $@ $^

# Objets

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@echo "+ - Compiling \"$(notdir $<)\"" > $(OUTPUT)
	@$(CC) -o $@ -c $< $(CFLAGS) $(INC)

# ---------------------------------------------------------------------------- #