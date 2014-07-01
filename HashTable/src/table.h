/**
  * @file table.h
  * @brief Fichier d'entetedu module \em Table de hachage.
  *
  * @author Alexis BRENON
  */

#ifndef __TABLE_H__
#define __TABLE_H__

#include "Element.h"

/**
  * @enum RehashType
  * @brief Enumère les type de rehashage.
  */
enum RehashType
{
	LINEAR_REHASH, /**< Rehachage linéaire */
	QUADRATIC_REHASH, /**< Rehachage quadratique */
	DOUBLE_HASH	/**< Double hachage */
};

/**
  * @struct sTable
  * @brief Une table est un tableau de pointeur sur Element.
  *
  * Notre table de hachage est un tableau (de taille définie à
  l'initialisation), qui pointe sur des Elements contenant forcément un
  champ nommé "key" qui est une chaine de caractère servant de clé.
  */
/**
  * @todo Ajouté un champs 'Conditionnel' en cas de double hachage pour
  utiliser une seconde fonction de hachage au lieu d'utiliser deux fois la
  même fonction.
  */
struct sTable
{
	Element** parrTab; 	/**< Tableau de pointeurs d'élément */
	int* iarrEmpty; /**< Tableau permettant de savoir si une case est vide ou non. */
	int iMaxSize;		/**< Taille maximale de la table */
	int iUsedSize;		/**< Nombre d'Elements stockés actuellement */
	int (*fHashFunc) (const Key, int); /**< Fonction de hachage */
	int (*fKeyCmp) (const Key, const Key); /**< Fonction de comparaison de clés */
	enum RehashType eRehashType; /**< Type de rehachage */

	void (*fCopy) 		(Element*, const Element*); /**< Fonction de copie d'Elements */
	void (*fRelease) 	(Element*);			 /**< Fonction de libération d'un Element */
};
/**
  * @typedef Table
  * @brief Redéfinition de type.
  */
typedef struct sTable Table;






/* ** *************************************************************** ** */
/* **                                                                 ** */
/* **                           INTERFACE                             ** */
/* **                                                                 ** */
/* ** *************************************************************** ** */





/* ** *************************************************************** ** */
/* **  Fonctions de création/initialisation.                          ** */
/* ** *************************************************************** ** */


/**
  * @fn Table* tableCreate (
				int m,
				int (*fHash) (const Key, int),
				int (*fKeyCmp) (const Key, const Key),
				enum RehashType eRehashType,
				void (*fCopyElement) (Element*, const Element*),
				void (*fReleaseElement) (Element*)
				);
  * @brief Crée et initialise une nouvelle table de hachage.
  *
  * @param[in] m Taille maximale de la table
  * @param[in] fHash Fonction de hachage
  * @param[in] fKeyCmp Fonction de comparaison de deux clés
  * @param[in] eRehashType Type de rehachage
  * @param[in] fCopyElement Fonction de copie d'Elements
  * @param[in] fReleaseElement Fonction de libération d'un Element
  * @return Un pointeur sur la nouvelle table.
  */
Table* tableCreate (
				int m,
				int (*fHash) (const Key, int),
				int (*fKeyCmp) (const Key, const Key),
				enum RehashType eRehashType,
				void (*fCopyElement) (Element*, const Element*),
				void (*fReleaseElement) (Element*)
				);
/**
  * @fn void tableDestroy (Table** ppTab);
  * @brief Détruit une table après l'avoir liberée.
  *
  * @param[in,out] ppTab Pointeur sur pointeur sur une table créée.
  */
void tableDestroy (
				Table** ppTab
				);

/**
  * @fn void tableInit (
				Table* pTab,
				int m,
				int (*fHash) (const Key, int),
				int (*fKeyCmp) (const Key, const Key),
				enum RehashType eRehashType,
				void (*fCopyElement) (Element*, const Element*),
				void (*fReleaseElement) (Element*)
				);
  * @brief Initialise une table déja allouée.
  *
  * @param[in,out] pTab Table de hachage allouée mais pas initialisée.
  * @param[in] m Taille maximale de la table
  * @param[in] fHash Fonction de hachage
  * @param[in] fKeyCmp Fonction de comparaison de deux clés
  * @param[in] eRehashType Type de rehachage
  * @param[in] fCopyElement Fonction de copie d'Elements
  * @param[in] fReleaseElement Fonction de libération d'un Element
  */
