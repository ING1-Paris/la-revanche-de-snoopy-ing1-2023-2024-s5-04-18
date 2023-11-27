#include <stdio.h>
#include <windows.h>
#include <unistd.h>
//nombre de bloc
#define NOMBRE_BLOCS 16
#include <time.h>
#include <conio.h>
void effacerEcran() {
    system("cls");//supprime tout dans la console
}

int code_secret;// code secret cache dans le nom

int xmin = 1; // minnimum du nombre de colonnes de la map
int ymin = 1;// minnimum de nombre de lignes de la map
int xmax = 20;// maximum du nombre de colonnes de la map
int ymax = 10;// maximum du nombre de lignes



// position de depart du personnage, au mileu du terrain
int x_personnage = 10;
int y_personnage = 5;


int blocs[NOMBRE_BLOCS][16] = {{8, 3}, {9, 3}, {10, 3}, {11, 3}, {12, 3}, {12, 4}, {12, 5}, {12, 6}, {12, 7}, {11, 7}, {10, 7},{9, 7}, {8, 7},{8, 6}, {8, 5}, {8, 4} };
int blocs_deplaces[NOMBRE_BLOCS] = {0};


// position de depart de la boule
int x_boule = 1;
int y_boule = 1;

int dx_boule = 1; // deplacement de la boule en x
int dy_boule = 1; // deplacement de la boule en y
// permet de faire avancer la boule en diagonale



// position des oiseaux aux quatre coins de la map
int x_oiseau1 = 1;
int y_oiseau1 = 1;

int x_oiseau2 = 20;
int y_oiseau2 = 1;

int x_oiseau3 = 1;
int y_oiseau3 = 10;

int x_oiseau4 = 20;
int y_oiseau4 = 10;

//nombre d'oiseau attrape
int oiseau_caught=0;
int choix_menu;




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
// Fonction pour deplacer le personnage vers la gauche
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

// Fonction pour deplacer le personnage vers la droite
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


