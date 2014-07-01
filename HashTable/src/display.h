/**
  * @file display.h
  * @brief Fichier d'entete du module \em d'affichage.
  *
  * @author Alexis BRENON
  */

#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "table.h"

/**
  * @fn void printLine (void);
  * @brief Affiche une ligne centrée.
  */
void printLine (void);

/**
  * @fn void printTitle (const char* title);
  * @brief Affiche un titre, centré, entre deux lignes.
  *
  * @param[in] title Le titre à afficher
  */
void printTitle (const char* title);

/**
  * @fn void printManualCreation (Table* pTable);
  * @brief Invite l'utilisateur à créer sa table.
  *
  * @param[in,out] pTable La table non initialisée.
  */
void printManualCreation (Table* pTable);

/**
  * @fn void printAutomaticCreation (Table* pTable);
  * @brief Création automatique de la table.
  *
  * @param[in,out] pTable La table non initialisée.
  */
void printAutomaticCreation (Table* pTable);

/**
  * @fn void printTable (const Table* pTable);
  * @brief Affiche l'ensemble des contacts de la table.
  *
  * @param[in] pTable La table à afficher.
  */
void printTable (const Table* pTable);

/**
  * @fn void printSearch (const Table* pTable);
  * @brief Affiche une invite de recherche.
  *
  * @param[in] pTable La table
  */
void printSearch (const Table* pTable);

/**
  * @fn int printAdd (Table* pTable);
  * @brief Invite à ajouter un contact à la table.
  *
  * @param[in,out] pTable La table
  * @return Le nombre d'entrées dans la table
  */
int printAdd (Table* pTable);

/**
  * @fn int printDel (Table* pTable);
  * @brief Invite à supprimer un contact à la table.
  *
  * @param[in,out] pTable La table
  * @return Le nombre d'entrées dans la table
  */
int printDel (Table* pTable);

/**
  * @fn void printPerfTests (Table* pTable);
  * @brief Génère le fichier de performances.
  *
  * @param[in,out] pTable La table
  */
void printPerfTests (Table* pTable);































#endif
