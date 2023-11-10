#include <stdio.h>
#include <conio.h>
#include <WINDOWS.H>
#define NOMBRE_BLOCS 2

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

// position de depart de la boule
int x_boule = 1;
int y_boule = 10;


int blocs[NOMBRE_BLOCS][2] = {{8, 5}, {12, 5}};// blocs et leurs positions 
int blocs_deplaces[NOMBRE_BLOCS] = {0};// Tableau pour suivre les blocs déplacés
// Fonction pour deplacer le personnage vers le haut
void deplacer_haut() {
    if (y_personnage > ymin) {
        // Empêcher le personnage de traverser les blocs
        for (int i = 0; i < NOMBRE_BLOCS; i++) {
            if (x_personnage == blocs[i][0] && y_personnage - 1 == blocs[i][1]) {
                return;
            }
        }
        y_personnage--;
    }
}

// Fonction pour déplacer le personnage vers le bas
void deplacer_bas() {
    if (y_personnage < ymax) {
        for (int i = 0; i < NOMBRE_BLOCS; i++) {
            if (x_personnage == blocs[i][0] && y_personnage + 1 == blocs[i][1]) {
                return;
            }
        }
        y_personnage++;
    }
}

// Fonction pour déplacer le personnage vers la gauche
void deplacer_gauche() {
    if (x_personnage > xmin) {
        for (int i = 0; i < NOMBRE_BLOCS; i++) {
            if (x_personnage - 1 == blocs[i][0] && y_personnage == blocs[i][1]) {
                return;
            }
        }
        x_personnage--;
    }
}

// Fonction pour déplacer le personnage vers la droite
void deplacer_droite() {
    if (x_personnage < xmax) {
        for (int i = 0; i < NOMBRE_BLOCS; i++) {
            if (x_personnage + 1 == blocs[i][0] && y_personnage == blocs[i][1]) {
                return;
            }
        }
        x_personnage++;
    }
}
void afficher_terrain() {
    printf("||*|*|*|*|*|*|*|*|*|*|*|*|\n");
    for (int i = 1; i <= 10; ++i) {
        printf("|*|");
        for (int j = 1; j <= 20; ++j) {
            if (i == y_personnage && j == x_personnage) {
                printf("S"); // Affiche le personnage (S)
            } else {
                int bloc_present = 0;
                for (int k = 0; k < NOMBRE_BLOCS; k++) {
                    if (blocs[k][0] == j && blocs[k][1] == i) {
                        printf("B"); // Affiche le bloc (B)
                        bloc_present = 1;
                        break;
                    }
                }
                if (bloc_present == 0) {
                    printf(" ");
                }
            }
        }
        printf("|*|\n");
    }
    printf("||*|*|*|*|*|*|*|*|*|*|*|*|\n");
}
void pousser_bloc() {
    for (int i = 0; i < NOMBRE_BLOCS; i++) {
        if (blocs_deplaces[i] == 0) {
            int dx = 0, dy = 0;
            switch (1) {
                case 1:
                    if (x_personnage + 1 == blocs[i][0] && y_personnage == blocs[i][1]) {
                        dx = 1;
                        break;
                    }
                case 2:
                    if (x_personnage - 1 == blocs[i][0] && y_personnage == blocs[i][1]) {
                        dx = -1;
                        break;
                    }
                case 3:
                    if (x_personnage == blocs[i][0] && y_personnage + 1 == blocs[i][1]) {
                        dy = 1;
                        break;
                    }
                case 4:
                    if (x_personnage == blocs[i][0] && y_personnage - 1 == blocs[i][1]) {
                        dy = -1;
                        break;
                    }
                default:
                    break;
            }

            int new_x = blocs[i][0] + dx;
            int new_y = blocs[i][1] + dy;

            if (new_x >= xmin && new_x <= xmax && new_y >= ymin && new_y <= ymax) {
                int can_push = 1;

                for (int j = 0; j < NOMBRE_BLOCS; j++) {
                    if (j != i && blocs[j][0] == new_x && blocs[j][1] == new_y) {
                        can_push = 0;
                        break;
                    }
                }

                if (can_push) {
                    blocs[i][0] = new_x;
                    blocs[i][1] = new_y;
                    blocs_deplaces[i] = 1; // Marquer le bloc comme déplacé
                    return; // Sortir de la fonction après avoir déplacé un bloc
                }
            }
        }
    }
}

int main() {
    char personnage = 'S';
    char boule = 'C';

    do {
        effacerEcran();
        // Afficher le terrain et le personnage immobile
        afficher_terrain();

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
            case 'p':
                pousser_bloc();
                break;
            default:
                break;
        }
    } while (x_personnage != x_boule && y_personnage!=x_boule);
    printf("GAME OVER");
}

void afficherJauge(int tempsRestant) {
    int i;
    printf("[");
    for (i = 0; i < tempsRestant; ++i) {
        printf("*");
    }
    for (i = tempsRestant; i < 120; ++i) {
        printf(" ");
    }
    printf("]\n");
}

int main() {    
    int tempsTotal = 120;
    int tempsRestant = tempsTotal;


    while (tempsRestant > 0)
    {
        printf("\rSecondes restantes : %d\n", tempsRestant);
        afficherJauge(tempsRestant);
        tempsRestant--;
        Sleep(1000); //patienter 1 000 ms (donc une seconde) dans chaque exécution de la boucle
        system("cls");
    }

    printf("Temps ecoule !\n");


    return 0;
}

