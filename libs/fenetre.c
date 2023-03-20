#include "fenetre.h"

menu_t * creerMenu(int hauteur, int largeur, int x, int y, char * titre, ligne_t lignes[], int nbItems) {

    // On alloue la memoire pour le menu
    menu_t * menu = malloc(sizeof(menu_t));

    // On initialise les variables
    menu->hauteur = hauteur;
    menu->largeur = largeur;
    menu->x = x;
    menu->y = y;
    menu->nbItems = nbItems;
    menu->curseur = 0;
    strcpy(menu->titre, titre);

    // On crée la fenetre
    menu->fenetre = newwin(hauteur, largeur, x, y);

    // On crée les lignes et items
    menu->lignes = (ligne_t **)calloc(nbItems + 1, sizeof(ligne_t *));
    menu->items = (ITEM **)calloc(nbItems + 1, sizeof(ITEM *));
    
    for(int i = 0; i < nbItems; i++) {
        
        menu->lignes[i] = malloc(sizeof(ligne_t));
        strcpy(menu->lignes[i]->nom, lignes[i].nom);
        strcpy(menu->lignes[i]->description, lignes[i].description);
        menu->lignes[i]->fonction = lignes[i].fonction;
        
        menu->items[i] = new_item(lignes[i].nom, lignes[i].description);
    }

    // On crée le menu
    menu->menu = new_menu((ITEM **)menu->items);    

    // On active le clavier
    keypad(menu->fenetre, TRUE);

    // On lie le menu à la fenetre
    set_menu_win(menu->menu, menu->fenetre);
    set_menu_sub(menu->menu, derwin(menu->fenetre, hauteur-4, largeur-2, 3, 1));
    set_menu_mark(menu->menu, " * ");
    
    // On affiche la fenetre
    box(menu->fenetre, 0, 0);
    mvwprintw(menu->fenetre, 1, (largeur-strlen(titre))/2, "%s", titre);
    wrefresh(menu->fenetre);
    
    // On affiche le menu
    post_menu(menu->menu);
    wrefresh(menu->fenetre);

    return menu;
}

/**
 * @brief Détruit un menu
 * 
 * @param menu Menu à détruire
 */
void detruireMenu(menu_t * menu) {

    // On detruit le menu
    unpost_menu(menu->menu);
    free_menu(menu->menu);
    for(int i = 0; menu->items[i]; i++) {
        free(menu->lignes[i]);
        free_item(menu->items[i]);
    }

    // On detruit la fenetre
    delwin(menu->fenetre);

    // On detruit le menu
    free(menu);
    endwin();
}

/**
 * @brief Déplace le curseur vers le bas
 * 
 * @param menu Menu concerné
 */
void descendreMenu(menu_t * menu) {
    if (menu->curseur < menu->nbItems-1) {
        menu_driver(menu->menu, REQ_DOWN_ITEM);
        menu->curseur++;
    }
}

/**
 * @brief Déplace le curseur vers le haut
 * 
 * @param menu Menu concerné
 */
void monterMenu(menu_t * menu) {
    if (menu->curseur > 0) {
        menu_driver(menu->menu, REQ_UP_ITEM);
        menu->curseur--;
    }
}

/**
 * @brief Rafraichit le menu
 * 
 * @param menu Menu concerné
 */
void refreshMenu(menu_t * menu) {
    unpost_menu(menu->menu);
    set_menu_win(menu->menu, menu->fenetre);
    set_menu_sub(menu->menu, derwin(menu->fenetre, menu->hauteur-4, menu->largeur-2, 3, 1));
    set_menu_mark(menu->menu, " * ");
    box(menu->fenetre, 0, 0);
    mvwprintw(menu->fenetre, 1, (menu->largeur-strlen(menu->titre))/2, "%s", menu->titre);
    mvwprintw(menu->fenetre, menu->hauteur-1, 4, "F1 : Retour");
    post_menu(menu->menu);
    wrefresh(menu->fenetre);
}