/**
 * @file decompiler.c
 * @author Mourtaza Akil (akilmourtaza.fr)
 * @brief Module implémentant la décompilation de bytecode ou d'arbres de
 * syntaxe abstraite de programmes Brainfuck obtenus grâce au module 'compiler'.
 * @date 2024-04-26
 * 
 * 
 */
#include "decompiler.h"

/* -------------------------------------------------------------------------- */
/*                                   PARSER                                   */
/* -------------------------------------------------------------------------- */

extern FILE *aain;
extern int aalex_destroy();

/* -------------------------------------------------------------------------- */
/*                             VARIABLES GLOBALES                             */
/* -------------------------------------------------------------------------- */

extern Asttree prog_tree;

/* -------------------------------------------------------------------------- */
/*                                  FONCTIONS                                 */
/* -------------------------------------------------------------------------- */

/**
 * @brief Convertis un arbre de syntaxe abstraite d'un programme Brainfuck en
 * programme Brainfuck.
 * 
 * @param out Le fichier de sortie.
 * @param tree L'arbre de syntaxe à convertir.
 */
void ast_to_brainfuck(FILE *out, Asttree tree) {
	int count;

	if (tree == NULL) return;

	// Le champ 'numéro lexical' est utilisé pour indiquer le nombre
	// d'opérations simples successives.
	count = tree->id_lex;

	switch (tree->type) {
		case A_LOOP:
			fprintf(out, BRAINFUCK_LOOP_BEGIN);
			ast_to_brainfuck(out, tree->son);
			fprintf(out, BRAINFUCK_LOOP_END);
			break;
		case A_INC:
			print_simple_inst(out, BRAINFUCK_INC, count, 0);
			break;
		case A_DEC:
			print_simple_inst(out, BRAINFUCK_DEC, count, 0);
			break;
		case A_LEFT:
			print_simple_inst(out, BRAINFUCK_LEFT, count, 0);
			break;
		case A_RIGHT:
			print_simple_inst(out, BRAINFUCK_RIGHT, count, 0);
			break;
		case A_PUT:
			print_simple_inst(out, BRAINFUCK_PUT, count, 0);
			break;
		case A_GET:
			print_simple_inst(out, BRAINFUCK_GET, count, 0);
			break;
		default:
			merror("ast_to_brainfuck() : 'tree->type' inconnu !");
	}

	ast_to_brainfuck(out, tree->little_brother);
}

/**
 * @brief Convertis l'arbre de syntaxe global en programme Brainfuck.
 * 
 * @param outpath Le fichier de sortie.
 */
static void decompile_to_brainfuck(char *outpath) {
	// Ouverture du fichier de sortie
	FILE *out = fopen(outpath, "w+");
	if (out == NULL)
		merror("decompile_ast_to_brainfuck() : Échec de l'ouverture du fichier"
			   "\"%s\"", outpath);
	
	// Décompilation
	ast_to_brainfuck(out, prog_tree);

	fclose(out);
}

/* -------------------------------------------------------------------------- */

/**
 * @brief Décompile le bytecode d'un programme Brainfuck.
 * 
 * @param inpath Le nom du fichier d'entrée.
 * @param outpath Le nom du fichier de sortie.
 */
void decompile(char *inpath, char *outpath) {
	// Analyse
	parse(inpath, &aain, aaparse, aalex_destroy);

	// Décompilation
	decompile_to_brainfuck(outpath);

	ast_free(prog_tree);
	prog_tree = NULL;
}

/* -------------------------------------------------------------------------- */