//affichage du terrain
void afficher_terrain() {
    char tableau[10][20];
    printf("||*|*|*|*|*|*|*|*|*|*|*|*|\n"); // premiere ligne de la map
    for (int i = 1; i <= 10; ++i) {
        printf("|*|");//premier mur de cahque ligne
        for (int j = 1; j <= 20; ++j) {
            if (i == y_personnage && j == x_personnage) {
                printf("S");//afficher snoopy aux coordonnées voulus
            } else if (i == y_boule && j == x_boule) {
                printf("O");//afficher la boule aux coordonnées voulus
            } else if(i == y_oiseau1 && j == x_oiseau1){
                printf("1");//afficher les 4 oiseaux
            }else if(i == y_oiseau2 && j == x_oiseau2){
                printf("2");}
            else if ( i == y_oiseau3 && j == x_oiseau3) {
                printf("3");
            }else if (i == y_oiseau4 && j == x_oiseau4 ) {
                printf("4");}
            else{
                int bloc_present = 0;//afficher les blocs
                for (int k = 0; k < NOMBRE_BLOCS; k++) {
                    if (blocs[k][0] == j && blocs[k][1] == i) {
                        printf("B");
                        bloc_present = 1;
                        break;
                    }
                }
                if (bloc_present == 0) {
                    printf(" ");//mettre des espaces la ou il n'y a pas de blocs
                }
            }

        }
        printf("|*|\n");// dernier mur de chaque ligne
    }
    printf("||*|*|*|*|*|*|*|*|*|*|*|*|\n");
}
void pousser_bloc() {//programme pour pousser les blocs
    for (int i = 0; i < NOMBRE_BLOCS; i++) {
        if (blocs_deplaces[i] == 0) {
            int dx = 0, dy = 0;

            //pousser le bloc d'une case en fonction de la ou ce trouve Snoopy
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

            // determiner si le bloc peut etre poussr
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
                    blocs_deplaces[i] = 1; // Marquer le bloc comme deplace
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
void menujeu(){
    do {
        system("cls");
        printf("                                                                                               ****    ****      \n");
        printf("                                                                                                *  *  *  *       \n");
        printf("                                          *******  ********  ****  ********  ********  *******   *  **  *        \n");
        printf("                                          *  *     *  *   *  *  *  * *  * *  * *  * *  *  3  *     ****          \n");
        printf("                                          *  *     *  * *  * *  *  * * 1* *  * * 2* *  *  ****     *  *          \n");
        printf("                                          *******  *  *  *  **  *  * *  * *  * *  * *  *  *        *  *          \n");
        printf("                                             *  *  ****   *******  ********  ********  *  *        ****          \n");
        printf("                                             *  *                                      ****                        \n");
        printf("                                          *******                                                              \n");

        printf("                                                    _________________________________\n");
        printf("                                                   |                                 | \n");
        printf("                                                   | Veuillez choisir une action :   | \n");
        printf("                                                   | 1) Nouvelle partie              | \n");
        printf("                                                   | 2) Afficher les regles          | \n");
        printf("                                                   | 3) Charger une partie           | \n");
        printf("                                                   |                                 | \n");
        printf("                                                   |_________________________________|\n\n\n\n\n");
        printf(" __________________\n");
        printf("| Auteurs :        |\n| ARMAND RATHERY   |\n| LORENZO ENGLENDER|\n| ELIOT PASCHAL    |\n");
        printf("|__________________|\n");
        scanf("%d", &choix_menu);

    } while (choix_menu<1 || choix_menu>4);
}
void afficherregle() {
    printf(" _________________________________________________\n");
    printf("| Voici les regles de la revanche de Snoopy       |\n");
    printf("|_________________________________________________|\n");

    printf("Bienvenue dans le jeu La Revanche de Snoopy !!!\n");
    printf("Les 12 meilleurs amis de Snoopy se sont faits kidnapper lors du dernier Salon de l'Agriculture et sont maintenant enfermes dans une cage.\n\n");
    printf("Heureusement, Snoopy est la pour les sauver.\n");
    printf("Apres un long periple Snoopy à enfin reussit a  s'introduire dans la premiere cage, mais cette derniere est plongee dans le noir complet et est gardee par une boule.\n");
    printf("Ta mission, si tu l'acceptes, est de diriger Snoopy à l aide de ton ordinateur pour qu il sauve ses amis.\n\n\n");

    printf("Les regles sont simples : tu peux indiquer a Snoopy de se deplacer avec les touches suivantes :\n");

    printf("-Z pour aller vers le haut\n");
    printf("-Q pour aller vers la gauche\n");
    printf("-S pour aller vers le bas\n");
    printf("-D pour aller vers la droite\n\n");

    printf("Ton but est donc de recuperer les oiseaux disperses dans la map.\n");
    printf("Cependant, la tache n'est pas si facile. Il y a un compte a rebours de 120 secondes qui te force à devoir te depecher !\n");
    printf("Si le temps est ecoule, le gardien viendra et sortira Snoopy de la cage.\n");

    printf("Si Snoopy se fait attraper 3 fois, il sera fait prisonnier et la partie sera perdue...\n");
    printf("Si Snoopy se prend trois fois la boule, la partie sera perdue...\n");

    printf("Attention, il y a aussi des blocs qui peuvent bloquer le passage jusqu aux oiseaux, mais grace à la force phenomenale de Snoopy, tu peux deplacer chaque bloc UNE seule fois grace a la touche P\n");
    printf("Bonne chance et que la force soit avec toi \n\n\n");
    printf("petit indice le premier code se trouve dans le titre du jeu sur le menu :)");
    printf("appuyer sur une touche pour quitter les regles");

}














int main() {
   menujeu();
    switch (choix_menu) {
        case 1:
            do {

                printf("rentrez le code secret pour acceder a la partie 1");
                scanf("%d", &code_secret);
            } while (code_secret!=123);


            tempsRestant = tempsTotal;
            debut = clock(); // Commencez le compte à rebours au debut du programme

            do {

                effacerEcran();
                // afficher le terrain, le personnage, la boule et les oiseaux
                afficher_terrain();
                if (x_personnage == x_oiseau1 && y_personnage == y_oiseau1) { // si snooppy attrape un oiseau
                    y_oiseau1--; // alors l'oiseau disparait
                    oiseau_caught++;// nombre d'oiseau attrapé augmente
                    printf("Bravo ! vous avez attrape %d oiseau(x)\n", oiseau_caught);
                    sleep(2);// pause de deux secondes pour feciliter l'utilisateur
                }
                if (x_personnage == x_oiseau2 && y_personnage == y_oiseau2) {
                    y_oiseau2--;//l oiseau disparait dans le mur du haut, il aurait pu disparaitre dans le mur sur le cote en remplacant par x_oiseau2++
                    oiseau_caught++;
                    printf("Bravo! vous avez attrape %d oiseau(x)\n", oiseau_caught);
                    sleep(2);
                }
                if (x_personnage == x_oiseau3 && y_personnage == y_oiseau3) {
                    y_oiseau3++;//l'oiseau disparait dans le mur du bas
                    oiseau_caught++;
                    printf("Bravo! vous avez attrape %d oiseau(x)\n", oiseau_caught);
                    sleep(2);
                }
                if (x_personnage == x_oiseau4 && y_personnage == y_oiseau4) {
                    y_oiseau4++;// l'oiseau disparait dans la ligne du bas
                    oiseau_caught++;
                    printf("Bravo! vous avez attrape %d oiseau(x)\n", oiseau_caught);
                    sleep(2);
                }
                if (oiseau_caught == 4) {
                    printf("Bravo! vous avez gagne\n");// si l'utilisateur attrape 4 oiseaux alors il a gagne sinon el jeu continue
                } else {// on place le else ici pour que tout le jeu s'arrete lorsque l on gagne , lr temps la boule et le personnage
                    if ((clock() - debut) / CLOCKS_PER_SEC % 1 == 0) {
                        miseAJourTemps();
                    }

                    // mettre a jour la position de la boule pour qu elle avance en diagonale
                    x_boule += dx_boule;
                    y_boule += dy_boule;

                    // fonction pour que la boule rebondisse sur les murs et donc qu elle ne sorte pas de la map
                    if (x_boule >= xmax || x_boule <= 1) {
                        dx_boule = -dx_boule;
                    }
                    if (y_boule >= ymax || y_boule <= 1) {
                        dy_boule = -dy_boule;
                    }

                    // deplacer le personnage en fonction de la touche appuyée
                    if (_kbhit()) {//indications de si une touche à été frappe
                        char touche = _getch();//attendre la frappe d'un caractere au clavier puis le lire
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
                            case 'p'://deplacer le bloc
                                memset(blocs_deplaces, 0, sizeof(blocs_deplaces));
                                pousser_bloc();
                                break;
                            case 't':
                            getch();
                            break;
                        }
                    }
                }
                printf("Temps restant : %d secondes\n", tempsRestant);
                // pause pour ralentir ou accelerer le mouvement entre chaque position de la balle
                usleep(100000); // pause de 0,1 seconde
            } while (x_personnage != x_boule || y_personnage != y_boule && tempsRestant > 0);
// continuer le jeu jusqu'a ce que le personnage rencontre la balle ou que le temps soit ecoule
            printf("GAME OVER");
            sleep(2000);// afficher game over pendant 2 secondes
            break;


        case 2:
       afficherregle();
            if (getch()) {
                menujeu();
                switch (choix_menu) {
                    case 1:
                        do {

                            printf("rentrez le code secret pour acceder a la partie 1");
                            scanf("%d", &code_secret);
                        } while (code_secret!=123);


                        tempsRestant = tempsTotal;
                        debut = clock(); // Commencez le compte à rebours au debut du programme

                        do {


                            effacerEcran();
                            // afficher le terrain, le personnage, la boule et les oiseaux
                            afficher_terrain();
                            if (x_personnage == x_oiseau1 && y_personnage == y_oiseau1) { // si snooppy attrape un oiseau
                                y_oiseau1--; // alors l'oiseau disparait
                                oiseau_caught++;// nombre d'oiseau attrapé augmente
                                printf("Bravo ! vous avez attrape %d oiseau(x)\n", oiseau_caught);
                                sleep(2);// pause de deux secondes pour feciliter l'utilisateur
                            }
                            if (x_personnage == x_oiseau2 && y_personnage == y_oiseau2) {
                                y_oiseau2--;//l oiseau disparait dans le mur du haut, il aurait pu disparaitre dans le mur sur le cote en remplacant par x_oiseau2++
                                oiseau_caught++;
                                printf("Bravo! vous avez attrape %d oiseau(x)\n", oiseau_caught);
                                sleep(2);
                            }
                            if (x_personnage == x_oiseau3 && y_personnage == y_oiseau3) {
                                y_oiseau3++;//l'oiseau disparait dans le mur du bas
                                oiseau_caught++;
                                printf("Bravo! vous avez attrape %d oiseau(x)\n", oiseau_caught);
                                sleep(2);
                            }
                            if (x_personnage == x_oiseau4 && y_personnage == y_oiseau4) {
                                y_oiseau4++;// l'oiseau disparait dans la ligne du bas
                                oiseau_caught++;
                                printf("Bravo! vous avez attrape %d oiseau(x)\n", oiseau_caught);
                                sleep(2);
                            }
                            if (oiseau_caught == 4) {
                                printf("Bravo! vous avez gagne\n");// si l'utilisateur attrape 4 oiseaux alors il a gagne sinon el jeu continue
                            } else {// on place le else ici pour que tout le jeu s'arrete lorsque l on gagne , lr temps la boule et le personnage
                                if ((clock() - debut) / CLOCKS_PER_SEC % 1 == 0) {
                                    miseAJourTemps();
                                }

                                // mettre a jour la position de la boule pour qu elle avance en diagonale
                                x_boule += dx_boule;
                                y_boule += dy_boule;

                                // fonction pour que la boule rebondisse sur les murs et donc qu elle ne sorte pas de la map
                                if (x_boule >= xmax || x_boule <= 1) {
                                    dx_boule = -dx_boule;
                                }
                                if (y_boule >= ymax || y_boule <= 1) {
                                    dy_boule = -dy_boule;
                                }

                                // deplacer le personnage en fonction de la touche appuyée
                                if (_kbhit()) {//indications de si une touche à été frappe
                                    char touche = _getch();//attendre la frappe d'un caractere au clavier puis le lire
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
                                        case 'p'://deplacer le bloc
                                            memset(blocs_deplaces, 0, sizeof(blocs_deplaces));
                                            pousser_bloc();
                                            break;
                                        case 't': // mettre en pause 
                                            getch();
                                            break;
                                    }
                                }
                            }
                            printf("Temps restant : %d secondes\n", tempsRestant);
                            // pause pour ralentir ou accelerer le mouvement entre chaque position de la balle
                            usleep(100000); // pause de 0,1 seconde
                        } while (x_personnage != x_boule || y_personnage != y_boule && tempsRestant > 0);
// continuer le jeu jusqu'a ce que le personnage rencontre la balle ou que le temps soit ecoule
                        printf("GAME OVER");
                        sleep(2000);// afficher game over pendant 2 secondes
                        break;


                    case 2:
                        afficherregle();
                        if (getch()) {
                            menujeu();







                        }
                        break;

                }








            }
            break;

    }

}
