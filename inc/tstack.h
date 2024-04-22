/**
 * @file tstack.h
 * @author Mourtaza Akil (akilmourtaza.fr)
 * @brief Module implémentant la structure de données 'Pile' avec un tableau.
 * @date 2024-04-22
 * 
 * 
 */
#ifndef _TSTACK_H_
#define _TSTACK_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

#include "merror.h"

/* -------------------------------------------------------------------------- */
/*                                   MACROS                                   */
/* -------------------------------------------------------------------------- */

/**
 * @def TSTACK_EMPTY
 * @brief Pile vide.
 * 
 */
#define TSTACK_EMPTY (Tstack){ \
	.top=-1, .s=NULL, .element_size = 0, \
	.available_count = 0 \
}

/* -------------------------------------------------------------------------- */
/*                                    TYPES                                   */
/* -------------------------------------------------------------------------- */

/**
 * @typedef Tstack
 * @struct Tstack
 * @brief Structure représentant une pile implémentée avec un tableau.
 * 
 * Cette structure permet de représenter tout type de données (cf void *).
 * 
 * @note Il est de la responsabilité de l'utilisateur de vérifier la cohérence
 * des types de données qu'il utilise avec la pile.
 */
typedef struct Tstack {
	int top;				///< Indice du sommet de la pile.
	void *s;				///< Contenu de la pile.
	size_t element_size;	///< Taille d'un élément de la pile.
	size_t available_count; ///< Espace disponible dans la pile.
} Tstack;

/* -------------------------------------------------------------------------- */
/*                          PROTOTYPES DES FONCTIONS                          */
/* -------------------------------------------------------------------------- */

/**
 * @brief Retourne une pile vide.
 * 
 * @return Tstack Une pile vide.
 */
extern Tstack tstack_empty();

/* -------------------------------------------------------------------------- */

/**
 * @brief Vérifie si une pile est vide.
 * 
 * @param stack La pile à vérifier.
 * @return true Si la pile est vide.
 * @return false Si la pile n'est pas vide.
 */
extern bool tstack_is_empty(Tstack stack);

/* -------------------------------------------------------------------------- */

/**
 * @brief Retourne une pile de la taille spécifiée.
 * 
 * @param element_count Le taille de la pile en nombre d'éléments.
 * @param element_size La taille (en octets) d'un élément de la pile.
 * @return Tstack Une pile initialisée aux paramètres spécifiés.
 */
extern Tstack tstack(size_t element_count, size_t element_size);

/* -------------------------------------------------------------------------- */

#endif
