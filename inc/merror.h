/**
 * @file merror.h
 * @author Mourtaza Akil (akilmourtaza.fr)
 * @brief Module implémentant l'affichage de messages d'erreur et d'avertisse
 * ments.
 * @date 2024-04-20
 * 
 * 
 */
#ifndef _MERROR_H_
#define _MERROR_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

/* -------------------------------------------------------------------------- */
/*                                   MACROS                                   */
/* -------------------------------------------------------------------------- */

/**
 * @def ERROR_PREFIX
 * @brief Préfixe à ajouter à tous les messages d'erreur.
 * 
 */
#define ERROR_PREFIX   "- Erreur -> "

/**
 * @def WARNING_PREFIX
 * @brief Préfixe à ajouter à tous les messages d'avertissement.
 * 
 */
#define WARNING_PREFIX "- Avertissement -> "

/* -------------------------------------------------------------------------- */
/*                          PROTOTYPES DES FONCTIONS                          */
/* -------------------------------------------------------------------------- */

/**
 * @brief Affiche un message d'erreur sur la sortie du module (Par défaut,
 * stderr) et arrête le programme en erreur.
 * 
 * @param format Le format du message.
 * @param ... Les arguments à placer dans le message.
 */
extern void merror(char *format, ...);

/* -------------------------------------------------------------------------- */

/**
 * @brief Affiche un message d'avertissement sur la sortie du module (Par
 * défaut, stderr).
 * 
 * @param format Le format du message.
 * @param ... Les arguments à placer dans le message.
 */
extern void mwarning(char *format, ...);

/* -------------------------------------------------------------------------- */

#endif