void tableInit (
				Table* pTab,
				int m,
				int (*fHash) (const Key, int),
				int (*fKeyCmp) (const Key, const Key),
				enum RehashType eRehashType,
				void (*fCopyElement) (Element*, const Element*),
				void (*fReleaseElement) (Element*)
				);
/**
  * @fn void tableRelease (Table* pTab);
  * @brief Libère la mémoire allouée pour une table de hachage.
  *
  * @param[in,out] pTab La table à libérée
  */
void tableRelease (
				Table* pTab
				);


/* ** *************************************************************** ** */
/* **  Fonctions de lecture/écriture.                                 ** */
/* ** *************************************************************** ** */


/**
  * @fn int tableInsert (Table* pTab, const Element* Elem);
  * @brief Ajoute l'élément Elem à la table pTab.
  * Elem doit contenir une champ nomme "key" qui sera une chaine de
caractères et qui servira de clé.
  *
  * @param[in,out] pTab Table
  * @param[in] Elem Element à copier et ajouter.
  * @return Le nombre d'éléments dans la table.
  */
int tableInsert (
				Table* pTab,
				const Element* Elem
				);
/**
  * @fn int tableRemoveElement (Table* pTab, const Element* Elem);
  * @brief Supprime l'élément Elem de la table.
  * Elem doit contenir une champ nomme "key" qui sera une chaine de
caractères et qui servira de clé.
  *
  * @param[in,out] pTab Table
  * @param[in] Elem Element à supprimer.
  * @return Le nombre d'éléments dans la table.
  */
int tableRemoveElement (
				Table* pTab,
				const Element* Elem
				);
/**
  * @fn int tableRemoveKey (Table* pTab, const Key key);
  * @brief Supprime l'élément ayant pour clé "key" de la table.
  *
  * @param[in,out] pTab Table
  * @param[in] key Clé de l'élément
  * @return Le nombre d'éléments dans la table.
  */
int tableRemoveKey (
				Table* pTab,
				const Key key
				);

/**
  * @fn Element* tableGetElement (
				const Table* pTab,
				const Key key
				);
  * @brief Permet d'obtenir un élément dans la table.
  *
  * @param[in] pTab Table
  * @param[in] key Clé de l'élément à obtenir
  * @return Un pointeur sur l'élément possédant la clé key ou NULL.
  */
Element* tableGetElement (
				const Table* pTab,
				const Key key
				);
/**
  * @fn Element* tableGetElementbyIndex (
				const Table* pTab,
				int i
				);
  * @brief Permet d'obtenir un élément dans la table.
  *
  * @param[in] pTab Table
  * @param[in] i Index de l'élément
  * @return Un pointeur sur l'élément ou NULL.
  */
Element* tableGetElementbyIndex (
					const Table* pTab,
					int i
					);


/* ** *************************************************************** ** */
/* **  Fonctions d'information.                                       ** */
/* ** *************************************************************** ** */

/**
  * @fn int tableIsEmpty (
				const Table* pTab
				);
  * @brief Permet de savoir si la table est vide ou non.
  *
  * @param[in] pTab Table
  * @return 1 si pTab est vide, 0 sinon
  */
int tableIsEmpty (
				const Table* pTab
				);

/**
  * @fn int tableGetNbElement (
				const Table* pTab
				);
  * @brief Permet de savoir combien d'éléments sont présent dans la table.
  *
  * @param[in] pTab La table
  * @return Le nombre d'Elements.
  */
int tableGetNbElement (
				const Table* pTab
				);

/**
  * @fn int tableMaxSize (
				const Table* pTab
				);
  * @brief Permet d'obtenir la taille maximale de la table.
  *
  * @param[in] pTab Table
  * @return La taille maximale de la table
  */
int tableMaxSize (
				const Table* pTab
				);


#endif /* __TABLE_H__ */
