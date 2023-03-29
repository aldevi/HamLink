#include <stdio.h>
#include <stdlib.h>
#include "../libs/fenetre.h"
#include "../libs/config_parser.h"

void sousMenuLienRadio();
void sousMenuPasserelle();
void sousMenuAudio();
void sousMenuIP();
void sousMenuEthernet();
void sousMenuWiFi();
void sousMenuDHCP();
void sousMenuAX25();
void switchModePasserelle();
void lancerAlsamixer();

/* --- VARIABLES GLOBALES --- */
hamlinkd_config * hamlinkdConf;

int main(void) {

    int flag = 1;
    int c;

    // On alloue la mémoire pour la structure de configuration
    hamlinkdConf = malloc(sizeof(hamlinkd_config));

    // On parse le fichier de configuration
    hamlinkd_parse_config(hamlinkdConf);

    // On crée les lignes du menu
    ligne_t lignes[4] = {
        {.nom = "Lien Radio", .description = "--->", .fonction = sousMenuLienRadio},
        {.nom = "Passerelle", .description = "--->", .fonction = sousMenuPasserelle},
        {.nom = "Audio", .description = "--->", .fonction = sousMenuAudio},
        {.nom = "Reglage des niveaux audios [Alsamixer]", .description = "", .fonction = lancerAlsamixer}
    };

    // On initialise la fenetre
    initscr();
    cbreak();
    noecho();

    // On récupère la taille de la fenetre
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // On crée le menu
    menu_t * menu = creerMenu(max_y-1, max_x-1, 1, 1, "HamLink", lignes, 4);
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

    // Sauvegarder les configurations
    hamlinkd_save_config(hamlinkdConf);

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
        {.nom = "Activer le mode passerelle [y/n]", .description = "", .fonction = switchModePasserelle},
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
                lignes[0].description[0] = hamlinkdConf->gateway_enable ? 'y' : 'n';
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

    strcpy(lignes[0].description, hamlinkdConf->ax25_ip);
    strcpy(lignes[1].description, hamlinkdConf->ax25_netmask);

    // On récupère la taille de la fenetre
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // On crée le menu
    formulaire_t * form = creerFormulaire(max_y-1, max_x-1, 1, 1, "HamLink - IP", lignes, 2);

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
                
                // On sauvegarde les paramètres
                strcpy(hamlinkdConf->ax25_ip, suppr_espaces(field_buffer(form->champs[0], 0), 0));
                strcpy(hamlinkdConf->ax25_netmask, suppr_espaces(field_buffer(form->champs[1], 0), 0));
                
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
    ligne_t lignes[1] = {
        {.nom = "Peripherique d'entree / sortie", .description = "", .fonction = NULL},
    };

    strcpy(lignes[0].description, hamlinkdConf->audio_device);

    // On récupère la taille de la fenetre
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // On crée le formulaire
    formulaire_t * form = creerFormulaire(max_y-1, max_x-1, 1, 1, "HamLink - Audio", lignes, 1);

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

                // On sauvegarde les paramètres
                strcpy(hamlinkdConf->audio_device, suppr_espaces(field_buffer(form->champs[0], 0), 0));

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

void sousMenuEthernet() {
    int flag = 1;
    int c;

    // On crée les lignes du sous menu
    ligne_t lignes[3] = {
        {.nom = "Activer Ethernet [y/n]", .description = "", .fonction = NULL},
        {.nom = "Adresse IP", .description = "", .fonction = NULL},
        {.nom = "Masque", .description = "", .fonction = NULL}
    };

    strcpy(lignes[0].description, hamlinkdConf->eth_gateway_enable ? "y" : "n");
    strcpy(lignes[1].description, hamlinkdConf->eth_gateway_ip);
    strcpy(lignes[2].description, hamlinkdConf->eth_gateway_netmask);

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

                // On sauvegarde les paramètres
                hamlinkdConf->eth_gateway_enable = field_buffer(form->champs[1], 0)[0] == 'y';
                strcpy(hamlinkdConf->eth_gateway_ip, suppr_espaces(field_buffer(form->champs[1], 0 ), 0));
                strcpy(hamlinkdConf->eth_gateway_netmask, suppr_espaces(field_buffer(form->champs[2], 0 ), 0));

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

    char buffer[MAX_CHAR];

    // On crée les lignes du sous menu
    ligne_t lignes[4] = {
        {.nom = "Activer WiFi [y/n]", .description = "", .fonction = NULL},
        {.nom = "SSID", .description = "", .fonction = NULL},
        {.nom = "Mot de passe", .description = "", .fonction = NULL},
        {.nom = "Canal", .description = "", .fonction = NULL}
    };

    strcpy(lignes[0].description, hamlinkdConf->wifi_gateway_enable ? "y" : "n");
    strcpy(lignes[1].description, hamlinkdConf->wifi_gateway_ssid);
    strcpy(lignes[2].description, hamlinkdConf->wifi_gateway_psk);

    sprintf(buffer, "%d", hamlinkdConf->wifi_gateway_channel);
    strcpy(lignes[3].description, buffer);

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

                // On sauvegarde les paramètres
                hamlinkdConf->wifi_gateway_enable = field_buffer(form->champs[0], 0)[0] == 'y';
                strcpy(hamlinkdConf->wifi_gateway_ssid, suppr_espaces(field_buffer(form->champs[1], 0), 0));
                strcpy(hamlinkdConf->wifi_gateway_psk, suppr_espaces(field_buffer(form->champs[2], 0), 0));
                hamlinkdConf->wifi_gateway_channel = atoi(suppr_espaces(field_buffer(form->champs[3], 0), 0));

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

    strcpy(lignes[0].description, hamlinkdConf->gateway_dhcp_enable ? "y" : "n");
    strcpy(lignes[1].description, hamlinkdConf->gateway_dhcp_start);
    strcpy(lignes[2].description, hamlinkdConf->gateway_dhcp_end);

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

                // On sauvegarde les modifications
                hamlinkdConf->gateway_dhcp_enable = field_buffer(form->champs[0], 0)[0] == 'y';
                strcpy(hamlinkdConf->gateway_dhcp_start, suppr_espaces(field_buffer(form->champs[1], 0), 0));
                strcpy(hamlinkdConf->gateway_dhcp_end, suppr_espaces(field_buffer(form->champs[2], 0), 0));

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
    char bufferBaudrate[MAX_CHAR];
    char bufferGPIO[MAX_CHAR];

    // On crée les lignes du sous menu
    ligne_t lignes[4] = {
        {.nom = "Indicatif radioamateur", .description = "", .fonction = NULL},
        {.nom = "Baudrate", .description = "", .fonction = NULL},
        {.nom = "Activer FX.25 [y/n]", .description = "", .fonction = NULL},
        {.nom = "PTT GPIO", .description = "", .fonction = NULL}
    };

    strcpy(lignes[0].description, hamlinkdConf->ax25_callsign);

    sprintf(bufferBaudrate, "%d", hamlinkdConf->ax25_baudrate);
    strcpy(lignes[1].description, bufferBaudrate);

    strcpy(lignes[2].description, hamlinkdConf->ax25_enable_fx25 ? "y" : "n");
    
    sprintf(bufferGPIO, "%d", hamlinkdConf->ax25_ptt_gpio);
    strcpy(lignes[3].description, bufferGPIO);

    // On récupère la taille de la fenetre
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // On crée le formulaire
    // menu_t * menu = creerMenu(max_y-1, max_x-1, 1, 1, "HamLink - AX25", lignes, 4);
    formulaire_t * form = creerFormulaire(max_y-1, max_x-1, 1, 1, "HamLink - AX25", lignes, 4);

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
                
                // On récupère les valeurs du formulaire
                strcpy(hamlinkdConf->ax25_callsign, suppr_espaces(field_buffer(form->champs[0], 0), 0));
                hamlinkdConf->ax25_baudrate = atoi(suppr_espaces(field_buffer(form->champs[1], 0), 0));
                hamlinkdConf->ax25_enable_fx25 = field_buffer(form->champs[2], 0)[0] == 'y';
                hamlinkdConf->ax25_ptt_gpio = atoi(suppr_espaces(field_buffer(form->champs[3], 0), 0));

                break;

            default:
                // On ajoute le caractère au champ
                form_driver(form->formulaire, c);
                form_driver(form->formulaire, '\0');
                
                break;
        }
    }
    // On detruit le formulaire
    detruireFormulaire(form);
}

void switchModePasserelle() {
    hamlinkdConf->eth_gateway_enable = 1 - hamlinkdConf->eth_gateway_enable;
}

void lancerAlsamixer() {
    // On lance alsa mixer
    system("alsamixer");
}