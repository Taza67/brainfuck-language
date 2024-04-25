/**
 * @file brainfuck.h
 * @author Mourtaza Akil (akilmourtaza.fr)
 * @brief En-tête de l'interpréteur Brainfuck.
 * @date 2024-04-20
 * 
 * 
 */
#ifndef _BRAINFUCK_H_
#define _BRAINFUCK_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>

#include "merror.h"
#include "ast.h"
#include "tstack.h"

/* -------------------------------------------------------------------------- */
/*                                   MACROS                                   */
/* -------------------------------------------------------------------------- */

/**
 * @def HELP_NOTICE_FORMAT
 * @brief Notice d'utilisation du programme.
 * 
 */
#define HELP_NOTICE_FORMAT \
		"\n" \
	"- Interpréteur du langage Brainfuck" \
	"\n" \
	"- Usage: %s [<option> [<sous-option>]] [<entree>] [<sortie>]\n" \
	"\n" \
	"  -    [<option>]                   :    -h    affiche la notice d'utilisation\n" \
	"                                         -c    compile le programme en entrée\n" \
	"                                         -cb   compile le bytecode en entrée\n" \
	"                                         -i    interprète le programme en entrée\n" \
	"                                         -ib   exécute le Bytecode en entrée\n" \
	"                                         -d    décompile le bytecode en entrée\n" \
	"\n" \
	"  +    -    [<sous-option>]         :    python    compile en Python\n" \
	"                                         c         compile en C\n" \
	"                                         + optionnel pour l'option {-c}\n" \
	"                                         + nécessaire pour l'option {-cb}\n" \
	"                                         bytecode  compile en C\n" \
	"                                         + optionnel pour l'option {-c}\n" \
	"\n" \
	"  -    [<entree>]                   :    code source en langage Brainfuck\n" \
	"                                         + nécessaire pour l'option {-c}\n" \
	"                                         + nécessaire pour l'option {-i}\n" \
	"                                         bytecode\n" \
	"                                         + nécessaire pour l'option {-cb}\n" \
	"                                         + nécessaire pour l'option {-ib}\n" \
	"                                         + nécessaire pour l'option {-d}\n" \
	"\n" \
	"  -    [<sortie>]                   :    nom du fichier de sortie\n" \
	"                                         + nécessaire pour l'option {-c}\n" \
	"                                         + nécessaire pour l'option {-cb}\n" \
	"                                         + nécessaire pour l'option {-d}\n" \
	"\n" \
	"  -    default                      :    affiche la notice d'utilisation\n" \
	"\n"

/**
 * @def EMPTY_BUFFER
 * @brief Fonction macro permettant de vider le buffer.
 * 
 */
#define EMPTY_BUFFER() \
	char _c = 0; while ((_c = getchar()) != '\n' && _c != EOF) \

/**
 * @def AST_TYPES_STRINGS
 * @brief Ensemble des chaînes de caractères associées à chaque type d'arbre
 * possible pour un arbre de syntaxe abstraite (AST) du langage Brainfuck.
 * 
 * @note Les chaînes doivent OBLIGATOIREMENT être dans le même ordre que l'énu-
 * mération qui définit les codes des types d'arbres.
 * 
 * @see AST_TYPES 
 */
#define AST_TYPES_STRINGS { \
	"PLUS", "MOINS", "DROITE", "GAUCHE", \
	"ÉCRITURE", "LECTURE", "BOUCLE" \
}



/* -------------------------------------------------------------------------- */
/*                                CONSTANTES                                  */
/* -------------------------------------------------------------------------- */

/**
 * @enum EXEC_MODES
 * @brief Énumération des modes d'exécution du programme.
 * 
 */
enum EXEC_MODES {
	MODE_HELP     ,  ///< Affichage de la notice d'utilisation.
	MODE_INTERPRET,  ///< Interprétation d'un programme Brainfuck.
	MODE_COMPILE  ,  ///< Compilation d'un programme Brainfuck.
	MODE_DECOMPILE,  ///< Décompilation d'un bytecode Brainfuck.
	MODE_VM,		 ///< Exécution d'un programme Brainfuck en Bytecode.
};

/* -------------------------------------------------------------------------- */

/**
 * @enum AST_TYPES
 * @brief Énumération des types d'arbres associés aux instructions du langage
 * Brainfuck.
 * 
 */
enum AST_TYPES {
	A_INC  ,  ///< Incrémentation de la case de données pointée.
	A_DEC  ,  ///< Décrémentation de la case de données pointée.
	A_RIGHT,  ///< Déplacement du pointeur de données à droite.
	A_LEFT ,  ///< Déplacement du pointeur de données à gauche.
	A_PUT  ,  ///< Affichage de la valeur de la donnée pointée.
	A_GET  ,  ///< Récupération d'une entrée.
	A_LOOP    ///< Boucle.
};

/* -------------------------------------------------------------------------- */

#endif
