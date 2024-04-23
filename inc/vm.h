/**
 * @file vm.h
 * @author Mourtaza Akil (akilmourtaza.fr)
 * @brief Module implémentant la machine virtuelle de l'interpréteur
 * Brainfuck.
 * @date 2024-04-20
 * 
 * 
 */
#ifndef _VM_H_
#define _VM_H_

#include "brainfuck.h"

/* -------------------------------------------------------------------------- */
/*                                CONSTANTES                                  */
/* -------------------------------------------------------------------------- */

/**
 * @def DATA_STACK_SIZE
 * @brief Taille de la pile de données.
 * 
 */
#define DATA_STACK_SIZE 32000

/* -------------------------------------------------------------------------- */
/*                          PROTOTYPES DES FONCTIONS                          */
/* -------------------------------------------------------------------------- */

/**
 * @brief Exécute un programme Brainfuck représenté sous forme d'un arbre de
 * syntaxe abstraite (AST).
 * 
 * @param tree L'arbre de syntaxe abstraite (AST) à exécuter.
 */
extern void execute_program(Asttree tree);

/* -------------------------------------------------------------------------- */

#endif
