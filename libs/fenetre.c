#include "fenetre.h"

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
menu_t * creerMenu(char * titre, int largeur, int hauteur, int x, int y) {
    
    // Création de la fenetre
    WINDOW * win = newwin(hauteur, largeur, y, x);
    // On écrit le titre
    box(win, 0, 0);
    mvwprintw(win, 0, 4, titre);
    refresh();

    // On crée le menu
    menu_t * m = (menu_t *)malloc(sizeof(menu_t));
    
    // On initialise les valeurs
    m->fenetre = win;
    m->hauteur = hauteur;
    m->largeur = largeur;
    strcpy(m->titre, titre);
    m->x = x;
    m->y = y;

    // On retourne le menu    
    return m;        
}
