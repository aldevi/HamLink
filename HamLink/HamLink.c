#include <stdio.h>
#include "../libs/fenetre.h"

/**
 * @brief Sous menu de configuration
 * 
 */
void sousMenuConfiguration();

/**
 * @brief Sous menu de statistiques
 * 
 */
void sousMenuStatistiques();

/**
 * @brief Sous menu d'outils
 * 
 */
void sousMenuOutils();

int main(void) {

    int flag = 1;
    int c;

    // On crée les lignes du menu
    ligne_t lignes[3] = {
        {.nom = "Configuration", .description = "--->", .fonction = sousMenuConfiguration},
        {.nom = "Statistiques", .description = "--->", .fonction = sousMenuStatistiques},
        {.nom = "Outils", .description = "--->", .fonction = sousMenuOutils}
    };

    // On initialise la fenetre
    initscr();
    cbreak();
    noecho();

    // On récupère la taille de la fenetre
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // On crée le menu
    menu_t * menu = creerMenu(max_y-1, max_x-1, 1, 1, "HamLink", lignes, 3);
    mvwprintw(menu->fenetre, max_y-2, 4, "F1 : Quitter");

    while(flag) {
        mvwprintw(menu->fenetre, 0, 0, "posMenu : %d", menu->curseur);
        wrefresh(menu->fenetre);
        c = wgetch(menu->fenetre);
        
        switch(c) {
            case KEY_DOWN:
                descendreMenu(menu);
                break;
            case KEY_UP:
                monterMenu(menu);
                break;

            // Touche entrée = 10
            case '\n' :
                // On execute la fonction
                (*(menu->lignes[menu->curseur]->fonction))();
                refreshMenu(menu);
                break;

            case KEY_F(1):
                flag = 0;
                break;
        }
    }

    // On detruit le menu
    detruireMenu(menu);
    return (0);
}

void sousMenuConfiguration() {
    int flag = 1;
    int c;

    // On crée les lignes du sous menu
    ligne_t lignes[3] = {
        {"Configuration 1", "--->", NULL},
        {"Configuration 2", "--->", NULL},
        {"Configuration 3", "--->", NULL}
    };

    // On récupère la taille de la fenetre
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // On crée le menu
    menu_t * menu = creerMenu(max_y-1, max_x-1, 1, 1, "HamLink - Configuration", lignes, 3);
    mvwprintw(menu->fenetre, max_y-2, 4, "F1 : Retour");

    while(flag) {
        mvwprintw(menu->fenetre, 0, 0, "posMenu : %d", menu->curseur);
        wrefresh(menu->fenetre);
        c = wgetch(menu->fenetre);
        
        switch(c) {
            case KEY_DOWN:
                descendreMenu(menu);
                break;
            case KEY_UP:
                monterMenu(menu);
                break;

            // Touche entrée = 10
            case '\n' :
                // On execute la fonction
                (*(menu->lignes[menu->curseur]->fonction))();
                refreshMenu(menu);
                break;

            case KEY_F(1):
                flag = 0;
                break;
        }
    }

    // On detruit le menu
    detruireMenu(menu);
}

void sousMenuStatistiques() {
    
}

void sousMenuOutils() {

}