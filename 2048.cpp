#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "modele.hpp"
#include <ncurses.h>
using namespace std;


int main(){
    srand(time(0)); //Initialiser le generateur de nombres aleatoires.
    plateauInitial(); //Commencer une nouvelle partie.

    initscr(); //Initialise l'ecran pour utiliser ncurses.
    start_color(); //Initalise le mode couleur de ncurses.
    noecho(); //Empeche l'affichage des touches tapées par le joueur sur le terminal.
    keypad(stdscr, TRUE); //Permet d'utiliser les touches "spéciales", ici ce sont les fléches. 

    init_pair(1, COLOR_BLACK, COLOR_WHITE); //Texte noir sur fond blanc.
    init_pair(2, COLOR_BLACK, COLOR_YELLOW); //Texte noir sur fond jaune.
    init_pair(3, COLOR_BLACK, COLOR_RED); //Etc...
    init_pair(4, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(5, COLOR_WHITE, COLOR_CYAN);
    init_pair(6, COLOR_WHITE, COLOR_BLUE);
    init_pair(7, COLOR_BLACK, COLOR_GREEN);
    init_pair(8, COLOR_GREEN, COLOR_WHITE);
    init_pair(9, COLOR_RED, COLOR_WHITE);
    init_pair(10, COLOR_CYAN, COLOR_WHITE);
    init_pair(11, COLOR_BLUE, COLOR_WHITE);


    while (estGagnant(plateau) == false && estTerminé(plateau) == false){
        affichage(); //Afficher le plateau. 
        refresh();
        int c = getch(); //Lit la touche pressé par le joueur.
        if (c == 'n') plateauInitial(); //Réinitialise le jeu
        else if (c == KEY_UP || c == 'z'){ //Déplacement haut.
            plateau = déplacement(plateau,'z');
            placerTuile();
        }
        else if (c == KEY_LEFT || c == 'q'){ //Déplacement gauche.
            plateau = déplacement(plateau,'q');
            placerTuile();
        }
        else if (c == KEY_DOWN || c == 's'){ //Déplacement bas.
            plateau = déplacement(plateau,'s');
            placerTuile();
        }
        else if (c == KEY_RIGHT || c == 'd'){ //Déplacement droit.
            plateau = déplacement(plateau,'d');
            placerTuile();
        }
        else if (c == 'a') break; //Quitte le jeu.
        else printw("La commande que vous avez choisie n'est pas valide! \n\n");
    }
    if (estGagnant(plateau) == true){
        printw("Bravo! Vous avez gagné!\n");
        napms(5000); //Afficher le message précedent pendant 5 secondes.
    }
    if (estTerminé(plateau) == true){
        printw("Game over!\n");
        napms(5000); //Afficher le message précedent pendant 5 secondes.
    }

    endwin(); //Fermer l'ecran.
    return 0; //Fin du jeu.
}