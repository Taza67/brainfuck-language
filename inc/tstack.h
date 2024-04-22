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
 * des types de données qu'il utilise avec la pile. Par exemple, l'utilisateur
 * ne pourra pas mettre des éléments de type 'Long' dans une pile initialisée
 * avec des éléments de type 'int'. Il est également déconseillé de modifier les
 * valeurs des champs de la pile sans passer par une des fonctions du module.
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
 * 
 * @note Une pile qui ne contient tout simplement pas d'éléments, mais qui est
 * initialisée n'est pas considérée comme vide ici. 
 * @note Une pile est considérée comme vide :
 * @note - Si le contenu de la pile n'est pas initialisé (stack.s = NULL)
 * @note - Si les deux champs element_size et available_count sont nuls (=0), et
 * le champ top = -1.
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

/**
 * @brief Empile un élément dans la pile.
 * 
 * @param stackp Le pointeur vers la pile qui reçoit l'élément.
 * @param elementp Le pointeur vers l'élément à empiler.
 * @param element_size La taille (en octets) de l'élément à empiler.
 * @return Tstack * Le pointeur vers la pile modifiée.
 * 
 * @note Les éléments suivants provoqueront une erreur :
 * @note - Pointeurs NULL.
 * @note - Pile vide (non initialisée).
 * @note - Taille de l'élément différente de celle des éléments de la pile.
 * @note - Pile pleine.
 * 
 * @see tstack_is_empty
 */
extern Tstack *tstack_push(Tstack *stackp, void *elementp, size_t element_size);

/* -------------------------------------------------------------------------- */

/**
 * @brief Retourne le sommet de la pile.
 * 
 * @param stackp Le pointeur vers la pile dont le sommet doit être renvoyé.
 * @return void* Un pointeur vers le sommet de la pile.
 * 
 * @note Le type retourné étant (void *), il revient à l'utilisateur de
 * convertir le contenu au bon type.
 * @note Il est également de la responsabilité de l'utilisateur de libérer la
 * mémoire allouée à l'élément retourné.
 * @note Les éléments suivants provoqueront une erreur :
 * @note - Pointeur NULL.
 * @note - Pile vide (non initialisée).
 * @note - Pile ne contient aucun élément.
 * 
 * @see tstack_is_empty
 */
extern void *tstack_head(Tstack *stackp);

/* -------------------------------------------------------------------------- */

/**
 * @brief Dépile et retourne le sommet de la pile
 * 
 * @param stackp Le pointeur vers la pile dont le sommet doit être dépilé.
 * @param top_element Le pointeur de l'emplacement qui doit récupérer le sommet
 * de la pile.
 * @return void* Le pointeur qui récupère le sommet.
 * 
 * @note Si 'top_element' == NULL alors le sommet ne sera pas recopié et donc
 * libéré automatiquement.
 * 
 * @see tstack_head
 */
void *tstack_pop(Tstack *stackp, void *top_element);

/* -------------------------------------------------------------------------- */

/**
 * @brief Libère la mémoire allouée à la pile.
 * 
 * @param stackp Le pointeur vers la pile dont la mémoire doit être libérée.
 * 
 * @note Un pointeur NULL provoquera une erreur.
 */
void tstack_free(Tstack *stackp);

/* -------------------------------------------------------------------------- */

#endif
