/**
 * @file utilities.h
 * @author Mourtaza Akil (akilmourtaza.fr)
 * @brief Module implémentant des fonctions utilitaires pour le programme.
 * @date 2024-04-25
 * 
 * 
 */
#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#include "brainfuck.h"

/* -------------------------------------------------------------------------- */
/*                                   MACROS                                   */
/* -------------------------------------------------------------------------- */

/**
 * @def TAB
 * @brief Caractère de tabulation à imprimer lors de la compilation.
 * 
 */
#define TAB "\t"

/* -------------------------------------------------------------------------- */
/*                          PROTOTYPES DES FONCTIONS                          */
/* -------------------------------------------------------------------------- */

/**
 * @brief Imprime l'indentation sur la sortie donnée.
 * 
 * @param out Le fichier de sortie.
 * @param depth Le nombre d'indentations à imprimer.
 */
extern void print_indent(FILE *out, int depth);

/* -------------------------------------------------------------------------- */

/**
 * @brief Imprime une instruction simple autant de fois qu'il est nécessaire.
 * 
 * @param out Le fichier de sortie.
 * @param inst La chaîne de caractère représentant l'instruction.
 * @param count Le nombre de fois que l'instruction doit être répétée.
 * @param depth La profondeur (indentation) de l'instruction.
 */
extern void print_simple_inst(FILE *out, char *inst, int count, int depth);

/* -------------------------------------------------------------------------- */

/**
 * @brief Affiche la notice d'utilisation du programme.
 * 
 * @param program Le nom du programme.
 * @param format Le format du message pré-notice à afficher.
 * @param ... Les arguments à placer dans le format du message.
 * 
 * @see HELP_NOTICE_FORMAT
 */
extern void usage(char *program, char *format, ...);

/* -------------------------------------------------------------------------- */

#endif
