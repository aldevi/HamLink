#include <stdio.h>
#include "../libs/fenetre.h"

void sousMenuLienRadio();
void sousMenuPasserelle();
void sousMenuAudio();
void sousMenuIP();
void sousMenuEthernet();
void sousMenuWiFi();
void sousMenuDHCP();
void sousMenuAX25();

void inputTexte();

int main(void) {

    int flag = 1;
    int c;

    // On crée les lignes du menu
    ligne_t lignes[3] = {
        {.nom = "Lien Radio", .description = "--->", .fonction = sousMenuLienRadio},
        {.nom = "Passerelle", .description = "--->", .fonction = sousMenuPasserelle},
        {.nom = "Audio", .description = "--->", .fonction = sousMenuAudio}
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

void sousMenuLienRadio() {
    int flag = 1;
    int c;

    // On crée les lignes du sous menu
    ligne_t lignes[2] = {
        {.nom = "IP", .description = "--->", .fonction = sousMenuIP},
        {.nom = "AX.25", .description = "--->", .fonction = sousMenuAX25},
    };

    // On récupère la taille de la fenetre
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // On crée le menu
    menu_t * menu = creerMenu(max_y-1, max_x-1, 1, 1, "HamLink - Lien Radio", lignes, 2);
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
                keypad(menu->fenetre, FALSE);
                (*(menu->lignes[menu->curseur]->fonction))();
                keypad(menu->fenetre, TRUE);
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

void sousMenuPasserelle() {
    int flag = 1;
    int c;

    // On crée les lignes du sous menu
    ligne_t lignes[4] = {
        {.nom = "Activer le mode passerelle [y/n]", .description = "", .fonction = NULL},
        {.nom = "Ethernet", .description = "--->", .fonction = sousMenuEthernet},
        {.nom = "WiFi", .description  ="--->", .fonction = sousMenuWiFi},
        {.nom = "DHCP", .description = "--->", .fonction = sousMenuDHCP}
    };

    // On récupère la taille de la fenetre
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // On crée le menu
    menu_t * menu = creerMenu(max_y-1, max_x-1, 1, 1, "HamLink - Passerelle", lignes, 4);
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

void sousMenuIP() {
    int flag = 1;
    int c;

    // On crée les lignes du sous menu
    ligne_t lignes[2] = {
        {.nom = "Adresse IP en AX.25", .description = "", .fonction = NULL},
        {.nom = "Masque", .description = "", .fonction = NULL}
    };

    // On récupère la taille de la fenetre
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // On crée le menu
    // menu_t * menu = creerMenu(max_y-1, max_x-1, 1, 1, "HamLink - IP", lignes, 2);
    formulaire_t * form = creerFormulaire(max_y-1, max_x-1, 1, 1, "HamLink - IP", lignes, 2);
    // mvwprintw(menu->fenetre, max_y-2, 4, "F1 : Retour");


    while(flag) {
        wrefresh(form->fenetre);
        c = wgetch(form->fenetre);
        
        switch(c) {
            case KEY_DOWN:
                descendreFormulaire(form);
                break;
            
            case KEY_UP:
                monterFormulaire(form);
                break;

            case KEY_BACKSPACE :
                form_driver(form->formulaire, REQ_DEL_PREV);
                break;

            case KEY_F(1):
                flag = 0;
                break;

            case KEY_F(2):
                flag = 0;
                form_driver(form->formulaire, REQ_VALIDATION);
                break;

            default:
                // On ajoute le caractère au champ
                form_driver(form->formulaire, c);
                break;
        }
    }

    // On detruit le formulaire
    detruireFormulaire(form);
}

void sousMenuAudio() {
    int flag = 1;
    int c;

    // On crée les lignes du sous menu
    ligne_t lignes[2] = {
        {.nom = "Peripherique d'entree / sortie", .description = "", .fonction = NULL},
        {.nom = "Reglage des niveaux audios [Alsamixer]", .description = "", .fonction = NULL}
    };

    // On récupère la taille de la fenetre
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // On crée le menu
    menu_t * menu = creerMenu(max_y-1, max_x-1, 1, 1, "HamLink - Audio", lignes, 2);
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
                // (*(menu->lignes[menu->curseur]->fonction))();
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

void sousMenuEthernet() {
    int flag = 1;
    int c;

    // On crée les lignes du sous menu
    ligne_t lignes[3] = {
        {.nom = "Activer Ethernet [y/n]", .description = "", .fonction = NULL},
        {.nom = "Adresse IP", .description = "", .fonction = NULL},
        {.nom = "Masque", .description = "", .fonction = NULL}
    };

    // On récupère la taille de la fenetre
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // On crée le formulaire
    formulaire_t * form = creerFormulaire(max_y-1, max_x-1, 1, 1, "HamLink - Ethernet", lignes, 3);
    mvwprintw(form->fenetre, max_y-2, 4, "F1 : Retour");

    while(flag) {
        wrefresh(form->fenetre);
        c = wgetch(form->fenetre);
        
        switch(c) {
            case KEY_DOWN:
                descendreFormulaire(form);
                break;
            
            case KEY_UP:
                monterFormulaire(form);
                break;

            case KEY_BACKSPACE :
                form_driver(form->formulaire, REQ_DEL_PREV);
                break;

            case KEY_F(1):
                flag = 0;
                break;

            case KEY_F(2):
                flag = 0;
                form_driver(form->formulaire, REQ_VALIDATION);
                break;

            default:
                // On ajoute le caractère au champ
                form_driver(form->formulaire, c);
                break;
        }
    }

    // On detruit le formulaire
    detruireFormulaire(form);
}

void sousMenuWiFi() {
    int flag = 1;
    int c;

    // On crée les lignes du sous menu
    ligne_t lignes[4] = {
        {.nom = "Activer WiFi [y/n]", .description = "", .fonction = NULL},
        {.nom = "SSID", .description = "", .fonction = NULL},
        {.nom = "Mot de passe", .description = "", .fonction = NULL},
        {.nom = "Canal", .description = "", .fonction = NULL}
    };

    // On récupère la taille de la fenetre
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // On crée le menu
    formulaire_t * form = creerFormulaire(max_y-1, max_x-1, 1, 1, "HamLink - WiFi", lignes, 4);

    while(flag) {
        wrefresh(form->fenetre);
        c = wgetch(form->fenetre);
        
        switch(c) {
            case KEY_DOWN:
                descendreFormulaire(form);
                break;
            
            case KEY_UP:
                monterFormulaire(form);
                break;

            case KEY_BACKSPACE :
                form_driver(form->formulaire, REQ_DEL_PREV);
                break;

            case KEY_F(1):
                flag = 0;
                break;

            case KEY_F(2):
                flag = 0;
                form_driver(form->formulaire, REQ_VALIDATION);
                break;

            default:
                // On ajoute le caractère au champ
                form_driver(form->formulaire, c);
                break;
        }
    }

    // On detruit le formulaire
    detruireFormulaire(form);
}

void sousMenuDHCP() {
    int flag = 1;
    int c;

    // On crée les lignes du sous menu
    ligne_t lignes[3] = {
        {.nom = "Activer DHCP [y/n]", .description = "", .fonction = NULL},
        {.nom = "Adresse debut de plage", .description = "", .fonction = NULL},
        {.nom = "Adresse fin de plage", .description = "", .fonction = NULL}
    };

    // On récupère la taille de la fenetre
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // On crée le formulaire
    formulaire_t * form = creerFormulaire(max_y-1, max_x-1, 1, 1, "HamLink - DHCP", lignes, 3);

    while(flag) {
        wrefresh(form->fenetre);
        c = wgetch(form->fenetre);
        
        switch(c) {
            case KEY_DOWN:
                descendreFormulaire(form);
                break;
            
            case KEY_UP:
                monterFormulaire(form);
                break;

            case KEY_BACKSPACE :
                form_driver(form->formulaire, REQ_DEL_PREV);
                break;

            case KEY_F(1):
                flag = 0;
                break;

            case KEY_F(2):
                flag = 0;
                form_driver(form->formulaire, REQ_VALIDATION);
                break;

            default:
                // On ajoute le caractère au champ
                form_driver(form->formulaire, c);
                break;
        }
    }

    // On detruit le formulaire
    detruireFormulaire(form);
}

void sousMenuAX25() {
    int flag = 1;
    int c;

    // On crée les lignes du sous menu
    ligne_t lignes[4] = {
        {.nom = "Indicatif radioamateur", .description = "", .fonction = NULL},
        {.nom = "Baudrate", .description = "", .fonction = NULL},
        {.nom = "Activer FX.25 [y/n]", .description = "", .fonction = NULL},
        {.nom = "PTT GPIO", .description = "", .fonction = NULL}
    };

    // On récupère la taille de la fenetre
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // On crée le formulaire
    // menu_t * menu = creerMenu(max_y-1, max_x-1, 1, 1, "HamLink - AX25", lignes, 4);
    formulaire_t * form = creerFormulaire(max_y-1, max_x-1, 1, 1, "HamLink - AX25", lignes, 4);
    // mvwprintw(menu->fenetre, max_y-2, 4, "F1 : Retour");

    while(flag) {
        wrefresh(form->fenetre);
        c = wgetch(form->fenetre);
        
        switch(c) {
            case KEY_DOWN:
                descendreFormulaire(form);
                break;
            
            case KEY_UP:
                monterFormulaire(form);
                break;

            case KEY_BACKSPACE :
                form_driver(form->formulaire, REQ_DEL_PREV);
                break;

            case KEY_F(1):
                flag = 0;
                break;

            case KEY_F(2):
                flag = 0;
                form_driver(form->formulaire, REQ_VALIDATION);
                break;

            default:
                // On ajoute le caractère au champ
                form_driver(form->formulaire, c);
                break;
        }
    }

    // On detruit le formulaire
    detruireFormulaire(form);
}

void inputTexte() {

    int flag = 1;
    int ch;

    ligne_t lignes[5] = {
        {"Option 1", "--->", NULL},
        {"Option 2", "--->", NULL},
        {"Option 3", "--->", NULL},
        {"Option 4", "--->", NULL},
        {"Option 5", "--->", NULL}
    };

    // On récupère la taille de la fenetre
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    formulaire_t * form = creerFormulaire(max_y/2, max_x-1, max_y/2, 1, "Options", lignes, 5);

    while(flag) {
        ch = wgetch(form->fenetre);
        wrefresh(form->fenetre);
        switch(ch) {
            
            case KEY_DOWN:
                descendreFormulaire(form);
                break;
            
            case KEY_UP:
                monterFormulaire(form);
                break;

            case KEY_BACKSPACE :
                form_driver(form->formulaire, REQ_DEL_PREV);
                break;

            case KEY_F(1):
                flag = 0;
                break;

            case KEY_F(2):
                flag = 0;
                form_driver(form->formulaire, REQ_VALIDATION);
                break;

            default:
                // On ajoute le caractère au champ
                form_driver(form->formulaire, ch);
                break;
        }
    }

    // On detruit le formulaire
    detruireFormulaire(form);
}