%{
#include "brainfuck.h"
#include "parser_code.tab.h"

#define  CC_USER_INIT \
    cclloc->first_line = cclloc->last_line = 1; \
    cclloc->first_column = cclloc->last_column = 1;

#define CC_USER_ACTION \
    cclloc->first_line = cclloc->last_line; \
    cclloc->first_column = cclloc->last_column; \
    for(int i = 0; cctext[i] != '\0'; i++) { \
        if(cctext[i] == '\n') { \
            cclloc->last_line++; \
            cclloc->last_column = 0; \
        } \
        else { \
            cclloc->last_column++; \
        } \
    }

#define YYSTYPE CCSTYPE
#define YYLTYPE CCLTYPE

/* -------------------------------------------------------------------------- */
/*                             GESTION DES ERREURS                            */
/* -------------------------------------------------------------------------- */

/**
 * @brief Gère les erreur de parsing rapportées par Bison pour l'analyseur de
 * code.
 * 
 * Cette fonction est responsable de l'affichage des messages d'erreur.
 * 
 * @param llocp La structure qui contient les informations de localisation de la
 * tête de lecture.
 */
void ccerror(CCLTYPE *llocp, char *s) {
	merror("Syntaxe : à la ligne %d, colonnes [%d - %d] sur le lexème '%s' !"
		   " [ %s ]", cclineno, llocp->first_column, llocp->last_column,
		   cctext, s);
}

int ccwrap(void) {
    return 1;  // Return 1 to signify no further files to process
}

%}

/* -------------------------------------------------------------------------- */
/*                                 DIRECTIVES                                 */
/* -------------------------------------------------------------------------- */

%option prefix="cc"
%option yylineno
%option bison-bridge bison-locations

/* -------------------------------------------------------------------------- */
/*                                   CLASSES                                  */
/* -------------------------------------------------------------------------- */

INSTRUCTION 			[\+\-\.\,\>\<\[\]]

/* -------------------------------------------------------------------------- */
/*                                  TERMINAUX                                 */
/* -------------------------------------------------------------------------- */

%%

{INSTRUCTION}			{ return *cctext; }
[^{INSTRUCTION}]       	{ /* */ }
.						;

%%

/* -------------------------------------------------------------------------- */
