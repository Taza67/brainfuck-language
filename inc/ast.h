/**
 * @file ast.h
 * @author Mourtaza Akil (akilmourtaza.fr)
 * @brief Module implémentant la structure de données 'Arbre Abstrait de
 * Syntaxe' (AST).
 * @date 2024-04-20
 * 
 * 
 */
#ifndef _AST_H_
#define _AST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <stdbool.h>

#include "merror.h"

/* -------------------------------------------------------------------------- */
/*                                   MACROS                                   */
/* -------------------------------------------------------------------------- */

/**
 * @def AST_EMPTY
 * @brief Arbre vide.
 * 
 */
#define AST_EMPTY NULL

/* -------------------------------------------------------------------------- */
/*                                    TYPES                                   */
/* -------------------------------------------------------------------------- */

/**
 * @typedef Astdata_type
 * @enum Astdata_type
 * @brief Énumération des types de données d'un noeud d'arbre de syntaxe
 * abstraite.
 * 
 * @note Attention ! Il ne s'agit pas du type de noeud/arbre, mais bien du type
 * de ces données. Un noeud peut avoir deux types de données : données
 * constantes ou données d'un arbre.
 * 
 * @see Astnode
 */
typedef enum Astdata_type {
	ASTDATA_TYPE_CONST, ASTDATA_TYPE_TREE
} Astdata_type;

/* -------------------------------------------------------------------------- */

/**
 * @typedef Astnode
 * @struct Astnode
 * @brief Structure représentant un noeud d'arbre de syntaxe abstraite (AST).
 * 
 * Cette structure permet de représenter les éléments simples telles que les
 * constantes et les éléments complexes tels que les appels de fonctions ou les
 * structures de contrôles en utilisant des méthodes de chaînage laissées à
 * l'imagination de l'utilisateur.
 * 
 * @note Lorsqu'il s'agit d'un noeud de constante, la variable 'constant'
 * donnera la valeur de la constante lorsqu'il s'agira d'un entier ou d'un
 * caractère, et le numéro lexicographique lorsqu'il s'agira d'une chaîne de
 * caractère ou d'un flottant.
 * @note Le type du noeud est défini comme un entier pour plus de généralité.
 */
typedef struct Astnode {
   	int type;    ///< Type du noeud.
	union {
		int constant;    ///< Données constantes.
		struct {
			int id_lex;              		    ///< Numéro lexicographique.
			int id_symb;             		    ///< Numéro de symbole.
			struct Astnode *son;     		    ///< Noeud fils.
			struct Astnode *little_brother;     ///< Noeud petit-frère.
		};               ///< Données de type arbre.
	}; 			///< Données du noeud.
} Astnode;

/* -------------------------------------------------------------------------- */

/**
 * @typedef Asttree
 * @brief Pointeur vers une structure noeud d'arbre de syntaxe abstraite (AST). 
 * 
 * @see Astnode
 */
typedef Astnode *Asttree;

/* -------------------------------------------------------------------------- */
/*                          PROTOTYPES DES FONCTIONS                          */
/* -------------------------------------------------------------------------- */

/**
 * @brief Retourne un arbre vide.
 * 
 * @return Asttree Un Arbre vide.
 */
extern Asttree ast_empty();

/* -------------------------------------------------------------------------- */

/**
 * @brief Vérifie si un arbre est vide ou pas.
 * 
 * @param tree L'arbre à vérifier.
 * @return true Si l'arbre est vide.
 * @return false Si l'arbre n'est pas vide.
 */
extern bool ast_is_empty(Asttree tree);

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
 */
extern Asttree ast(Astdata_type data_type, ...);

/* -------------------------------------------------------------------------- */

#endif
