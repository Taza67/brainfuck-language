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

/**
 * @def AST_ROOT_STR
 * @brief Racine d'un AST pour son impression.
 * 
 */
#define AST_ROOT_STR	"[PROGRAM]"

/**
 * @def AST_TAB_STR
 * @brief Caractère de tabulation dans l'impression d'un AST.
 * 
 */
#define AST_TAB_STR 	"\t"

/**
 * @def AST_OBRA_STR
 * @brief Caractère de début d'un ensemble de fils.
 * 
 * @see AST_CBRA_STR
 */
#define AST_OBRA_STR	"{"

/**
 * @def AST_CBRA_STR
 * @brief Caractère de fermeture d'un ensemble de fils.
 * 
 * @see AST_OBRA_STR
 */
#define AST_CBRA_STR	"}"

/**
 * @def AST_TYPE_FORMAT
 * @brief Format d'impression du type d'un arbre.
 * 
 */
#define AST_TYPE_FORMAT	"TYPE[%s]"

/**
 * @def AST_LEX_FORMAT
 * @brief Format d'impression du numéro lexicographique d'un arbre.
 * 
 */
#define AST_LEX_FORMAT 	"LEX[%d]"

/**
 * @def AST_SYM_FORMAT
 * @brief Format d'impression du numéro de symbole d'un arbre.
 * 
 */
#define AST_SYM_FORMAT 	"SYM[%d]"


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
 * @note - Données de type constante :
 * 	   ast(ASTDATA_TYPE_CONST, type: <int>, constant: <int>)
 * @note - Données de type arbre :
 *     ast(ASTDATA_TYPE_TREE, type: <int>, id_lex: <int>, id_symb: <int>,
 *         son: Asttree, little_brother: Asttree)
 */
extern Asttree ast(Astdata_type data_type, ...);

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
extern Asttree ast_add_son(Asttree tree, Asttree son);

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
extern Asttree ast_add_little_brother(Asttree tree, Asttree little_brother);

/* -------------------------------------------------------------------------- */

/**
 * @brief Libère la mémoire allouée à l'intégralité de l'arbre (racine, fils,
 * petit-frères).
 * 
 * @param tree L'arbre dont la mémoire doit être libérée.
 * 
 * @note Attention ! Il ne faut surtout pas qu'il y ait de cycle dans l'arbre.
 */
extern void ast_free(Asttree tree);

/* -------------------------------------------------------------------------- */

/**
 * @brief Imprime un arbre sur la sortie spécifiée sous un format lisible pour
 * l'oeil humain.
 * 
 * @param tree L'arbre à imprimer.
 * @param types Les chaînes de caractères associées aux types d'arbres
 * possibles.
 * @param out La sortie sur laquelle imprimer l'arbre (Par défaut, stdout).
 */
extern void ast_print(Asttree tree, char *types[], FILE* out);

/* -------------------------------------------------------------------------- */

#endif
