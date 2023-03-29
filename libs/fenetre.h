#include <menu.h>
#include <form.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

// CONSTANTES

#define MAX_ITEM_MENU 30
#define MAX_CHAR 255

// STRUCTURES

// Ligne d'un menu
typedef struct {
    char nom[MAX_CHAR];
    char description[MAX_CHAR];
    void (* fonction)(); // Fonction à appeler
} ligne_t;

// Menu
typedef struct {
    WINDOW * fenetre;
    MENU * menu;
    ligne_t ** lignes;
    ITEM ** items;
    int nbItems;
    int hauteur;
    int largeur;
    int x;
    int y;
    int curseur;
    char titre[MAX_CHAR];
} menu_t;

// Formulaire
typedef struct {
    WINDOW * fenetre;
    FORM * formulaire;
    FIELD ** champs;
    ligne_t ** lignes;
    int nbChamps;
    int hauteur;
    int largeur;
    int x;
    int y;
    int curseur;
    char titre[MAX_CHAR];
} formulaire_t;

/**
 * @brief Crée un menu et l'affiche
 * 
 * @param hauteur Hauteur de la fenetre
 * @param largeur Largeur de la fenetre
 * @param x Position en x de la fenetre
 * @param y Position en y de la fenetre
 * @param titre Titre du menu 
 * @param lignes Liste des lignes du menu
 * @param nbLignes Nombre de lignes du menu
 * @return menu_t* Menu créé
 */
menu_t * creerMenu(int hauteur, int largeur, int x, int y, char * titre, ligne_t lignes[], int nbLignes);

/**
 * @brief Crée un formulaire et l'afficheg
 * 
 * @param hauteur Hauteur de la fenetre
 * @param largeur Largeur de la fenetre
 * @param x Position en x de la fenetre
 * @param y Position en y de la fenetre
 * @param titre Titre du formulaire
 * @param lignes Liste des lignes du formulaire
 * @param nbChamps Nombre de champs du formulaire
 * @return formulaire_t* Formulaire créé
 */
formulaire_t * creerFormulaire(int hauteur, int largeur, int x, int y, char * titre, ligne_t lignes[], int nbChamps);

/**
 * @brief Détruit un menu
 * 
 * @param menu Menu à détruire
 */
void detruireMenu(menu_t * menu);

void detruireFormulaire(formulaire_t * formulaire);

void descendreFormulaire(formulaire_t * formulaire);

void monterFormulaire(formulaire_t * formulaire);

/**
 * @brief Déplace le curseur vers le bas
 * 
 * @param menu Menu concerné
 */
void descendreMenu(menu_t * menu);

/**
 * @brief Déplace le curseur vers le haut
 * 
 * @param menu Menu concerné
 */
void monterMenu(menu_t * menu);

/**
 * @brief Rafraichit le menu
 * 
 * @param menu Menu concerné
 */
void refreshMenu(menu_t * menu);

char * suppr_espaces(char * chan,char cara);