/**
 * @file parser.c
 * @author Mourtaza Akil (akilmourtaza.fr)
 * @brief Module implémentant des fonctions liées à l'analyseur.
 * @date 2024-04-24
 * 
 * 
 */
#include "parser.h"

/* -------------------------------------------------------------------------- */
/*                                  FONCTIONS                                 */
/* -------------------------------------------------------------------------- */

/**
 * @brief Exécute un analyseur sur le fichier d'entrée fourni.
 * 
 * @param filepath Le nom du fichier à analyser.
 * @param inp Le pointeur vers l'entrée de l'analyseur.
 * @param parser La fonction d'analyse à exécuter.
 * @param lex_destroy La fonction de libération de mémoire à exécuter.
 * @return int Le résultat de l'analyse.
 */
int parse(char *filepath, FILE** inp, int (*parser)(void),
		  int (*lex_destroy)(void)) {
	int parse_ret;

	*inp = fopen(filepath, "r");
	if (*inp == NULL)
		merror("parse() : Échec de l'ouverture du fichier d'entrée \"%s\" !",
			   filepath);
	
	parse_ret = (*parser)();
	
	fclose(*inp);
	(*lex_destroy)();
	return parse_ret;
}

/* -------------------------------------------------------------------------- */
