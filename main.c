#include <stdio.h>
#include <conio.h>
#include <WINDOWS.H>


// Fonction pour effacer l'écran de la console c quoi ca ??
void effacerEcran() {
    system("cls");
}

int xmin = 1; // Modification des limites pour prendre en compte les bords
int ymin = 1;
int xmax = 20;
int ymax = 10;

// Position de depart du personnage
int x_personnage = 5;
int y_personnage = 5;

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
    // Définir les limites de l'espace de jeu
    printf("|*|*|*|*|*|*|*|*|*|*|*|*|\n");
    for (int i = 1; i <= 10; ++i) {
        printf("|*|                  |*|\n");
    }
    printf("|*|*|*|*|*|*|*|*|*|*|*|*|");

    // Exemple d'utilisation, ?? a laisser ca ??
    deplacer_haut();
    deplacer_gauche();
    deplacer_bas();
    deplacer_droite();

    // Vérifier les nouvelles coordonnées du personnage ??a laisser ca ?
    printf("Nouvelles coordonnées : (%d, %d)\n", x_personnage, y_personnage);
    printf("Appuyez sur une touche pour quitter...\n");

    char personnage = 'S';

    while (1) {
        effacerEcran();

        // Afficher le terrain et le personnage
        printf("||*|*|*|*|*|*|*|*|*|*|*|*|\n");
        for (int i = 1; i <= 10; ++i) {
            printf("|*|");
            for (int j = 1; j <= 20; ++j) {
                if (i == y_personnage && j == x_personnage) {
                    printf("%c", personnage);
                } else {
                    printf(" ");
                }
            }
            printf("|*|\n");
        }
        printf("||*|*|*|*|*|*|*|*|*|*|*|*|");

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

    return 0;
}
