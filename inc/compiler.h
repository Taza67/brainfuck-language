/**
 * @file compiler.h
 * @author Mourtaza Akil (akilmourtaza.fr)
 * @brief Module implémentant la compilation de programmes Brainfuck.
 * @date 2024-04-25
 * 
 * 
 */
#ifndef _COMPILER_H_
#define _COMPILER_H_

#include "brainfuck.h"
#include "parser.h"
#include "parser_ast.tab.h"
#include "parser_code.tab.h"

/* -------------------------------------------------------------------------- */
/*                                   MACROS                                   */
/* -------------------------------------------------------------------------- */

/**
 * @def CMODE_BOPTION
 * @brief Chaîne de caractères représentant l'option de compilation depuis un
 * programme Brainfuck écrit en bytecode.
 * 
 */
#define CMODE_BOPTION "-cb"

/**
 * @def CMODE_COPTION
 * @brief Chaîne de caractères représentant l'option de compilation depuis un
 * programme Brainfuck écrit en Brainfuck brut.
 * 
 */
#define CMODE_COPTION "-c"

/**
 * @def CMODE_BC_ARG
 * @brief Chaîne de caractères représentant l'argument d'option de compilation
 * vers du bytecode.
 * 
 */
#define CMODE_BC_ARG "bytecode"

/**
 * @def CMODE_PC_ARG
 * @brief Chaîne de caractères représentant l'argument d'option de compilation
 * vers du python.
 * 
 */
#define CMODE_PC_ARG "python"

/**
 * @def CMODE_CC_ARG
 * @brief Chaîne de caractères représentant l'argument d'option de compilation
 * vers du C.
 * 
 */
#define CMODE_CC_ARG "c"

/* --------------------------------- Python --------------------------------- */

/**
 * @def PYTHON_HEADER
 * @brief Chaîne de caractères représentant l'entête d'un programme Brainfuck
 * convertis en programme python.
 * 
 */
#define PYTHON_HEADER \
	"#!/usr/bin/env python3\n\n" \
	"STACK_LENGTH = 32000\n\n" \
	"def main():\n" \
	"\tstack = [0] * STACK_LENGTH\n" \
	"\ti = 0\n"

/**
 * @def PYTHON_FOOTER
 * @brief Chaîne de caractères représentant le pied d'un programme Brainfuck
 * convertis en programme python.
 * 
 */
#define PYTHON_FOOTER \
	"\n" \
	"main()\n"

/**
 * @def PYTHON_LOOP
 * @brief Chaîne de caractères représentant une boucle d'un programme Brainfuck
 * convertis en programme python.
 * 
 */
#define PYTHON_LOOP \
	"while (stack[i]):\n"

/**
 * @def PYTHON_INC
 * @brief Chaîne de caractères représentant l'instruction d'incrémentation d'un
 * programme Brainfuck convertis en programme python.
 * 
 */
#define PYTHON_INC \
	"stack[i] += 1\n"

/**
 * @def PYTHON_DEC
 * @brief Chaîne de caractères représentant l'instruction de décrémentation d'un
 * programme Brainfuck convertis en programme python.
 * 
 */
#define PYTHON_DEC \
	"stack[i] -= 1\n"

/**
 * @def PYTHON_LEFT
 * @brief Chaîne de caractères représentant l'instruction de déplacement vers la
 * gauche d'un programme Brainfuck convertis en programme python.
 * 
 */
#define PYTHON_LEFT \
	"i -= 1\n"

/**
 * @def PYTHON_RIGHT
 * @brief Chaîne de caractères représentant l'instruction de déplacement vers la
 * droite d'un programme Brainfuck convertis en programme python.
 * 
 */
#define PYTHON_RIGHT \
	"i += 1\n"

/**
 * @def PYTHON_PUT
 * @brief Chaîne de caractères représentant l'instruction d'écriture d'un
 * programme Brainfuck convertis en programme python.
 * 
 */
#define PYTHON_PUT \
	"print(chr(stack[i]), end=\"\")\n"

/**
 * @def PYTHON_GET
 * @brief Chaîne de caractères représentant l'instruction de lecture d'un
 * programme Brainfuck convertis en programme python.
 * 
 */
#define PYTHON_GET \
	"stack[i] = input(1)\n"

/* -------------------------------------------------------------------------- */
/*                                 CONSTANTES                                 */
/* -------------------------------------------------------------------------- */

/**
 * @enum COMPILER_MODES
 * @brief Énumération des différents modes de compilation.
 * 
 */
enum COMPILER_MODES {
	CMODE_CBC,	///< Compilation de Brainfuck brut vers du Brainfuck bytecode.
	CMODE_CPC,	///< Compilation de Brainfuck brut vers du python.
	CMODE_BPC,	///< Compilation de Brainfuck bytecode vers du Python.
	CMODE_CCC,	///< Compilation de Brainfuck brut vers du C.
	CMODE_BCC	///< Compilation de Brainfuck bytecode vers du C.
};

/* -------------------------------------------------------------------------- */
/*                          PROTOTYPES DES FONCTIONS                          */
/* -------------------------------------------------------------------------- */

/**
 * @brief Convertis un arbre de syntaxe abstraite d'un programme Brainfuck en
 * un programme Python.
 * 
 * @param out Le fichier de sortie.
 * @param tree L'arbre de syntaxe à convertir.
 */
extern void ast_to_python(FILE *out, Asttree tree);

/* -------------------------------------------------------------------------- */

/**
 * @brief Compile un programme Brainfuck.
 * 
 * @param argc Le nombre d'arguments passés au programme principal.
 * @param argv Les arguments passés au programme principal.
 * 
 * @note Un nombre d'arguments incorrect provoquera une erreur.
 */
extern void compile(int argc, char *argv[]);

/* -------------------------------------------------------------------------- */

#endif
