/**
 * @file parser.h
 * @author Mourtaza Akil (akilmourtaza.fr)
 * @brief Module implémentant des fonctions liées à l'analyseur.
 * @version 0.1
 * @date 2024-04-24
 * 
 * 
 */
#ifndef _PARSER_H_
#define _PARSER_H_

#include "brainfuck.h"

/* -------------------------------------------------------------------------- */
/*                          PROTOTYPES DES FONCTIONS                          */
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
extern int parse(char *filepath, FILE** inp, int (*parser)(void),
		  int (*lex_destroy)(void));

/* -------------------------------------------------------------------------- */

#endif
