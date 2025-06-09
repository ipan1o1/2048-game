#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "modele.hpp"
#include <ncurses.h>
using namespace std;

using Plateau = vector<vector<int>>;
Plateau plateau(4,vector<int>(4,0)); //Créer un plateau 4x4 rempli de zéros.
int score = 0; //Initialiser le score du joueur a 0.

int tireDeuxOuQUatre(){ //Fonction qui choisit entre 2 et 4 de maniere aleatoire.
    int aleatoire = rand() % 100 + 1; //Génerer un nombre entre 1 et 100.
    if (aleatoire <= 90) return 2; //Si il est inferieur ou egal a 90, on obtient la valeur 2. (Probabilité de 9/10)
    else return 4; //Si il est superieur a 90, on obtient la valeur 4. (Probabilité de 1/10)
}

Plateau plateauVide(){ //Créer un plateau 4x4 rempli de zéros.
    return Plateau(4, vector<int>(4, 0));
}


void placerTuile(){
    int ligne, colonne;
    do{
        ligne = rand()%4; //Trouver une case aleatoire, commencant par toruver une ligne aleatoire..
        colonne = rand()%4; // puis une colonne aleatoire.
    } while (plateau[ligne][colonne] != 0); //Cette case doite etre vide.
    plateau[ligne][colonne] = tireDeuxOuQUatre(); //Affecter une valeur (2 ou 4) a cette case vide.
}


Plateau plateauInitial(){ //Réinitialise le jeu et place 2 tuiles aléatoirement.
    score = 0; //Rénitaliser le score du joueur.
    plateau = plateauVide(); //Le plateau doit etre vide.
    placerTuile(); //On place deux tuiles aleatoirement.
    placerTuile();
    return plateau;
}

void affichage() {  
    clear(); //Effacer tout ce qui est au terminal.
    attron(COLOR_PAIR(6)); //Afficher le texte suivant avec le paire de couleurs 6.
    printw("---------------------\n");
    attroff(COLOR_PAIR(6)); //Desactiver le paire de couleurs 6.
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (plateau[i][j] == 0) {
                printw("|    "); 
            } else {
                if (plateau[i][j] == 2){ 
                    attron(COLOR_PAIR(1));//Si une case contient 2, on l'attribue le pair de couleurs 1.
                }if (plateau[i][j] == 4){
                    attron(COLOR_PAIR(2)); //Si une case contient 4, on l'attribue le pair de couleurs 2.
                }if (plateau[i][j] == 8){
                    attron(COLOR_PAIR(3)); //Etc..
                }if (plateau[i][j] == 16){
                    attron(COLOR_PAIR(4));
                }if (plateau[i][j] == 32){
                    attron(COLOR_PAIR(6));
                }if (plateau[i][j] == 64){
                    attron(COLOR_PAIR(5));
                }if (plateau[i][j] == 128){
                    attron(COLOR_PAIR(7));
                }if (plateau[i][j] == 256){
                    attron(COLOR_PAIR(8));
                }if (plateau[i][j] == 512){
                    attron(COLOR_PAIR(9));
                }if (plateau[i][j] == 1024){
                    attron(COLOR_PAIR(10));
                }if (plateau[i][j] == 2048){
                    attron(COLOR_PAIR(11));
                }
                printw("|%4d", plateau[i][j]); 
                attroff(COLOR_PAIR(1) | COLOR_PAIR(2) | COLOR_PAIR(3) | COLOR_PAIR(4) | COLOR_PAIR(5) | COLOR_PAIR(6) | COLOR_PAIR(7) | COLOR_PAIR(8) | COLOR_PAIR(9) | COLOR_PAIR(10) | COLOR_PAIR(11));
                ////Desactiver tous les pairs de couleurs.
            }
        }
        attron(COLOR_PAIR(6)); //Afficher le texte suivant avec le paire de couleurs 6.
        printw("|\n");
        printw("---------------------\n");
        attroff(COLOR_PAIR(6)); //Desactiver le paire de couleurs 6.
    }
    attron(COLOR_PAIR(3)); //Afficher le texte suivant avec le paire de couleurs 3.
    printw("\nCommandes : Flèche haut / z, Flèche bas / s , Flèche gauche /q ,\nFlèche droite / d, n (nouvelle partie), a (quitter)\n");
    attroff(COLOR_PAIR(3)); //Desactiver le paire de couleurs 3.
    attron(COLOR_PAIR(2));//Afficher le texte suivant avec le paire de couleurs 2.
    printw("\nScore : %d\n", score);
    attroff(COLOR_PAIR(2));//Desactiver le paire de couleurs 2.
    refresh(); //Mise a jour de l'ecran.
}

Plateau déplacementGauche(Plateau plateau){
    for (int i = 0; i < 4; i++){
        for (int j = 1; j < 4; j++){ //Parcourir tous les cases du tableau.
            if (plateau[i][j]!=0){ //Trouver une case qui n'est pas vide.
                int indice = j; 
                while (indice > 0 && (plateau[i][indice-1] == 0 || plateau[i][indice] == plateau[i][indice-1])){
                    if (plateau[i][indice-1] == 0){ //Si la tuile a la gauche est vide,
                        plateau[i][indice-1] = plateau[i][indice]; //on deplace notre tuile vers la gauche.
                        plateau[i][indice] = 0; //Notre tuile devient = 0
                    }else if (plateau[i][indice-1] == plateau[i][indice]){
                        plateau[i][indice-1] *= 2; //Si la tuile a la gauche est egale a notre tuile principale, on la multiplie par 2.
                        score += plateau[i][indice-1];
                        plateau[i][indice] = 0; //Notre tuile devient = 0
                        break; //Arreter le deplacement lorsque toutes les tuiles se sont deplacées.
                    }
                    indice--; //Aller a la gauche pour voir si on peut continuer a deplacer la tuile.
                }
            }
        }
    }
    return plateau;
} 


