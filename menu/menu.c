#include <stdio.h>
#include "../libs/fenetre.h"

int main(void) {

    // On initialise la fenetre
    initscr();
    cbreak();
    noecho();

    // On récupère la taille de la fenetre
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // On crée le menu
    menu_t * menu = creerMenu("HamLink", max_x-10, max_y-1, 5, 1);

    // On empeche la fermeture de la fenetre
    // Seul CTRL C fonctionne
    while(wgetch(menu->fenetre));
    endwin();

    return (0);
}