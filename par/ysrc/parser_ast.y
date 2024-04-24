%{
#include "brainfuck.h"	
#include "parser_ast.tab.h"

extern int aalex(AASTYPE *lvalp, AALTYPE *llocp);
extern void aaerror(AALTYPE *llocp, char *s);

extern Asttree prog_tree;
%}

/* -------------------------------------------------------------------------- */
/*                                 DIRECTIVES                                 */
/* -------------------------------------------------------------------------- */

%union {
	Asttree t;
	int		i;
}

%define		api.prefix		{aa}
%define		api.pure 	full
%locations

/* -------------------------------------------------------------------------- */
/*                              (NON - )TERMINAUX                             */
/* -------------------------------------------------------------------------- */

%token		ROOT OBRA CBRA
%token<i>	NODE_TYPE LEX SYM

%type<t>	sons son node

/* -------------------------------------------------------------------------- */
/*                                  GRAMMAIRE                                 */
/* -------------------------------------------------------------------------- */

%%

tree :
		ROOT OBRA sons CBRA
		{
			prog_tree = $3;
		}
	;

sons :
		son sons
		{
			$$ = ast_add_little_brother($1, $2);
		}
	|	son
		{
			$$ = $1;
		}
	;

son	:
		node OBRA sons CBRA
		{
			$$ = ast_add_son($1, $3);
		}
	|	node
		{
			$$ = $1;
		}
	;

node :
		NODE_TYPE LEX SYM
		{
			$$ = ast(ASTDATA_TYPE_TREE, $1, $2, $3, ast_empty(), ast_empty());
		}
	;

%%

/* -------------------------------------------------------------------------- */
