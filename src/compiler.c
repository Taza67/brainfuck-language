/**
 * @file compiler.c
 * @author Mourtaza Akil (akilmourtaza.fr)
 * @brief Module implémentant la compilation de programmes Brainfuck.
 * @date 2024-04-25
 * 
 * 
 */
#include "compiler.h"

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

extern Asttree prog_tree;

/* -------------------------------------------------------------------------- */
/*                                  FONCTIONS                                 */
/* -------------------------------------------------------------------------- */


/* -------------------------------- Bytecode -------------------------------- */

/**
 * @brief Imprime sur la sortie donnée, le bytecode du programme stocké dans
 * l'arbre de syntaxe global.
 * 
 * @param outpath Le fichier de sortie.
 * 
 * @see ast_print
 * @see prog_tree
 */
static void compile_to_bytecode(char *outpath) {
	char *types[] = AST_TYPES_STRINGS;

	// Ouverture du fichier de sortie
	FILE *out = fopen(outpath, "w+");
	if (out == NULL)
		merror("compile_to_bytecode() : Échec de l'ouverture du fichier \"%s\"",
				outpath);
	
	// Compilation
	ast_print(prog_tree, types, out);

	fclose(out);
}

/* --------------------------------- PYTHON --------------------------------- */

/* -------------------------------------------------------------------------- */

/* ------------------------------------ C ----------------------------------- */

/* -------------------------------------------------------------------------- */

/**
 * @brief Retourne le mode de compilation à exécuter.
 * 
 * @param option L'option de compilation utilisée.
 * @param option_arg L'argument donné à l'option.
 * @return int Un mode compilation.
 * 
 * @note Les éléments suivant provoquent une erreur !
 * @note - Option de compilation inconnue.
 * @note - Argument d'option de compilation inconnu ou incompatible.
 */
static int compiler_mode(char *option, char *option_arg) {
	if (strcmp(option, CMODE_BOPTION) == 0) {
		if (strcmp(option_arg, CMODE_PC_ARG) == 0) return CMODE_BPC;
		if (strcmp(option_arg, CMODE_CC_ARG) == 0) return CMODE_BCC;	
		
		merror("compiler_mode() : Argument [%s] inconnu !", option_arg);

	} else if (strcmp(option, CMODE_COPTION) == 0) {
		if (strcmp(option_arg, CMODE_BC_ARG) == 0) return CMODE_CBC;
		if (strcmp(option_arg, CMODE_PC_ARG) == 0) return CMODE_CPC;
		if (strcmp(option_arg, CMODE_CC_ARG) == 0) return CMODE_CCC;
	
		merror("compiler_mode() : Argument [%s] inconnu/incompatible !",
			   option_arg);
	}

	return -1;
}

/**
 * @brief Compile un programme Brainfuck.
 * 
 * @param argc Le nombre d'arguments passés au programme principal.
 * @param argv Les arguments passés au programme principal.
 * 
 * @note Un nombre d'arguments incorrect provoquera une erreur.
 */
void compile(int argc, char *argv[]) {
	char *outpath = NULL, *inpath = NULL;
	int mode = -1;
	
	// Récupération des paramètres
	switch (argc) {
		case 4:
			mode 	= CMODE_CBC;
			inpath  = argv[2]; 
			outpath = argv[3];
			break;
		case 5:
			mode	= compiler_mode(argv[1], argv[2]);
			inpath  = argv[3];
			outpath = argv[4];
			break;
		default:
			merror("compile() : Nombre d'argument [%d] incorrect !", argc);	
	}
	
	// Analyse
	switch (mode) {
		case CMODE_BCC:
		case CMODE_BPC:
			parse(inpath, &aain, aaparse, aalex_destroy); break;
		case CMODE_CCC:
		case CMODE_CBC:
		case CMODE_CPC: parse(inpath, &ccin, ccparse, cclex_destroy); break;
	}

	// Compilation
	switch (mode) {
		case CMODE_CBC: compile_to_bytecode(outpath); break;
	}
}

/* -------------------------------------------------------------------------- */
