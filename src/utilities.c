/**
 * @file utilities.c
 * @author Mourtaza Akil (akilmourtaza.fr)
 * @brief Module implémentant des fonctions utilitaires pour le programme.
 * @date 2024-04-25
 * 
 * 
 */
#include "utilities.h"

/* -------------------------------------------------------------------------- */
/*                                  FONCTION                                  */
/* -------------------------------------------------------------------------- */

/**
 * @brief Imprime l'indentation sur la sortie donnée.
 * 
 * @param out Le fichier de sortie.
 * @param depth Le nombre d'indentations à imprimer.
 */
void print_indent(FILE *out, int depth) {
	for (int i = 0; i < depth; i++) fprintf(out, TAB);
}

/* -------------------------------------------------------------------------- */

/**
 * @brief Imprime une instruction simple autant de fois qu'il est nécessaire.
 * 
 * @param out Le fichier de sortie.
 * @param inst La chaîne de caractère représentant l'instruction.
 * @param count Le nombre de fois que l'instruction doit être répétée.
 * @param depth La profondeur (indentation) de l'instruction.
 */
void print_simple_inst(FILE *out, char *inst, int count, int depth) {
	for (int  i = 0; i < count; i++) {
		print_indent(out, depth);
		fprintf(out, "%s", inst);
	}
}

/* ---------------------------------- Main ---------------------------------- */

/**
 * @brief Affiche la notice d'utilisation du programme.
 * 
 * @param program Le nom du programme.
 * @param format Le format du message pré-notice à afficher.
 * @param ... Les arguments à placer dans le format du message.
 * 
 * @see HELP_NOTICE_FORMAT
 */
void usage(char *program, char *format, ...) {
    va_list args;

	// Message
    va_start(args, format);
		if (strlen(format) != 0) {
			fprintf(stderr, "- Message -> ");
			vfprintf(stderr, format, args);

			if (format[strlen(format)] != '\n')
				fprintf(stderr, "\n");
		}
    va_end(args);

	// Notice
    printf(HELP_NOTICE_FORMAT, program);

    exit(EXIT_FAILURE);
}

/* -------------------------------------------------------------------------- */
