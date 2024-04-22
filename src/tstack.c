/**
 * @file tstack.c
 * @author Mourtaza Akil (akilmourtaza.fr)
 * @brief Module implémentant la structure de données 'Pile' avec un tableau.
 * @date 2024-04-22
 * 
 * 
 */
#include "tstack.h"

/* -------------------------------------------------------------------------- */
/*                                  FONCTIONS                                 */
/* -------------------------------------------------------------------------- */

/**
 * @brief Retourne une pile vide.
 * 
 * @return Tstack Une pile vide.
 */
Tstack tstack_empty() {
	return TSTACK_EMPTY;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief Vérifie si une pile est vide.
 * 
 * @param stack La pile à vérifier.
 * @return true Si la pile est vide.
 * @return false Si la pile n'est pas vide.
 */
bool tstack_is_empty(Tstack stack) {
	Tstack empty = tstack_empty();

	return empty.s == stack.s || (empty.top == stack.top &&
		   empty.element_size == stack.element_size &&
		   empty.available_count == stack.available_count);
}

/* -------------------------------------------------------------------------- */

/**
 * @brief Retourne une pile de la taille spécifiée.
 * 
 * @param element_count Le taille de la pile en nombre d'éléments.
 * @param element_size La taille (en octets) d'un élément de la pile.
 * @return Tstack Une pile initialisée aux paramètres spécifiés.
 */
Tstack tstack(size_t element_count, size_t element_size) {
	Tstack stack;

	stack.s = (void *)calloc(element_count, element_size);
	if (stack.s == NULL)
		merror("ast() : Échec de l'allocation de mémoire à 's' ! [%s]",
			   strerror(errno));
	
	stack.top = -1;
	stack.element_size = element_size;
	stack.available_count = element_count;
	
	return stack;
}

/* -------------------------------------------------------------------------- */
