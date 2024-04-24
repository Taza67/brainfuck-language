%{
#include "brainfuck.h"
#include "parser_ast.tab.h"

#define  AA_USER_INIT \
    aalloc->first_line = aalloc->last_line = 1; \
    aalloc->first_column = aalloc->last_column = 1;

#define AA_USER_ACTION \
    aalloc->first_line = aalloc->last_line; \
    aalloc->first_column = aalloc->last_column; \
    for(int i = 0; aatext[i] != '\0'; i++) { \
        if(aatext[i] == '\n') { \
            aalloc->last_line++; \
            aalloc->last_column = 0; \
        } \
        else { \
            aalloc->last_column++; \
        } \
    }

#define YYSTYPE AASTYPE
#define YYLTYPE AALTYPE
#define AAERROR 9999

/* -------------------------------------------------------------------------- */
/*                                FONCTIONS YY                                */
/* -------------------------------------------------------------------------- */

void aaerror(AALTYPE *llocp, char *s) {
	merror("Syntaxe : à la ligne %d, colonnes [%d - %d] sur le lexème '%s' !"
		" [ %s ]", aalineno, llocp->first_column, llocp->last_column,
		aatext, s);
}

%}

/* -------------------------------------------------------------------------- */
/*                                 DIRECTIVES                                 */
/* -------------------------------------------------------------------------- */

%option prefix="aa"
%option yylineno
%option bison-bridge bison-locations
%option noyywrap

/* -------------------------------------------------------------------------- */
/*                                   CLASSES                                  */
/* -------------------------------------------------------------------------- */

SEP             [ \t\n\r]
DIGIT           [0-9]
NUMBER          [-+]?{DIGIT}*
TYPE            TYPE
LEX             LEX\[{NUMBER}\]
SYM             SYM\[{NUMBER}\]

ROOT            \[PROGRAM\]
LOOP            {TYPE}\[BOUCLE\]
PLUS            {TYPE}\[PLUS\]
MINUS           {TYPE}\[MOINS\]
LEFT            {TYPE}\[GAUCHE\]
RIGHT           {TYPE}\[DROITE\]
PUT             {TYPE}\[ÉCRITURE\]
GET             {TYPE}\[LECTURE\]

OBRA            \{
CBRA            \}

/* -------------------------------------------------------------------------- */
/*                                  TERMINAUX                                 */
/* -------------------------------------------------------------------------- */

%%

{ROOT}          { return ROOT; }
{OBRA}          { return OBRA; }
{CBRA}          { return CBRA; }
{LOOP}          { yylval->i = A_LOOP;  return NODE_TYPE; }
{PLUS}          { yylval->i = A_INC;   return NODE_TYPE; }
{MINUS}         { yylval->i = A_DEC;   return NODE_TYPE; }
{LEFT}          { yylval->i = A_LEFT;  return NODE_TYPE; }
{RIGHT}         { yylval->i = A_RIGHT; return NODE_TYPE; }
{PUT}           { yylval->i = A_PUT;   return NODE_TYPE; }
{GET}           { yylval->i = A_GET;   return NODE_TYPE; }
{LEX}           { sscanf(aatext, "LEX[%d]", &(yylval->i)); return LEX; }
{SYM}           { sscanf(aatext, "SYM[%d]", &(yylval->i)); return SYM; }

{SEP}           { /* */ }
.               { /* */ }

%%

/* -------------------------------------------------------------------------- */
