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
 * 
 * @note Une pile qui ne contient tout simplement pas d'éléments, mais qui est
 * initialisée n'est pas considérée comme vide ici. 
 * @note Une pile est considérée comme vide :
 * @note - Si le contenu de la pile n'est pas initialisé (stack.s = NULL)
 * @note - Si les deux champs element_size et available_count sont nuls (=0), et
 * le champ top = -1.
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
Tstack *tstack_push(Tstack *stackp, void *elementp, size_t element_size) {
	// Pointeurs NULL
	if (stackp == NULL || elementp == NULL)
		merror("tstack_push() : 'stackp' ou 'elementp' est NULL !");

	// Pile vide
	if (tstack_is_empty(*stackp))
		merror("tstack_push() : La pile est vide !");
	
	// Vérification de la compatibilité de taille
	if (element_size != stackp->element_size)
		merror("tstack_push() : La taille de l'élément à ajouter est différente"
			   "de celle des éléments de la pile ! Élément[%d] vs Pile[%d]",
			   element_size, stackp->element_size);
	
	// Vérification de la place disponible
	if (stackp->available_count == 0)
		merror("tstack_push() : 'stack' est pleine !");
	
	stackp->top++;
	memcpy((char *)stackp->s + stackp->top * element_size, elementp,
		   element_size);
	stackp->available_count--;

	return stackp;
}

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
void *tstack_head(Tstack *stackp) {
	void *top_element;
	
	// Pointeur NULL
	if (stackp == NULL)
		merror("tstack_head() : 'stackp' est NULL !");

	// Pile vide
	if (tstack_is_empty(*stackp))
		merror("tstack_head() : La pile est vide !");
	
	// Pile sans aucun élément
	if (stackp->top == -1)
		merror("tstack_head() : La pile ne contient aucun élément !");

	top_element = malloc(stackp->element_size);
	if (top_element == NULL)
		merror("tstack_head() : Échec de l'allocation de mémoire à "
			   "'top_element' !");

	memcpy(top_element, (char *)stackp->s + stackp->top * stackp->element_size,
		   stackp->element_size);

	return top_element;
}

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
void *tstack_pop(Tstack *stackp, void *top_element) {
	void *tep = tstack_head(stackp);

	// Si 'top_element' est non NULL, l'utilisateur souhaite récupérer le
	// sommet.
	if (top_element != NULL) memcpy(top_element, tep, stackp->element_size);
	else free(tep);

	stackp->top--;

	return top_element;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief Libère la mémoire allouée à la pile.
 * 
 * @param stackp Le pointeur vers la pile dont la mémoire doit être libérée.
 * 
 * @note Un pointeur NULL provoquera une erreur.
 */
void tstack_free(Tstack *stackp) {
	Tstack empty = TSTACK_EMPTY;

	if (stackp == NULL)
		merror("tstack_free() : 'stackp' est NULL !");

	free(stackp->s);
	stackp->s = empty.s;
	stackp->top = empty.top;
	stackp->available_count = empty.available_count;
	stackp->element_size = empty.element_size;
}

/* -------------------------------------------------------------------------- */
