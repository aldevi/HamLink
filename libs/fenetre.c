#include "fenetre.h"

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
formulaire_t * creerFormulaire(int hauteur, int largeur, int x, int y, char * titre, ligne_t lignes[], int nbChamps) {

    // On alloue la memoire pour le formulaire
    formulaire_t * formulaire = malloc(sizeof(formulaire_t));
    
    // On initialise les variables
    formulaire->hauteur = hauteur;
    formulaire->largeur = largeur;
    formulaire->x = x;
    formulaire->y = y;
    formulaire->nbChamps = nbChamps;
    formulaire->curseur = 0;
    strcpy(formulaire->titre, titre);

    // On crée la fenetre
    formulaire->fenetre = newwin(hauteur, largeur, x, y);

    // On affiche la fenetre
    box(formulaire->fenetre, 0, 0);

    // On crée les lignes et champs
    formulaire->lignes = (ligne_t **)calloc(nbChamps + 1, sizeof(ligne_t *));
    formulaire->champs = (FIELD **)calloc(nbChamps + 1, sizeof(FIELD *));

    for(int i = 0; i < nbChamps; i++) {
        
        formulaire->lignes[i] = malloc(sizeof(ligne_t));
        strcpy(formulaire->lignes[i]->nom, lignes[i].nom);
        strcpy(formulaire->lignes[i]->description, lignes[i].description);
        formulaire->lignes[i]->fonction = lignes[i].fonction;
        
        formulaire->champs[i] = new_field(1, largeur/2, (2*i)+2, strlen(formulaire->lignes[i]->nom) + 5, 0, 0);
        set_field_back(formulaire->champs[i], A_UNDERLINE);
        field_opts_off(formulaire->champs[i], O_AUTOSKIP);
        set_field_buffer(formulaire->champs[i], 0, lignes[i].description);
    }

    // On ajoute un champ vide pour terminer la liste
    formulaire->champs[nbChamps] = NULL;

    // On crée le formulaire
    formulaire->formulaire = new_form(formulaire->champs);

    // On active le clavier
    keypad(formulaire->fenetre, TRUE);

    // On lie le formulaire à la fenetre
    set_form_win(formulaire->formulaire, formulaire->fenetre);
    set_form_sub(formulaire->formulaire, derwin(formulaire->fenetre, hauteur-2, largeur-2, 1, 1));
    
    // On affiche le formulaire
    post_form(formulaire->formulaire);

    // On affiche le titre
    mvwprintw(formulaire->fenetre, 1, (largeur-strlen(titre))/2, "%s", titre);

    // On affiche les touches
    mvwprintw(formulaire->fenetre, hauteur-1, 4, "F1 : Retour | F2 : Sauvegarder");

    for (int i = 0 ; i < nbChamps ; i++)
        mvwprintw(formulaire->fenetre, (2*i)+3, 1, "%s", lignes[i].nom);

    // On affiche le titre
    wrefresh(formulaire->fenetre);

    return formulaire;
}

void detruireFormulaire(formulaire_t * formulaire) {
    
    // On detruit le formulaire
    unpost_form(formulaire->formulaire);
    free_form(formulaire->formulaire);
    for(int i = 0; formulaire->champs[i]; i++) {
        free(formulaire->lignes[i]);
        free_field(formulaire->champs[i]);
    }

    // On detruit la fenetre
    delwin(formulaire->fenetre);

    // On detruit le formulaire
    free(formulaire);
    endwin();
}

/**
 * @brief Déplace le curseur vers le bas
 * 
 * @param formulaire Formulaire concerné
 */
void descendreFormulaire(formulaire_t * formulaire) {
    if (formulaire->curseur < formulaire->nbChamps-1) {
        form_driver(formulaire->formulaire, REQ_NEXT_FIELD);
        formulaire->curseur++;
    }
}

/**
 * @brief Déplace le curseur vers le haut
 * 
 * @param formulaire Formulaire concerné
 */
void monterFormulaire(formulaire_t * formulaire) {
    if (formulaire->curseur > 0) {
        form_driver(formulaire->formulaire, REQ_PREV_FIELD);
        formulaire->curseur--;
    }
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