#include <stdio.h>
#include <windows.h>
#include <unistd.h>
#include <time.h>
#include <conio.h>

void effacerEcran() {
    system("cls");
}

int xmin = 1;
int ymin = 1;
int xmax = 20;
int ymax = 10;

int x_personnage = 10;
int y_personnage = 5;

int x_boule = 1;
int y_boule = 1;

int dx_boule = 1;
int dy_boule = 1;

int x_oiseau1 = 1;
int y_oiseau1 = 1;

int x_oiseau2 = 20;
int y_oiseau2 = 1;

int x_oiseau3 = 1;
int y_oiseau3 = 10;

int x_oiseau4 = 20;
int y_oiseau4 = 10;

int tempsTotal = 120;
int tempsRestant;
clock_t debut = 0;

void miseAJourTemps() {
    tempsRestant = tempsTotal - (clock() - debut) / CLOCKS_PER_SEC;
}

void afficher_terrain() {
    printf("||*|*|*|*|*|*|*|*|*|*|*|*|\n");
    for (int i = 1; i <= 10; ++i) {
        printf("|*|");
        for (int j = 1; j <= 20; ++j) {
            if (i == y_personnage && j == x_personnage) {
                printf("S");
            } else if (i == y_boule && j == x_boule) {
                printf("O");
            } else if (i == y_oiseau1 && j == x_oiseau1) {
                printf("1");
            } else if (i == y_oiseau2 && j == x_oiseau2) {
                printf("2");
            } else {
                printf(" ");
            }
        }
        printf("|*|\n");
    }
    printf("||*|*|*|*|*|*|*|*|*|*|*|*|\n");
}

int main() {
    tempsRestant = tempsTotal;
    debut = clock();

    do {
        if ((clock() - debut) / CLOCKS_PER_SEC % 1 == 0) {
            miseAJourTemps();
        }

        effacerEcran();
        afficher_terrain();

        x_boule += dx_boule;
        y_boule += dy_boule;

        if (x_boule >= xmax || x_boule <= xmin) {
            dx_boule = -dx_boule;
        }
        if (y_boule >= ymax || y_boule <= ymin) {
            dy_boule = -dy_boule;
        }

        if (_kbhit()) {
            char touche = _getch();
            switch (touche) {
                case 'z':
                    if (y_personnage > ymin) y_personnage--;
                    break;
                case 's':
                    if (y_personnage < ymax) y_personnage++;
                    break;
                case 'q':
                    if (x_personnage > xmin) x_personnage--;
                    break;
                case 'd':
                    if (x_personnage < xmax) x_personnage++;
                    break;
            }
        }
        printf("Temps restant : %d secondes\n", tempsRestant);
        usleep(100000);
    } while (x_personnage != x_boule || y_personnage != y_boule && tempsRestant > 0);

    printf("GAME OVER");
    sleep(5);
    return 0;
}
