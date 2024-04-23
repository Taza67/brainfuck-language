/**
 * @file vm.c
 * @author Mourtaza Akil (akilmourtaza.fr)
 * @brief Module implémentant la machine virtuelle de l'interpréteur
 * Brainfuck.
 * @date 2024-04-20
 * 
 * 
 */
#include "vm.h"

/* -------------------------------------------------------------------------- */
/*                             VARIABLES GLOBALES                             */
/* -------------------------------------------------------------------------- */

/**
 * @var int * data_stack
 * @brief Pile de données de l'interpréteur Brainfuck.
 */
static int *data_stack;

/* -------------------------------------------------------------------------- */

/**
 * @var int * ptr
 * @brief Pointeur de données de l'interpréteur Brainfuck.
 * 
 */
static int *ptr;

/* -------------------------------------------------------------------------- */
/*                                  FONCTIONS                                 */
/* -------------------------------------------------------------------------- */

/**
 * @brief Initialise la pile de données de l'interpréteur Brainfuck.
 * 
 */
static void init_stack() {
	data_stack = (int *)calloc(DATA_STACK_SIZE, sizeof(int));
	ptr = data_stack;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief Exécute une instruction Brainfuck représentée sous la forme d'un
 * arbre de syntaxe abstraite (AST).
 * 
 * @param tree L'arbre de syntaxe abstraite (AST) de l'instruction.
 * 
 * @note Cette fonction exécute en chaîne toutes les instructions qui suivent
 * l'instruction donnée.
 */
static void execute_instruction(Asttree tree) {
	int ast_type, count;

	if (ast_is_empty(tree)) return;

	// Le champ 'numéro lexical' est utilisé pour indiquer le nombre
	// d'opérations simples successives.
	count = tree->id_lex;

	ast_type = tree->type;
	switch (ast_type) {
		case A_LOOP:
			while (*ptr != 0)
				execute_instruction(tree->son);
			execute_instruction(tree->little_brother);
			break;
		case A_INC:
			(*ptr) += count;
			execute_instruction(tree->little_brother);
			break;
		case A_DEC:
			(*ptr) -= count;
			execute_instruction(tree->little_brother);
			break;
		case A_LEFT:
			ptr -= count;
			execute_instruction(tree->little_brother);
			break;
		case A_RIGHT:
			ptr += count;
			execute_instruction(tree->little_brother);
			break;
		case A_PUT:
			for (int i = 0;  i < count; i++)
				putchar(*ptr);

			execute_instruction(tree->little_brother);
			break;
		case A_GET:
			for (int i = 0; i < count; i++)
				*ptr = getchar();

			EMPTY_BUFFER();
			execute_instruction(tree->little_brother);
			break;
		default:
			merror("execute_instruction() : 'tree->type' inconnu !");
	}
}

/* -------------------------------------------------------------------------- */

/**
 * @brief Libère la mémoire allouée à la pile de données de l'interpréteur
 * Brainfuck.
 * 
 */
static void free_stack() {
	free(data_stack);
	data_stack = NULL;
	ptr = NULL;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief Exécute un programme Brainfuck représenté sous forme d'un arbre de
 * syntaxe abstraite (AST).
 * 
 * @param tree L'arbre de syntaxe abstraite (AST) à exécuter.
 */
void execute_program(Asttree tree) {
	init_stack();
	execute_instruction(tree);
	free_stack();
}

/* -------------------------------------------------------------------------- */
