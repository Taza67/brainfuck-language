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
