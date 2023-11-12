// https://koor.fr/C/ctime/clock.wp (forum pour le timer)//


#include <stdio.h>
#include <windows.h>
#include <unistd.h>
#define NOMBRE_BLOCS 16
#include <time.h>
#include <conio.h>
#include <string.h>
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


int blocs[NOMBRE_BLOCS][16] = {{8, 3}, {9, 3}, {10, 3}, {11, 3}, {12, 3}, {12, 4}, {12, 5}, {12, 6}, {12, 7}, {11, 7}, {10, 7},{9, 7}, {8, 7},{8, 6}, {8, 5}, {8, 4} };
int blocs_deplaces[NOMBRE_BLOCS] = {0};
// Position de départ de la boule
int x_boule = 1;
int y_boule = 1;

int dx_boule = 1; // Déplacement de la boule en x
int dy_boule = 1; // Déplacement de la boule en y


int x_oiseau1 = 1;
int y_oiseau1 = 1;

int x_oiseau2 = 20;
int y_oiseau2 = 1;

int x_oiseau3 = 1;
int y_oiseau3 = 10;

int x_oiseau4 = 20;
int y_oiseau4 = 10;

int oiseau_caught=0;



// Fonction pour déplacer le personnage vers le haut
void deplacer_haut() {
    if (y_personnage > ymin) {
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
                printf("S");
            } else if (i == y_boule && j == x_boule) {
                printf("O");
            } else if(i == y_oiseau1 && j == x_oiseau1){
                printf("1");
            }else if(i == y_oiseau2 && j == x_oiseau2){
                printf("2");}
                else if ( i == y_oiseau3 && j == x_oiseau3) {
                printf("3");
            }else if (i == y_oiseau4 && j == x_oiseau4 ) {
                printf("4");}
            else{
                int bloc_present = 0;
                for (int k = 0; k < NOMBRE_BLOCS; k++) {
                    if (blocs[k][0] == j && blocs[k][1] == i) {
                        printf("B");
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

            if (x_personnage + 1 == blocs[i][0] && y_personnage == blocs[i][1]) {
                dx = 1;
            } else if (x_personnage - 1 == blocs[i][0] && y_personnage == blocs[i][1]) {
                dx = -1;
            } else if (x_personnage == blocs[i][0] && y_personnage + 1 == blocs[i][1]) {
                dy = 1;
            } else if (x_personnage == blocs[i][0] && y_personnage - 1 == blocs[i][1]) {
                dy = -1;
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
                }
            }
        }
    }
}



int tempsTotal = 120;
int tempsRestant ;
clock_t debut = 0; // initialisez debut


void miseAJourTemps() {

    tempsRestant = tempsTotal - (clock() - debut) / CLOCKS_PER_SEC;
}

int main() {
  system("cls");
    printf("                                                                                            ****    ****      \n");
    printf("                                                                                             *  *  *  *       \n");
    printf("                                          *******  ********  ****  ********  ******* *******  *  **  *        \n");
    printf("                                          *  *     *  *   *  *  *  * *  * *  *     * *     *    ****          \n");
    printf("                                          *  *     *  * *  * *  *  * *  * *  *  **** *  ****    *  *          \n");
    printf("                                          *******  *  *  *  **  *  * *  * *  *  *    *  *       *  *          \n");
    printf("                                             *  *  ****   *******  ********  *  *    *  *       ****          \n");
    printf("                                             *  *                            ****    ****                     \n");
    printf("                                          *******                                                              \n");
    sleep(5);
    tempsRestant = tempsTotal;
    debut = clock(); // Commencez le compte à rebours au début du programme

    do {
        // Vérifiez le temps toutes les secondes


        effacerEcran();
        // Afficher le terrain, le personnage et la boule
        afficher_terrain();
         if(x_personnage==x_oiseau1 && y_personnage==y_oiseau1){
            y_oiseau1--;
            oiseau_caught++;
            printf("vous avez attrape %d oiseau\n",oiseau_caught);
        }
        if(x_personnage==x_oiseau2 && y_personnage==y_oiseau2){
            y_oiseau2--;
            oiseau_caught++;
            printf("vous avez attrape %d oiseau\n",oiseau_caught);
        }
        if(x_personnage==x_oiseau3 && y_personnage==y_oiseau3){
            y_oiseau3++;
            oiseau_caught++;
            printf("vous avez attrape %d oiseau\n",oiseau_caught);
        }
        if(x_personnage==x_oiseau4 && y_personnage==y_oiseau4){
            y_oiseau4++;
            oiseau_caught++;
            printf("vous avez attrape %d oiseau\n",oiseau_caught);
        }
        if(oiseau_caught==4){
            printf("vous avez gagne\n");
            }else {
            if ((clock() - debut) / CLOCKS_PER_SEC % 1 == 0) {
                miseAJourTemps();
            }

        // Mettre à jour la position de la boule en diagonale
        x_boule += dx_boule;
        y_boule += dy_boule;

        // Gestion des rebonds de la boule sur les bords de la carte
        if (x_boule >= xmax || x_boule <= 1) {
            dx_boule = -dx_boule;
        }
        if (y_boule >= ymax || y_boule <= 1) {
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
                case 'p':
                    memset(blocs_deplaces, 0, sizeof(blocs_deplaces));
                    pousser_bloc();
                    break;
            }
        }
        }
        printf("Temps restant : %d secondes\n", tempsRestant);
        // Pause pour ralentir le mouvement
        usleep(100000); // Attendre 100 000 microsecondes (0,1 seconde)
    } while (x_personnage != x_boule || y_personnage != y_boule && tempsRestant > 0);

    printf("GAME OVER");
    sleep(2000);
    return 0;
}
