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

/**
 * @brief Fonction auxiliaire à ast_to_python.
 * 
 * Imprime le programme Python correspondant à l'arbre donné sur la
 * sortie donnée.
 * 
 * @param out Le fichier de sortie.
 * @param tree L'arbre à convertir.
 * @param depth La profondeur (indentation) de l'arbre.
 * 
 * @note Un type d'arbre inconnue provoquera une erreur.
 */
static void ast_to_python_aux(FILE *out, Asttree tree, int depth) {
	int count;

	if (ast_is_empty(tree)) return;

	// Le champ 'numéro lexical' est utilisé pour indiquer le nombre
	// d'opérations simples successives.
	count = tree->id_lex;

	switch (tree->type) {
		case A_LOOP:
			print_indent(out, depth);
			fprintf(out, PYTHON_LOOP);
			ast_to_python_aux(out, tree->son, depth + 1);
			break;
		case A_INC:
			print_simple_inst(out, PYTHON_INC, count, depth);
			break;
		case A_DEC:
			print_simple_inst(out, PYTHON_DEC, count, depth);
			break;
		case A_LEFT:
			print_simple_inst(out, PYTHON_LEFT, count, depth);
			break;
		case A_RIGHT:
			print_simple_inst(out, PYTHON_RIGHT, count, depth);
			break;
		case A_PUT:
			print_simple_inst(out, PYTHON_PUT, count, depth);
			break;
		case A_GET:
			print_simple_inst(out, PYTHON_GET, count, depth);
			break;
		default:
			merror("ast_to_python_aux() : 'tree->type' inconnu !");
	}

	ast_to_python_aux(out, tree->little_brother, depth);
}

/**
 * @brief Convertis un arbre de syntaxe abstraite d'un programme Brainfuck en
 * un programme Python.
 * 
 * @param out Le fichier de sortie.
 * @param tree L'arbre de syntaxe à convertir.
 */
void ast_to_python(FILE *out, Asttree tree) {
	fprintf(out, PYTHON_HEADER);
	ast_to_python_aux(out, tree, 1);
	fprintf(out, PYTHON_FOOTER);
}

/**
 * @brief Convertis l'arbre de syntaxe abstraite global en un programme Python.
 * 
 * @param outpath Le fichier de sortie.
 */
static void compile_to_python(char *outpath) {
	// Ouverture du fichier de sortie
	FILE *out = fopen(outpath, "w+");
	if (out == NULL)
		merror("compile_to_python() : Échec de l'ouverture du fichier \"%s\"",
			   outpath);
	
	// Compilation
	ast_to_python(out, prog_tree);

	fclose(out);
}

/* ------------------------------------ C ----------------------------------- */

/**
 * @brief Fonction auxiliaire à ast_to_c.
 * 
 * Imprime le programme C correspondant à l'arbre donné sur la
 * sortie donnée.
 * 
 * @param out Le fichier de sortie.
 * @param tree L'arbre à convertir.
 * @param depth La profondeur (indentation) de l'arbre.
 * 
 * @note Un type d'arbre inconnue provoquera une erreur.
 */
static void ast_to_c_aux(FILE *out, Asttree tree, int depth) {
	int count;

	if (ast_is_empty(tree)) return;

	// Le champ 'numéro lexical' est utilisé pour indiquer le nombre
	// d'opérations simples successives.
	count = tree->id_lex;

	switch (tree->type) {
		case A_LOOP:
			print_indent(out, depth);
			fprintf(out, C_LOOP_BEGIN);
			ast_to_c_aux(out, tree->son, depth + 1);
			fprintf(out, C_LOOP_END);
			break;
		case A_INC:
			print_simple_inst(out, C_INC, count, depth);
			break;
		case A_DEC:
			print_simple_inst(out, C_DEC, count, depth);
			break;
		case A_LEFT:
			print_simple_inst(out, C_LEFT, count, depth);
			break;
		case A_RIGHT:
			print_simple_inst(out, C_RIGHT, count, depth);
			break;
		case A_PUT:
			print_simple_inst(out, C_PUT, count, depth);
			break;
		case A_GET:
			print_simple_inst(out, C_GET, count, depth);
			break;
		default:
			merror("ast_to_c_aux() : 'tree->type' inconnu !");
	}

	ast_to_c_aux(out, tree->little_brother, depth);
}

/**
 * @brief Convertis un arbre de syntaxe abstraite d'un programme Brainfuck en
 * un programme C.
 * 
 * @param out Le fichier de sortie.
 * @param tree L'arbre de syntaxe à convertir.
 */
void ast_to_c(FILE *out, Asttree tree) {
	fprintf(out, C_HEADER);
	ast_to_c_aux(out, tree, 1);
	fprintf(out, C_FOOTER);
}

/**
 * @brief Convertis l'arbre de syntaxe abstraite global en un programme C.
 * 
 * @param outpath Le fichier de sortie.
 */
static void compile_to_c(char *outpath) {
	// Ouverture du fichier de sortie
	FILE *out = fopen(outpath, "w+");
	if (out == NULL)
		merror("compile_to_c() : Échec de l'ouverture du fichier \"%s\"",
			   outpath);
	
	// Compilation
	ast_to_c(out, prog_tree);

	fclose(out);
}

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
		case CMODE_CPC:
		case CMODE_BPC: compile_to_python(outpath);   break;
		case CMODE_CCC:
		case CMODE_BCC: compile_to_c(outpath);		  break;
	}

	ast_free(prog_tree);
	prog_tree = NULL;
}

/* -------------------------------------------------------------------------- */
