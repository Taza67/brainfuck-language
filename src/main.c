#include "brainfuck.h"
#include "parser.h"
#include "compiler.h"
#include "decompiler.h"
#include "vm.h"
#include "parser_ast.tab.h"
#include "parser_code.tab.h"

/* -------------------------------------------------------------------------- */
/*                                   PARSER                                   */
/* -------------------------------------------------------------------------- */

extern FILE* ccin;
extern FILE* aain;
extern int cclex_destroy(void);
extern int aalex_destroy(void);

/* -------------------------------------------------------------------------- */
/*                             VARIABLES GLOBALES                             */
/* -------------------------------------------------------------------------- */

/**
 * @var Asttree prog_tree
 * @brief Variable permettant de stocker les arbres de syntaxe abstraite
 * calculés par les analyseurs.
 * 
 */
Asttree prog_tree;

/* -------------------------------------------------------------------------- */
/*                                    MAIN                                    */
/* -------------------------------------------------------------------------- */

/**
 * @brief Récupère le mode d'exécution du programme à partir des arguments
 * d'appel.
 * 
 * @param argc Le nombre d'arguments.
 * @param argv Les arguments.
 * @return int Un mode d'exécution du programme.
 * 
 * @note Un nombre d'arguments incorrect provoque une erreur.
 */
int mode(int argc, char *argv[]) {
	int mode = -1;

	switch (argc) {
		case 1:
			return MODE_HELP;
		case 2: 
			if (strcmp(argv[1], "-h") == 0) 	mode = MODE_HELP;
			break;
		case 3:
			if (strcmp(argv[1], "-i") == 0) 	mode = MODE_INTERPRET;
			if (strcmp(argv[1], "-ib") == 0) 	mode = MODE_VM;
			break;
		case 4:
			if (strcmp(argv[1], "-c") == 0) 	mode = MODE_COMPILE;
			if (strcmp(argv[1], "-d") == 0)		mode = MODE_DECOMPILE;
			break;
		case 5:
			if (strcmp(argv[1], "-c") == 0)		mode = MODE_COMPILE;
			if (strcmp(argv[1], "-cb") == 0)	mode = MODE_COMPILE;
			break;
		default:
			usage(argv[0], "Le nombre d'arguments [%d] est incorrect !", argc);
			exit(EXIT_FAILURE);
	}

	return mode;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief Exécute le programme selon le mode donné.
 * 
 * @param mode Le mode d'exécution du programme
 * @param argv Les arguments du programme.
 * 
 * @note Un mode d'exécution inconnu provoque une erreur.
 */
void exec(int mode, int argc, char *argv[]) {
	switch (mode) {
		case MODE_HELP:
			usage(argv[0], "");
			break;
		case MODE_INTERPRET:
			parse(argv[2], &ccin, ccparse, cclex_destroy);
			execute_program(prog_tree);
			break;
		case MODE_COMPILE:
			compile(argc, argv);
			break;
		case MODE_DECOMPILE:
			decompile(argv[2], argv[3]);
			break;
		case MODE_VM:
			parse(argv[2], &aain, aaparse, aalex_destroy);
			execute_program(prog_tree);
			break;
		default:
			usage(argv[0], "L'option [%s] est incorrecte/mal utilisée !",
				  argv[1]);
			exit(EXIT_FAILURE);
	}
}

/* -------------------------------------------------------------------------- */

/**
 * @brief Point d'entrée du programme.
 * 
 * @param argc Le nombre d'arguments du programme.
 * @param argv Les argument du programme.
 * @return int Résultat d'exécution du programme.
 */
int main(int argc, char *argv[]) {
	int m;

	m = mode(argc, argv);
	exec(m, argc, argv);

	ast_free(prog_tree);
	exit(EXIT_SUCCESS);
}

/* -------------------------------------------------------------------------- */
