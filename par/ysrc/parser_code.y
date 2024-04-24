%{
#include "brainfuck.h"
#include "parser_code.tab.h"

extern int cclex(CCSTYPE *lvalp, CCLTYPE *llocp);
extern void ccerror(CCLTYPE *llocp, char *s);

extern Asttree prog_tree;
%}

/* -------------------------------------------------------------------------- */
/*                                 DIRECTIVES                                 */
/* -------------------------------------------------------------------------- */

%union {
	Asttree t;
	int     i;
	struct {
		int code, count;
	} o;
}

%define		api.prefix	{cc}
%define 	api.pure 	full
%locations

/* -------------------------------------------------------------------------- */
/*                              (NON - )TERMINAUX                             */
/* -------------------------------------------------------------------------- */

%right 		'+' '-' '<' '>' '.' ','

%type<t>	instructions instruction
%type<o>	simple_instructions
%type<i>	incrementations decrementations leftmoves rightmoves puts gets

/* -------------------------------------------------------------------------- */
/*                                  GRAMMAIRE                                 */
/* -------------------------------------------------------------------------- */

%%

program :
		instructions
		{
			prog_tree = $1;
		}
	;

instructions :
		instruction instructions
		{
			// $1 sera égal à NULL s'il s'agit d'une boucle vide.
			$$ = ($1 != NULL) ? ast_add_little_brother($1, $2) : $2;
		}
	| 	instruction
		{
			$$ = $1;
		}
	;

instruction :
		simple_instructions
		{
			$$ = ast(ASTDATA_TYPE_TREE, $1.code, $1.count, -1, ast_empty(),
					 ast_empty());
		}
	| 	'[' instructions ']'
		{
			$$ = ast(ASTDATA_TYPE_TREE, A_LOOP, -1, -1, $2, ast_empty());
		}
	|	'[' /* Boucle vide */ ']'
		{
			$$ = NULL;
		}
	;

/* --------------------------- Instuctions simples -------------------------- */

simple_instructions :
		incrementations
		{
			$$.code = A_INC;
			$$.count = $1;
		}
	|	decrementations
		{
			$$.code = A_DEC;
			$$.count = $1;
		}
	|	rightmoves
		{
			$$.code = A_RIGHT;
			$$.count = $1;
		}
	|	leftmoves
		{
			$$.code = A_LEFT;
			$$.count = $1;
		}
	|	puts
		{
			$$.code = A_PUT;
			$$.count = $1;
		}
	|	gets
		{
			$$.code = A_GET;
			$$.count = $1;
		}
	;

/* ----------------------------- Incrémentation ----------------------------- */

incrementations :
		'+' incrementations
		{
			$$ = 1 + $2;
		}
	|	'+'
		{
			$$ = 1;
		}
	;

/* ----------------------------- Décrémentation ----------------------------- */

decrementations :
		'-' decrementations
		{
			$$ = 1 + $2;
		}
	|	'-'
		{
			$$ = 1;
		}
	;

/* -------------------------- Déplacement à droite -------------------------- */

rightmoves :
		'>' rightmoves
		{
			$$ = 1 + $2;
		}
	|	'>'
		{
			$$ = 1;
		}
	;

/* -------------------------- Déplacement à gauche -------------------------- */

leftmoves :
		'<' leftmoves
		{
			$$ = 1 + $2;
		}
	|	'<'
		{
			$$ = 1;
		}
	;

/* -------------------------------- Écriture -------------------------------- */

puts :
		'.' puts
		{
			$$ = 1 + $2;
		}
	|	'.'
		{
			$$ = 1;
		}
	;

/* --------------------------------- Lecture -------------------------------- */

gets :
		',' gets
		{
			$$ = 1 + $2;
		}
	|	','
		{
			$$ = 1;
		}
	;

%%

/* -------------------------------------------------------------------------- */
