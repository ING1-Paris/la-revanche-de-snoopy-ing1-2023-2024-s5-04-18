#include <stdio.h>
#include <windows.h>
#include <unistd.h>


#include <conio.h>
void effacerEcran() {
    system("cls");
}

int xmin = 1; // Modification des limites pour prendre en compte les bords
int ymin = 1;
int xmax = 20;
int ymax = 10;

// Position de départ du personnage
int x_personnage = 10;
int y_personnage = 5;

// Position de départ de la boule
int x_boule = 1;
int y_boule = 1;

int dx_boule = 1; // Déplacement de la boule en x
int dy_boule = 1; // Déplacement de la boule en y

int largeur_map = 20;
int hauteur_map = 10;

// Fonction pour déplacer le personnage vers le haut
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

    do {
        effacerEcran();
        // Afficher le terrain, le personnage et la boule
        printf("||*|*|*|*|*|*|*|*|*|*|*|*|\n");
        for (int i = 1; i <= hauteur_map; ++i) {
            printf("|*|");
            for (int j = 1; j <= largeur_map; ++j) {
                if (i == y_personnage && j == x_personnage) {
                    printf("%c", personnage);
                } else if (i == y_boule && j == x_boule) {
                    printf("%c", boule);
                } else {
                    printf(" ");
                }
            }
            printf("|*|\n");
        }
        printf("||*|*|*|*|*|*|*|*|*|*|*|*|\n");

        // Mettre à jour la position de la boule en diagonale
        x_boule += dx_boule;
        y_boule += dy_boule;

        // Gestion des rebonds de la boule sur les bords de la carte
        if (x_boule >= largeur_map || x_boule <= 1) {
            dx_boule = -dx_boule;
        }
        if (y_boule >= hauteur_map || y_boule <= 1) {
            dy_boule = -dy_boule;
        }

        // Déplacer le personnage en fonction de la touche appuyée
        if (_kbhit()) {
            char touche = _getch();
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
            }
        }

        // Pause pour ralentir le mouvement
        usleep(100000); // Attendre 100 000 microsecondes (0,1 seconde)
    } while (x_personnage != x_boule || y_personnage != y_boule);
    printf("GAME OVER");

    return 0;
}
