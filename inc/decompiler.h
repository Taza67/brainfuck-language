/**
 * @file decompiler.h
 * @author Mourtaza Akil (akilmourtaza.fr)
 * @brief Module implémentant la décompilation de bytecode ou d'arbres de
 * syntaxe abstraite de programmes Brainfuck obtenus grâce au module 'compiler'.
 * @date 2024-04-26
 * 
 * 
 */
#ifndef _DECOMPILER_H_
#define _DECOMPILER_H_

#include "brainfuck.h"
#include "parser.h"
#include "parser_ast.tab.h"

/* -------------------------------------------------------------------------- */
/*                                   MACROS                                   */
/* -------------------------------------------------------------------------- */

/**
 * @def BRAINFUCK_LOOP_BEGIN
 * @brief Chaîne de caractères représentant le début d'une boucle d'un programme
 * Brainfuck.
 * 
 */
#define BRAINFUCK_LOOP_BEGIN "["

/**
 * @brief Chaîne de caractères représentant la fin d'une boucle d'un programme
 * Brainfuck.
 * 
 */
#define BRAINFUCK_LOOP_END "]"

/**
 * @def BRAINFUCK_INC
 * @brief Chaîne de caractères représentant l'instruction d'incrémentation d'un
 * programme Brainfuck.
 * 
 */
#define BRAINFUCK_INC "+"

/**
 * @def BRAINFUCK_DEC
 * @brief Chaîne de caractères représentant l'instruction de décrémentation d'un
 * programme Brainfuck.
 * 
 */
#define BRAINFUCK_DEC "-"

/**
 * @def BRAINFUCK_LEFT
 * @brief Chaîne de caractères représentant l'instruction de déplacement vers la
 * gauche d'un programme Brainfuck.
 * 
 */
#define BRAINFUCK_LEFT "<"

/**
 * @def BRAINFUCK_RIGHT
 * @brief Chaîne de caractères représentant l'instruction de déplacement vers la
 * droite d'un programme Brainfuck.
 * 
 */
#define BRAINFUCK_RIGHT ">"

/**
 * @def BRAINFUCK_PUT
 * @brief Chaîne de caractères représentant l'instruction d'écriture d'un
 * programme Brainfuck.
 * 
 */
#define BRAINFUCK_PUT "."

/**
 * @def BRAINFUCK_GET
 * @brief Chaîne de caractères représentant l'instruction de lecture d'un
 * programme Brainfuck.
 * 
 */
#define BRAINFUCK_GET ","

/* -------------------------------------------------------------------------- */
/*                          PROTOTYPES DES FONCTIONS                          */
/* -------------------------------------------------------------------------- */

/**
 * @brief Convertis un arbre de syntaxe abstraite d'un programme Brainfuck en
 * programme Brainfuck.
 * 
 * @param out Le fichier de sortie.
 * @param tree L'arbre de syntaxe à convertir.
 */
extern void ast_to_brainfuck(FILE *out, Asttree tree);

/* -------------------------------------------------------------------------- */

/**
 * @brief Décompile le bytecode d'un programme Brainfuck.
 * 
 * @param inpath Le nom du fichier d'entrée.
 * @param outpath Le nom du fichier de sortie.
 */
extern void decompile(char *inpath, char *outpath);

/* -------------------------------------------------------------------------- */

#endif
