#include <stdio.h>
#include <conio.h>
#include <WINDOWS.H>




int xmin = 1; // Modification des limites pour prendre en compte les bords
int ymin = 1;
int xmax = 20;
int ymax = 10;

// Position de depart du personnage
int x_personnage = 10;
int y_personnage = 5;

// position de depart de la boule
int x_boule = 1;
int y_boule = 10;

// Fonction pour deplacer le personnage vers le haut
void deplacer_haut() {
    if (y_personnage > ymin) {
        y_personnage--;
    }
}

// Fonction pour déplacer le personnage vers le bas
void deplacer_bas() {
    if (y_personnage < ymax) {
        y_personnage++;
    }
}

// Fonction pour déplacer le personnage vers la gauche
void deplacer_gauche() {
    if (x_personnage > xmin) {
        x_personnage--;
    }
}

// Fonction pour déplacer le personnage vers la droite
void deplacer_droite() {
    if (x_personnage < xmax) {
        x_personnage++;
    }
}

int main() {
    char personnage = 'S';
    char boule = 'C';

    while (1) {

        // Afficher le terrain et le personnage immobile
        printf("||*|*|*|*|*|*|*|*|*|*|*|*|\n");
        for (int i = 1; i <= 10; ++i) {
            printf("|*|");
            for (int j = 1; j <= 20; ++j) {
                if (i == y_personnage && j == x_personnage) {
                    printf("%c", personnage);
                } else {
                    if (i == y_boule && j == x_personnage) {
                        printf("%c", boule);
                    } else {
                        printf(" ");
                    }
                }
            }
            printf("|*|\n");
        }
        printf("||*|*|*|*|*|*|*|*|*|*|*|*|\n");
// le personnage reste immobile jusqu a qu une touche soit pressé
        // Attendre l'entrée de l'utilisateur (sans nécessiter la touche Entrée)
        char touche = _getch();

        // Déplacer le personnage en fonction de la touche appuyée
        switch (touche) {
            case 'z':
                deplacer_haut();
                break;
            case 's':
                deplacer_bas();
                break;
            case 'q':
                deplacer_gauche();
                break;
            case 'd':
                deplacer_droite();
                break;
            default:
                break;
        }
    }
}