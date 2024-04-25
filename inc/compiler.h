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
