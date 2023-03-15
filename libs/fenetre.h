#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

// CONSTANTES

#define MAX_LIGNE_MENU 15
#define MAX_TITRE 255

// STRUCTURES

typedef struct {
    char * contenu;
} ligne_t;

typedef struct {
    WINDOW * fenetre;
    char titre[MAX_TITRE];
    int largeur, hauteur;
    int x, y;
    ligne_t options[MAX_LIGNE_MENU];
} menu_t;

// FONCTIONS

/**
 * @brief Créer une fenetre
 * 
 * @param titre Titre de la fenetre
 * @param largeur Largeur de la fenetre
 * @param hauteur Hauteur de la fenetre
 * @param x Position x
 * @param y Position y
 * @return menu_t* Le menu
 */
menu_t * creerMenu(char * titre, int largeur, int hauteur, int x, int y);