/**
  * @file Element.h
  * @brief Fichier d'entête du module \em Element.
  *
  * @author Alexis BRENON
  */

#ifndef __ELEMENT_H__
#define __ELEMENT_H__

/**
  * @typedef Key
  * @brief Une clé est un pointeur sur n'importe quel type.
  * Seule la fonction de hachage devra savoir de quel type elle est.
  */
typedef void* Key;

/**
  * @struct sElement
  * @brief Structure représentant les éléments à stocker dans la table.
  * Cette structure doit absolument contenir un champ de type Key nommé
  key.
  */
struct sElement
{
	Key key; /**< Clé de l'élément (pointera sur le nom */
	char* name;	/**< Nom du contact */
	char num[5];	/**< Numéro du contact */
};
/**
  * @typedef Element
  * @brief Redéfinition de type.
  */
typedef struct sElement Element;





/* ** *************************************************************** ** */
/* **                                                                 ** */
/* **                           INTERFACE                             ** */
/* **                                                                 ** */
/* ** *************************************************************** ** */





/* ** *************************************************************** ** */
/* **  Fonctions de création/initialisation.                          ** */
/* ** *************************************************************** ** */

/**
  * @fn Element* elementCreate (
					const char* name,
					const char num[5]
					);
  * @brief Crée et initialise un élément.
  *
  * @param[in] name Nom du contact
  * @param[in] num Numéro du contact
  * @return L'élément créé.
  */
Element* elementCreate (
					const char* name,
					const char num[5]
					);
/**
  * @fn void elementDestroy (
					Element** ppElem
					);
  * @brief Libère et détruit un élément.
  *
  * @param[in,out] ppElem POinteur sur pointeur sur l'élément à détruire.
  */
void elementDestroy (
					Element** ppElem
					);

/**
  * @fn void elementInit (
				Element* pElem,
				const char* name,
				const char num[5]
				);
  * @brief Initialise un élément.
  *
  * @param[in,out] pElem Pointeur sur l'élément à initialiser.
  * @param[in] name Nom du contact
  * @param[in] num Numéro du contact
  */
void elementInit (
				Element* pElem,
				const char* name,
				const char num[5]
				);
/**
  * @fn void elementRelease (
				Element* pElem
				);
  * @brief Libère l'espace alloué par un élément.
  *
  * @param[in,out] pElem Pointeur sur l'élément à libérer.
  */
void elementRelease (
				Element* pElem
				);

/**
  * @fn void elementCopy (
				Element* pElemDest,
				const Element* pElemSourc
				);
  * @brief Constructeur de copie.
  *
  * @param[out] pElemDest Pointeur sur Element près à être initialisé.
  * @param[in] pElemSourc Element copié.
  */
void elementCopy (
				Element* pElemDest,
				const Element* pElemSourc
				);

/* ** *************************************************************** ** */
/* **  Accesseurs/Mutateurs                                           ** */
/* ** *************************************************************** ** */


/**
  * @fn void elementSetName (
				Element* pElem,
				const char* name
				);
  * @brief Mutateur sur le nom.
  *
  * @param[in,out] pElem Elément
  * @param[in] name Nom du contact.
  */
void elementSetName (
				Element* pElem,
				const char* name
				);
/**
  * @fn const char* elementGetName (
				Element* pElem,
				);
  * @brief Accesseur sur le nom.
  *
  * @param[in,out] pElem Elément
  * @return Nom du contact.
  */
const char* elementGetName (
				Element* pElem
				);

/**
  * @fn void elementSetNum (
				Element* pElem,
				const char num[5]
				);
  * @brief Mutateur sur le numéro.
  *
  * @param[in,out] pElem Elément
  * @param[in] num Numero du contact.
  */
void elementSetNum (
				Element* pElem,
				const char num[5]
				);
/**
  * @fn const char* elementGetNum (
				Element* pElem,
				);
  * @brief Accesseur sur le numéro.
  *
  * @param[in,out] pElem Elément
  * @return Numero du contact.
  */
const char* elementGetNum (
				Element* pElem
				);


/* ** *************************************************************** ** */
/* **  Fonctions relative à la table de hachage                       ** */
/* ** *************************************************************** ** */

/**
  * @fn int elementKeyCmp (
				const Key key1,
				const Key key2
				);
  * @brief Fonction de comparaison de deux clés.
  *
  * @param[in] key1 Première clé
  * @param[in] key2 Deuxieme clé
  * @return 0 si les deux clés sont idéntiques.
  */
int elementKeyCmp (
				const Key key1,
				const Key key2
				);


/**
  * @fn int elementHashExtraction (
				const Key key,
				int iMax
				);
  * @brief Fonction de hachage par extraction.
  *
  * @param[in] key Clé à hacher
  * @param[in] iMax Valeur maximale de la caleur de hachage
  * @return La valeur de hachage correspondant à la clé
  */
int elementHashExtraction (
				const Key key,
				int iMax
				);
/**
  * @fn int elementHashCompression (
				const Key key,
				int iMax
				);
  * @brief Fonction de hachage par compression.
  *
  * @param[in] key Clé à hacher
  * @param[in] iMax Valeur maximale de la caleur de hachage
  * @return La valeur de hachage correspondant à la clé
  */
int elementHashCompression (
				const Key key,
				int iMax
				);
/**
  * @fn int elementHashModulo (
				const Key key,
				int iMax
				);
  * @brief Fonction de hachage par modulo.
  *
  * @param[in] key Clé à hacher
  * @param[in] iMax Valeur maximale de la caleur de hachage
  * @return La valeur de hachage correspondant à la clé
  */
int elementHashModulo (
				const Key key,
				int iMax
				);
/**
  * @fn int elementHashMultiplication (
				const Key key,
				int iMax
				);
  * @brief Fonction de hachage par multiplication.
  *
  * @param[in] key Clé à hacher
  * @param[in] iMax Valeur maximale de la caleur de hachage
  * @return La valeur de hachage correspondant à la clé
  */
int elementHashMultiplication (
				const Key key,
				int iMax
				);

#endif /* __ELEMENT_H__ */
