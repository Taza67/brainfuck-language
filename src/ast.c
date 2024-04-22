/** 
 * @file ast.c
 * @author Mourtaza Akil (akilmourtaza.fr)
 * @brief Module implémentant la structure de données 'Arbre Abstrait de
 * Syntaxe' (AST).
 * @date 2024-04-20
 * 
 * 
 */
#include "ast.h"

/* -------------------------------------------------------------------------- */
/*                                  FONCTIONS                                 */
/* -------------------------------------------------------------------------- */

/**
 * @brief Retourne un arbre vide.
 * 
 * @return Asttree Un Arbre vide.
 */
Asttree ast_empty() {
	return AST_EMPTY;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief Vérifie si un arbre est vide ou pas.
 * 
 * @param tree L'arbre à vérifier.
 * @return true Si l'arbre est vide.
 * @return false Si l'arbre n'est pas vide.
 */
bool ast_is_empty(Asttree tree) {
	return tree == ast_empty();
}

/* -------------------------------------------------------------------------- */

/**
 * @brief Retourne un arbre initialisé avec les données.
 * 
 * @param data_type Le type de données.
 * @param ... Les données à affecter aux données de l'arbre.
 * @return Asttree Un arbre initialisé avec les données.
 * 
 * @note Un type de données inconnu provoquera une erreur.
 * @note Il s'agit d'une fonction variadique. Les appels de fonctions dépendront
 * du type de données à affecter.
 * @note - Données de type constante :
 * 	   ast(ASTDATA_TYPE_CONST, type: <int>, constant: <int>)
 * @note - Données de type arbre :
 *     ast(ASTDATA_TYPE_TREE, type: <int>, id_lex: <int>, id_symb: <int>,
 *         son: Asttree, little_brother: Asttree)
 */
Asttree ast(Astdata_type data_type, ...) {
	va_list args;
	Asttree tree;

	// Création de l'arbre
	tree = (Asttree)malloc(sizeof(Astnode));
	if (tree == NULL)
		merror("ast() : Échec de l'allocation de mémoire à 'tree' ! [%s]",
			   strerror(errno));

	// Initialisation de l'arbre en fonction du type de données à recevoir.
	va_start(args, data_type);
		tree->type = va_arg(args, int);
		
		switch (data_type) {
			case ASTDATA_TYPE_CONST:
				tree->constant = va_arg(args, int);
				break;
			case ASTDATA_TYPE_TREE:
				tree->id_lex = va_arg(args, int);
				tree->id_symb = va_arg(args, int);
				tree->son = va_arg(args, Asttree);
				tree->little_brother = va_arg(args, Asttree);
				break;
			default:
				merror("ast() : 'data_type' ne correspond pas à aucune"
					   "constante de l'énumération Astdata_type !");
		}
	va_end(args);

	return tree;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief Donne un fils à un arbre et retourne l'arbre père.
 * 
 * @param tree L'arbre qui reçoit un fils.
 * @param son L'arbre fils.
 * @return Asttree L'arbre père.
 * 
 * @note L'arbre ne peut pas recevoir de fils, s'il est déjà un arbre père, si
 * il a déjà un fils.
 * @note Les éléments suivants provoqueront une erreur :
 * @note - Arbre (père) vide.
 * @note - Arbre (père) a déjà un fils.
 */
Asttree ast_add_son(Asttree tree, Asttree son) {
	if (ast_is_empty(tree))
		merror("ast_add_son() : 'tree' est vide !");

	if (!ast_is_empty(tree->son))
		merror("ast_add_son() : 'tree' a déjà un fils !");

	tree->son = son;

	return tree;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief Donne un petit-frère à un arbre et retourne l'arbre grand-frère.
 * 
 * @param tree L'arbre qui reçoit un frère.
 * @param little_brother L'arbre petit-frère.
 * @return Asttree L'arbre grand-frère.
 * 
 * @note L'arbre ne peut pas recevoir de petit-frère s'il est déjà un arbre
 * grand-frère, s'il a déjà un petit-frère.
 * @note Les éléments suivants provoqueront une erreur :
 * @note - Arbre (grand-frère) vide.
 * @note - Arbre (grand-frère) a déjà un petit-frère.
 */
Asttree ast_add_little_brother(Asttree tree, Asttree little_brother) {
	if (ast_is_empty(tree))
		merror("ast_add_little_brother() : 'tree' est vide !");
	
	if (!ast_is_empty(tree->little_brother))
		merror("ast_add_little_brother() : 'tree' a déjà un petit-frère !");
	
	tree->little_brother = little_brother;

	return tree;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief Libère la mémoire allouée à l'intégralité de l'arbre (racine, fils,
 * petit-frères).
 * 
 * @param tree L'arbre dont la mémoire doit être libérée.
 * 
 * @note Attention ! Il ne faut surtout pas qu'il y ait de cycle dans l'arbre.
 */
void ast_free(Asttree tree) {
	if (tree == NULL) return;
	
	ast_free(tree->son);
	ast_free(tree->little_brother);
	free(tree);
}

/* -------------------------------------------------------------------------- */

/**
 * @brief Fonction auxilaire à ast_print.
 * 
 * Cette fonction permet d'imprimer un arbre AST sous un format lisible pour
 * l'oeil humain.
 * 
 * @param tree L'arbre à imprimer.
 * @param types Les chaînes de caractères associées aux types d'arbres
 * possibles.
 * @param depth La profondeur de l'arbre.
 * @param out La sortie sur laquelle imprimer l'arbre (Par défaut, stdout).
 * 
 * @see ast_print
 */
static void ast_print_aux(Asttree tree, char *types[], int depth, FILE *out) {
	if (tree == NULL) return;
	if (out == NULL) out = stdout;

	// Tabulation
	for (int i = 0; i < depth; i++) fprintf(out, AST_TAB_STR);

	// Noeud
	fprintf(out, AST_TYPE_FORMAT AST_LEX_FORMAT AST_SYM_FORMAT,
			types[tree->type], tree->id_lex, tree->id_symb);
	
	// Fils
	if (tree->son != NULL) {
		fprintf(out, " " AST_OBRA_STR "\n");
		ast_print_aux(tree->son, types, depth + 1, out);
		
		for (int i = 0; i < depth; i++) fprintf(out, AST_TAB_STR);
		fprintf(out, AST_CBRA_STR "\n");
	} else {
		fprintf(out, "\n");
	}

	// Frère
	ast_print_aux(tree->little_brother, types, depth, out);
}

/**
 * @brief Imprime un arbre sur la sortie spécifiée sous un format lisible pour
 * l'oeil humain.
 * 
 * @param tree L'arbre à imprimer.
 * @param types Les chaînes de caractères associées aux types d'arbres
 * possibles.
 * @param out La sortie sur laquelle imprimer l'arbre (Par défaut, stdout).
 */
void ast_print(Asttree tree, char *types[], FILE *out) {
	fprintf(out, AST_ROOT_STR " " AST_OBRA_STR "\n");
	ast_print_aux(tree, types, 1, out);
	fprintf(out, AST_CBRA_STR "\n");
}

/* -------------------------------------------------------------------------- */
