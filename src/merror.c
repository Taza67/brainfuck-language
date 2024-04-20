/**
 * @file merror.c
 * @author Mourtaza Akil (akilmourtaza.fr)
 * @brief Module implémentant l'affichage de messages d'erreur.
 * @date 2024-04-20
 * 
 * 
 */
#include "merror.h"

/* -------------------------------------------------------------------------- */
/*                             VARIABLES GLOBALES                             */
/* -------------------------------------------------------------------------- */

/**
 * @brief Sortie du module.
 * 
 * Les messages d'erreur seront imprimés sur cette sortie.
 * 
 * @note Par défaut, la sortie standard d'erreur y est affecté.
 */
FILE *merr;

/* -------------------------------------------------------------------------- */
/*                                  FONCTIONS                                 */
/* -------------------------------------------------------------------------- */

/**
 * @brief Affiche un message d'erreur sur la sortie du module (Par défaut,
 * stderr) et arrête le programme en erreur.
 * 
 * @param format Le format du message.
 * @param ... Les arguments à placer dans le message.
 */
void merror(char *format, ...) {
	va_list args;

	// Si la sortie du module n'est pas initialisée, elle est initialisée à
	// stderr par défaut.
	if (merr == NULL) merr = stderr;

	fprintf(merr, ERROR_PREFIX);
	va_start(args, format);
		vfprintf(merr, format, args);
	va_end(args);
	fflush(merr);

	exit(EXIT_FAILURE);
}

/* -------------------------------------------------------------------------- */