Plateau déplacementDroite(Plateau plateau){
    for (int i = 0; i < 4; i++){
        for (int j = 2; j >= 0; j--){ //Parcourir tous les cases du tableau.
            if (plateau[i][j]!=0){ //Trouver une case qui n'est pas vide.
                int indice = j;
                while (indice < 3 && (plateau[i][indice+1] == 0 || plateau[i][indice] == plateau[i][indice+1])){
                    if (plateau[i][indice+1] == 0){ //Si la tuile a la droite est vide,
                        plateau[i][indice+1] = plateau[i][indice]; //on deplace notre tuile vers la gauche.
                        plateau[i][indice] = 0; //Notre tuile devient = 0
                    }else if (plateau[i][indice+1] == plateau[i][indice]){
                        plateau[i][indice+1] *= 2;  //Si la tuile a la droite est egale a notre tuile principale, on la multiplie par 2.
                        score += plateau[i][indice+1];
                        plateau[i][indice] = 0; //Notre tuile devient = 0
                        break; //Arreter le deplacement lorsque toutes les tuiles se sont deplacées.
                    }
                    indice++; //Aller a la droite pour voir si on peut continuer a deplacer la tuile.
                }
            }
        }
    }
    return plateau;
} 


Plateau déplacementBas(Plateau plateau){
    for (int j= 0; j < 4; j++){
        for (int i = 2; i >= 0; i--){ //Parcourir tous les cases du tableau.
            if (plateau[i][j]!=0){ //Trouver une case qui n'est pas vide.
                int indice = i;
                while (indice < 3 && (plateau[indice+1][j] == 0 || plateau[indice+1][j] == plateau[indice][j])){
                    if (plateau[indice+1][j] == 0){ //Si la tuile au dessous est vide,
                        plateau[indice+1][j] = plateau[indice][j]; //on deplace notre tuile vers le bas.
                        plateau[indice][j] = 0; //Notre tuile devient = 0
                    }else if (plateau[indice+1][j] == plateau[indice][j]){
                        plateau[indice+1][j] *= 2; //Si la tuile au dessous est egale a notre tuile principale, on la multiplie par 2.
                        score += plateau[indice+1][j];
                        plateau[indice][j] = 0; //Notre tuile devient = 0
                        break; //Arreter le deplacement lorsque toutes les tuiles se sont deplacées.
                    }
                    indice++; //Aller au dessous pour voir si on peut continuer a deplacer la tuile.
                }
            }
        }
    }
    return plateau;
} 


Plateau déplacementHaut(Plateau plateau){
    for (int j= 0; j < 4; j++){
        for (int i = 1; i < 4; i++){ //Parcourir tous les cases du tableau.
            if (plateau[i][j]!=0){ //Trouver une case qui n'est pas vide.
                int indice = i;
                while (indice > 0 && (plateau[indice-1][j] == 0 || plateau[indice-1][j] == plateau[indice][j])){
                    if (plateau[indice-1][j] == 0){ //Si la tuile au dessus est vide,
                        plateau[indice-1][j] = plateau[indice][j]; //on deplace notre tuile vers le haut.
                        plateau[indice][j] = 0; //Notre tuile devient = 0
                    }else if (plateau[indice-1][j] == plateau[indice][j]){
                        plateau[indice-1][j] *= 2; //Si la tuile au dessus est egale a notre tuile principale, on la multiplie par 2.
                        score += plateau[indice-1][j];
                        plateau[indice][j] = 0; //Notre tuile devient = 0
                        break; //Arreter le deplacement lorsque toutes les tuiles se sont deplacées.
                    }
                    indice--; //Aller au dessus pour voir si on peut continuer a deplacer la tuile.
                }
            }
        }
    }
    return plateau;
} 


Plateau déplacement(Plateau plateau, char commande){ //Fonction pour gérer les déplacements.
    if (commande == 'z') { 
        plateau = déplacementHaut(plateau);
    }else if (commande == 's'){
        plateau = déplacementBas(plateau);
    }else if (commande == 'q'){
        plateau = déplacementGauche(plateau);
    }else if (commande == 'd'){
        plateau = déplacementDroite(plateau);
    }else{
        cout << "Déplacement impossible!";
    }
    return plateau;
}


bool estGagnant(Plateau plateau){ //Vérifie si une des tuiles == 2048, si oui return true, sinon, return false.
    for (int i=0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (plateau[i][j] == 2048){
                clear();
                printw("Bravo! Vous avez gagné\n");
                napms(5000); //Afficher le message précedent pendant 5 secondes.
                return true;
            }
        }
    }
    return false; //Aucune case est == 2048 donc le joueur n'a pas encore gagné, return false.
}


bool estTerminé(Plateau plateau){ //Vérifie si il y a encore des mouvements possibles sur le plateau.
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (plateau[i][j] == 0) return false; //Si il y a une case vide, le jeu n'est pas terminé donc return false.
            if (j < 3 && plateau[i][j] == plateau[i][j+1]) return false; //Vérifie si il y a une fusion possible a la droite.
            if (i < 3 && plateau[i][j] == plateau[i+1][j]) return false; //Vérifie si il y a une fusion possible en dessous.
        }
    }
    return true; //Aucune case vide ni fusion possible, le jeu est terminé donc return true.
}