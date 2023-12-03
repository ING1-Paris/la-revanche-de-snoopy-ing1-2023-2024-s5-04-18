#include <stdio.h>
#include <windows.h>
#include <unistd.h>
//nombre de bloc
#define NOMBRE_BLOCS 16
#include <time.h>
#include <conio.h>


// bloc piege a mettre dans le case p, tu choisis les coordonnes du bloc cassable
if (x_personnage==9 && y_personnage == 2 ||x_personnage==9 && y_personnage == 4 || x_personnage==8 && y_personnage == 3 || x_personnage==10 && y_personnage == 3) {
                            printf("vous etes tombe sur un bloc piege, vous perdez une vie");
                            tempsAvantLaPause = clock();
                            sleep(2);
                            debut += clock() - tempsAvantLaPause;
                            if (viesnoopy>0){
                                viesnoopy= viesnoopy-1;
                            }else if (viesnoopy==0){
                                system("cls");
                                printf("  ***   *****  *   *  *****\n");
                                printf(" *      *   *  ** **  *    \n");
                                printf(" *  **  *****  * * *  **** \n");
                                printf(" *   *  *   *  *   *  *    \n");
                                printf("  ***   *   *  *   *  *****\n");

                                printf(" ***  *         *  *****  ****\n");
                                printf("*   *  *       *   *      *   *\n");
                                printf("*   *   *     *    ****   ****\n");
                                printf("*   *    *   *     *      *  *\n");
                                printf(" ***       *       *****  *   *\n");;
                                printf("appuyer sur 1 pour revenir au menu");
                                scanf("%d", &touchepourquit);
                                reinitialiser_jeu();
                            }
                            case1();

                        }

// bloc bonus a mettre dans case p, tu choisis les coordonnes du bloc
if(x_personnage==7 && y_personnage == 5 ||x_personnage==8 && y_personnage == 6 || x_personnage==8 && y_personnage == 4 || x_personnage==9 && y_personnage == 5) {
                    if (viesnoopy < 3) {
                        printf(" vous avez declenché un bloc bonus, vous gagne une vie sauf si vous en avez deja 3");
                        tempsAvantLaPause = clock();
                        sleep(2);
                        debut += clock() - tempsAvantLaPause;
                        viesnoopy = viesnoopy + 1;
                    } else
                        (printf(" vous avez declenche un bloc bonus, vous gagne une vie sauf si vous en avez deja 3"));
                    tempsAvantLaPause = clock();
                    sleep(2);
                    debut += clock() - tempsAvantLaPause;
                }




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


int blocs[NOMBRE_BLOCS][3] = { {9, 3, 0}, {10, 3, 0}, {11, 3, 0},  {12, 4, 0}, {12, 5, 0}, {12, 6, 0},  {11, 7, 0}, {10, 7, 0},{9, 7, 0}, {8, 6, 0}, {8, 5, 0}, {8, 4, 0} };
int blocs_deplaces[NOMBRE_BLOCS] = {0};
int blocs_initiaux[NOMBRE_BLOCS][2];

typedef struct {
    int x;
    int y;
    int deplace;
} BlocDeplace;
BlocDeplace blocs_deplaces_info[NOMBRE_BLOCS];

void sauvegarder_positions_initiales() {
    for (int i = 0; i < NOMBRE_BLOCS; i++) {
        blocs_initiaux[i][0] = blocs[i][0];
        blocs_initiaux[i][1] = blocs[i][1];
    }
    FILE *fichier = fopen("positions_initiales_blocs.txt", "w");
    if (fichier != NULL) {
        for (int i = 0; i < NOMBRE_BLOCS; i++) {
            fprintf(fichier, "%d %d\n", blocs_initiaux[i][0], blocs_initiaux[i][1]);
        }
        fclose(fichier);
    }
}
void charger_positions_initiales() {
    FILE *fichier = fopen("positions_initiales_blocs.txt", "r");
    if (fichier != NULL) {
        for (int i = 0; i < NOMBRE_BLOCS; i++) {
            fscanf(fichier, "%d %d", &blocs_initiaux[i][0], &blocs_initiaux[i][1]);
        }
        fclose(fichier);
    }
    // Copier les positions initiales dans les blocs actuels
    for (int i = 0; i < NOMBRE_BLOCS; i++) {
        blocs[i][0] = blocs_initiaux[i][0];
        blocs[i][1] = blocs_initiaux[i][1];
    }
}

int x_bloccassable =2;
int y_bloccassable = 1;

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
            else if ( i == y_bloccassable && j == x_bloccassable){
                printf("C");
            }
            else{
                int bloc_present = 0;
                for (int k = 0; k < NOMBRE_BLOCS; k++) {
                    if (blocs[k][0] == j && blocs[k][1] == i) {
                        if (blocs_deplaces[k] != 1) {

                            printf("B");
                        }
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

void casserblocs(){
    if (x_personnage == x_bloccassable++ && y_personnage == y_bloccassable) {
        x_bloccassable= x_bloccassable-3;
    }else if (x_personnage == x_bloccassable && y_personnage == y_bloccassable++){
        x_bloccassable= x_bloccassable-3;
    }
}

void pousser_bloc() {
    for (int i = 0; i < NOMBRE_BLOCS; i++) {
        if (((x_personnage + 1 == blocs[i][0] && y_personnage == blocs[i][1]) ||
             (x_personnage - 1 == blocs[i][0] && y_personnage == blocs[i][1]) ||
             (x_personnage == blocs[i][0] && y_personnage + 1 == blocs[i][1]) ||
             (x_personnage == blocs[i][0] && y_personnage - 1 == blocs[i][1])) &&
            blocs_deplaces_info[i].deplace == 1) {
            return;
        }
    }

    int bloc_en_deplacement = -1;

    for (int i = 0; i < NOMBRE_BLOCS; i++) {
        if ((x_personnage + 1 == blocs[i][0] && y_personnage == blocs[i][1]) ||
            (x_personnage - 1 == blocs[i][0] && y_personnage == blocs[i][1]) ||
            (x_personnage == blocs[i][0] && y_personnage + 1 == blocs[i][1]) ||
            (x_personnage == blocs[i][0] && y_personnage - 1 == blocs[i][1])) {
            bloc_en_deplacement = i;
            break;
        }
    }

    if (bloc_en_deplacement != -1) {
        int dx = 0, dy = 0;

        if (x_personnage + 1 == blocs[bloc_en_deplacement][0]) {
            dx = 1;
        } else if (x_personnage - 1 == blocs[bloc_en_deplacement][0]) {
            dx = -1;
        } else if (y_personnage + 1 == blocs[bloc_en_deplacement][1]) {
            dy = 1;
        } else if (y_personnage - 1 == blocs[bloc_en_deplacement][1]) {
            dy = -1;
        }

        int new_x = blocs[bloc_en_deplacement][0] + dx;
        int new_y = blocs[bloc_en_deplacement][1] + dy;

        if (new_x >= xmin && new_x <= xmax && new_y >= ymin && new_y <= ymax) {
            int can_push = 1;

            for (int j = 0; j < NOMBRE_BLOCS; j++) {
                if (j != bloc_en_deplacement && blocs[j][0] == new_x && blocs[j][1] == new_y) {
                    can_push = 0;
                    break;
                }
            }

            if (blocs_deplaces_info[bloc_en_deplacement].deplace == 1) {
                return;
            }

            if (can_push) {
                blocs[bloc_en_deplacement][0] = new_x;
                blocs[bloc_en_deplacement][1] = new_y;

                if (blocs_deplaces_info[bloc_en_deplacement].deplace != 1) {
                    blocs_deplaces_info[bloc_en_deplacement].deplace = 1;
                }
            }
        }
    }
}




int tempsTotal = 120;
int tempsRestant ;
clock_t debut = 0; // initialisez debut
clock_t tempsAvantLaPause;

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
        printf("                                                   | 2) niveau 2                     | \n");
        printf("                                                   | 3) niveau 3                     | \n");
        printf("                                                   | 4) Afficher les regles          | \n");
        printf("                                                   | 5)charger une partie            | \n");
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











int touchepourquit;
int touchquitconsole; // utiliser pour pouvoir retourner en arrière sans quitter la console hehe
int viesnoopy=3;




void reinitialiser_jeu() {
    // reinitialiser les positions et les variables du jeu


    xmin = 1; // minnimum du nombre de colonnes de la map
    ymin = 1;// minnimum de nombre de lignes de la map
    xmax = 20;// maximum du nombre de colonnes de la map
    ymax = 10;// maximum du nombre de lignes



// position de depart du personnage, au mileu du terrain
    x_personnage = 10;
    y_personnage = 5;



    x_bloccassable =2;
    y_bloccassable = 1;

// position de depart de la boule
    x_boule = 1;
    y_boule = 1;

    dx_boule = 1; // deplacement de la boule en x
    dy_boule = 1; // deplacement de la boule en y
// permet de faire avancer la boule en diagonale



// position des oiseaux aux quatre coins de la map
    x_oiseau1 = 1;
    y_oiseau1 = 1;

    x_oiseau2 = 20;
    y_oiseau2 = 1;

    x_oiseau3 = 1;
    y_oiseau3 = 10;

    x_oiseau4 = 20;
    y_oiseau4 = 10;




    oiseau_caught = 0;
    viesnoopy = 3;
    tempsTotal = 120;
    tempsRestant = tempsTotal;
    debut = clock();
    memset(blocs_deplaces, 0, sizeof(blocs_deplaces));
    charger_positions_initiales();
}
int affichercoeur( ) {
    if(viesnoopy==3) {
        printf("   **   **    **   **    **   **\n  ");
        printf("**** ****  **** ****  **** ****\n  ");
        printf(" ******     ******     ******\n ");
        printf("   ****       ****       ****\n  ");
        printf("   **         **         **\n    ");

    }else if(viesnoopy==2) {
        printf("     **   **    **   **\n  ");
        printf("  **** ****  **** ****\n  ");
        printf("   ******     ******\n  ");
        printf("    ****       ****\n  ");
        printf("     **         **\n  ");

    }else if(viesnoopy==1) {
        printf("     **   **\n ");
        printf("   **** ****\n  ");
        printf("   ******\n  ");
        printf("    ****\n  ");
        printf("     **\n  ");

    }else if (viesnoopy==0){
        printf(" ");
    }
}

int afficheroiseau(){
    if(oiseau_caught==1) {
        printf("\n");
        printf(" *     * \n");
        printf("  *   * \n");
        printf("   * *   \n");
        printf("    *\n");
    }else if(oiseau_caught==2){

        printf("\n");
        printf(" *     *     *     * \n");
        printf("  *   *       *   *  \n");
        printf("   * *         * *   \n");
        printf("    *           *    \n");
    }else if (oiseau_caught==3){
        printf("                           \n");
        printf(" *     *     *     *    *     * \n");
        printf("  *   *       *   *      *   *\n");
        printf("   * *         * *        * *\n");
        printf("    *           *          *\n");


    }else if ( oiseau_caught==4){
        printf(" \n");
        printf(" *     *     *     *    *     *    *     *\n");
        printf("  *   *       *   *      *   *      *   *\n");
        printf("   * *         * *        * *        * *\n");
        printf("    *           *          *          * \n");
    }else if(oiseau_caught==0){
        printf(" ");
    }
}







void case1(){
    for (int i = 0; i < NOMBRE_BLOCS; i++) {
        blocs_deplaces_info[i].x = blocs[i][0];
        blocs_deplaces_info[i].y = blocs[i][1];
        blocs_deplaces_info[i].deplace = 0;
    }


    do {

        printf("rentrez le code secret pour acceder a la partie 1");
        scanf("%d", &code_secret);
    } while (code_secret != 123);


    tempsRestant = tempsTotal;
    debut = clock(); // commencez le compte à rebours au debut du programme


    do {

        effacerEcran();
        // afficher le terrain, le personnage, la boule et les oiseaux
        afficher_terrain();
        if (x_personnage == x_oiseau1 && y_personnage == y_oiseau1) { // si snooppy attrape un oiseau
            y_oiseau1--; // alors l'oiseau disparait
            oiseau_caught++;// nombre d'oiseau attrapé augmente
            printf("Bravo ! vous avez attrape %d oiseau(x)\n", oiseau_caught);
            tempsAvantLaPause = clock();
            sleep(2);// pause de deux secondes pour feciliter l'utilisateur
            debut += clock() - tempsAvantLaPause;
        }
        if (x_personnage == x_oiseau2 && y_personnage == y_oiseau2) {
            y_oiseau2--;//l oiseau disparait dans le mur du haut, il aurait pu disparaitre dans le mur sur le cote en remplacant par x_oiseau2++
            oiseau_caught++;
            printf("Bravo! vous avez attrape %d oiseau(x)\n", oiseau_caught);
            tempsAvantLaPause = clock();
            sleep(2);
            debut += clock() - tempsAvantLaPause;
        }
        if (x_personnage == x_oiseau3 && y_personnage == y_oiseau3) {
            y_oiseau3++;//l'oiseau disparait dans le mur du bas
            oiseau_caught++;
            printf("Bravo! vous avez attrape %d oiseau(x)\n", oiseau_caught);
            tempsAvantLaPause = clock();
            sleep(2);
            debut += clock() - tempsAvantLaPause;
        }
        if (x_personnage == x_oiseau4 && y_personnage == y_oiseau4) {
            y_oiseau4++;// l'oiseau disparait dans la ligne du bas
            oiseau_caught++;
            printf("Bravo! vous avez attrape %d oiseau(x)\n", oiseau_caught);
            tempsAvantLaPause = clock();
            sleep(2);
            debut += clock() - tempsAvantLaPause;
        }
        if (oiseau_caught == 4) {
            printf("Bravo! vous avez gagne\n");// si l'utilisateur attrape 4 oiseaux alors il a gagne sinon el jeu continue
            printf("Votre score est de %d snoopy\n",tempsRestant*100);
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
                        for (int i = 0; i < NOMBRE_BLOCS; i++) {
                            if (((x_personnage + 1 == blocs[i][0] && y_personnage == blocs[i][1]) ||
                                 (x_personnage - 1 == blocs[i][0] && y_personnage == blocs[i][1]) ||
                                 (x_personnage == blocs[i][0] && y_personnage + 1 == blocs[i][1]) ||
                                 (x_personnage == blocs[i][0] && y_personnage - 1 == blocs[i][1])) &&
                                blocs_deplaces[i] == 1) {
                                break; // Sortir du case 'p' si un bloc "M" est à côté du personnage
                            }
                        }
                        memset(blocs_deplaces, 0, sizeof(blocs_deplaces));
                        pousser_bloc();
                        break;
                    case 'l':
                        tempsAvantLaPause = clock();
                        getch();

                        debut += clock() - tempsAvantLaPause;
                        break;
                    case 'c': // casser bloc
                        casserblocs();
                        break;
                }
            }
        }
        printf("Temps restant : %d secondes\n", tempsRestant);
        affichercoeur( );
        afficheroiseau();
        // pause pour ralentir ou accelerer le mouvement entre chaque position de la balle
        usleep(100000); // pause de 0,1 seconde
        if(x_personnage == x_boule && y_personnage == y_boule || tempsRestant < 0){
            viesnoopy = viesnoopy-1;
            printf("vous avez perdue une vie\n");
            tempsAvantLaPause = clock();
            sleep(2);
            debut += clock() - tempsAvantLaPause;
        }
    } while (viesnoopy!=0);
    system("cls");
    printf("  ***   *****  *   *  *****  \n");
    printf(" *      *   *  ** **  *    \n");
    printf(" *  **  *****  * * *  ****   \n");
    printf(" *   *  *   *  *   *  *    \n");
    printf("  ***   *   *  *   *  ***** \n");
    printf(" \n");
    printf(" ****  *         *  *****  **** \n");
    printf("*    *  *       *   *      *   *\n");
    printf("*    *   *     *    ****   **** \n");
    printf("*    *    *   *     *      *  *  \n");
    printf(" ****       *       *****  *   *\n");

    printf("appuyer sur 1 pour revenir au menu");
    scanf("%d", &touchepourquit);
    reinitialiser_jeu();



}



int main() {
    sauvegarder_positions_initiales();
    do {

        menujeu();
        do {
            switch (choix_menu) {
                case 1:
                    case1();
                    break;



                case 2:
                    do {

                        printf("rentrez le code secret pour acceder a la partie 2");
                        scanf("%d", &code_secret);
                    } while (code_secret != 12);
                    //faire le case 2 ( le niveau 2)
                    break;
                case 3:
                    do {

                        printf("rentrez le code secret pour acceder a la partie 3");
                        scanf("%d", &code_secret);
                    } while (code_secret != 1);
                    break;
                case 4:
                    afficherregle();
                    printf("appuyer sur 1 pour revenir au menu");
                    scanf("%d", &touchepourquit);
                    break;

                case 5:
                    break;
                
            }
        } while (touchepourquit != 1);
    } while (touchquitconsole!=1);
}











































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


int blocs[NOMBRE_BLOCS][3] = { {9, 3, 0}, {10, 3, 0}, {11, 3, 0},  {12, 4, 0}, {12, 5, 0}, {12, 6, 0},  {11, 7, 0}, {10, 7, 0},{9, 7, 0}, {8, 6, 0}, {8, 5, 0}, {8, 4, 0} };
int blocs_deplaces[NOMBRE_BLOCS] = {0};
int blocs_initiaux[NOMBRE_BLOCS][2];

typedef struct {
    int x;
    int y;
    int deplace;
} BlocDeplace;
BlocDeplace blocs_deplaces_info[NOMBRE_BLOCS];

void sauvegarder_positions_initiales() {
    for (int i = 0; i < NOMBRE_BLOCS; i++) {
        blocs_initiaux[i][0] = blocs[i][0];
        blocs_initiaux[i][1] = blocs[i][1];
    }
    FILE *fichier = fopen("positions_initiales_blocs.txt", "w");
    if (fichier != NULL) {
        for (int i = 0; i < NOMBRE_BLOCS; i++) {
            fprintf(fichier, "%d %d\n", blocs_initiaux[i][0], blocs_initiaux[i][1]);
        }
        fclose(fichier);
    }
}
void charger_positions_initiales() {
    FILE *fichier = fopen("positions_initiales_blocs.txt", "r");
    if (fichier != NULL) {
        for (int i = 0; i < NOMBRE_BLOCS; i++) {
            fscanf(fichier, "%d %d", &blocs_initiaux[i][0], &blocs_initiaux[i][1]);
        }
        fclose(fichier);
    }
    // Copier les positions initiales dans les blocs actuels
    for (int i = 0; i < NOMBRE_BLOCS; i++) {
        blocs[i][0] = blocs_initiaux[i][0];
        blocs[i][1] = blocs_initiaux[i][1];
    }
}

int x_bloccassable =2;
int y_bloccassable = 1;

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
            else if ( i == y_bloccassable && j == x_bloccassable){
                printf("C");
            }
            else{
                int bloc_present = 0;
                for (int k = 0; k < NOMBRE_BLOCS; k++) {
                    if (blocs[k][0] == j && blocs[k][1] == i) {
                        if (blocs_deplaces[k] != 1) {

                            printf("B");
                        }
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

void casserblocs(){
    if (x_personnage == x_bloccassable++ && y_personnage == y_bloccassable) {
        x_bloccassable= x_bloccassable-3;
    }else if (x_personnage == x_bloccassable && y_personnage == y_bloccassable++){
        x_bloccassable= x_bloccassable-3;
    }
}

void pousser_bloc() {
    for (int i = 0; i < NOMBRE_BLOCS; i++) {
        if (((x_personnage + 1 == blocs[i][0] && y_personnage == blocs[i][1]) ||
             (x_personnage - 1 == blocs[i][0] && y_personnage == blocs[i][1]) ||
             (x_personnage == blocs[i][0] && y_personnage + 1 == blocs[i][1]) ||
             (x_personnage == blocs[i][0] && y_personnage - 1 == blocs[i][1])) &&
            blocs_deplaces_info[i].deplace == 1) {
            return;
        }
    }

    int bloc_en_deplacement = -1;

    for (int i = 0; i < NOMBRE_BLOCS; i++) {
        if ((x_personnage + 1 == blocs[i][0] && y_personnage == blocs[i][1]) ||
            (x_personnage - 1 == blocs[i][0] && y_personnage == blocs[i][1]) ||
            (x_personnage == blocs[i][0] && y_personnage + 1 == blocs[i][1]) ||
            (x_personnage == blocs[i][0] && y_personnage - 1 == blocs[i][1])) {
            bloc_en_deplacement = i;
            break;
        }
    }

    if (bloc_en_deplacement != -1) {
        int dx = 0, dy = 0;

        if (x_personnage + 1 == blocs[bloc_en_deplacement][0]) {
            dx = 1;
        } else if (x_personnage - 1 == blocs[bloc_en_deplacement][0]) {
            dx = -1;
        } else if (y_personnage + 1 == blocs[bloc_en_deplacement][1]) {
            dy = 1;
        } else if (y_personnage - 1 == blocs[bloc_en_deplacement][1]) {
            dy = -1;
        }

        int new_x = blocs[bloc_en_deplacement][0] + dx;
        int new_y = blocs[bloc_en_deplacement][1] + dy;

        if (new_x >= xmin && new_x <= xmax && new_y >= ymin && new_y <= ymax) {
            int can_push = 1;

            for (int j = 0; j < NOMBRE_BLOCS; j++) {
                if (j != bloc_en_deplacement && blocs[j][0] == new_x && blocs[j][1] == new_y) {
                    can_push = 0;
                    break;
                }
            }

            if (blocs_deplaces_info[bloc_en_deplacement].deplace == 1) {
                return;
            }

            if (can_push) {
                blocs[bloc_en_deplacement][0] = new_x;
                blocs[bloc_en_deplacement][1] = new_y;

                if (blocs_deplaces_info[bloc_en_deplacement].deplace != 1) {
                    blocs_deplaces_info[bloc_en_deplacement].deplace = 1;
                }
            }
        }
    }
}




int tempsTotal = 120;
int tempsRestant ;
clock_t debut = 0; // initialisez debut
clock_t tempsAvantLaPause;

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
        printf("                                                   | 3) chzrger une partie           | \n");
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











int touchepourquit;
int touchquitconsole; // utiliser pour pouvoir retourner en arrière sans quitter la console hehe
int viesnoopy=3;




void reinitialiser_jeu() {
    // Réinitialiser les positions et les variables du jeu


    xmin = 1; // minnimum du nombre de colonnes de la map
    ymin = 1;// minnimum de nombre de lignes de la map
    xmax = 20;// maximum du nombre de colonnes de la map
    ymax = 10;// maximum du nombre de lignes



// position de depart du personnage, au mileu du terrain
    x_personnage = 10;
    y_personnage = 5;



    x_bloccassable =2;
    y_bloccassable = 1;

// position de depart de la boule
    x_boule = 1;
    y_boule = 1;

    dx_boule = 1; // deplacement de la boule en x
    dy_boule = 1; // deplacement de la boule en y
// permet de faire avancer la boule en diagonale



// position des oiseaux aux quatre coins de la map
    x_oiseau1 = 1;
    y_oiseau1 = 1;

    x_oiseau2 = 20;
    y_oiseau2 = 1;

    x_oiseau3 = 1;
    y_oiseau3 = 10;

    x_oiseau4 = 20;
    y_oiseau4 = 10;




    oiseau_caught = 0;
    viesnoopy = 3;
    tempsTotal = 120;
    tempsRestant = tempsTotal;
    debut = clock();
    memset(blocs_deplaces, 0, sizeof(blocs_deplaces));
    charger_positions_initiales();
}
void sauvegarder_jeu() {
    FILE *fichier = fopen("sauvegarde.txt", "w");
    if (fichier != NULL) {
        fprintf(fichier, "%d %d\n", x_personnage, y_personnage);
        fprintf(fichier, "%d %d\n", x_boule, y_boule);
        fprintf(fichier, "%d %d\n", x_oiseau1, y_oiseau1);
        fprintf(fichier, "%d %d\n", x_oiseau2, y_oiseau2);
        fprintf(fichier, "%d %d\n", x_oiseau3, y_oiseau3);
        fprintf(fichier, "%d %d\n", x_oiseau4, y_oiseau4);



        fclose(fichier);
    }
}
void sauvegarder_etat_blocs(int blocs[NOMBRE_BLOCS][2], int blocs_deplaces[NOMBRE_BLOCS]) {
    FILE *fichier = fopen("sauvegarde_blocs.txt", "w");
    if (fichier != NULL) {
        for (int i = 0; i < NOMBRE_BLOCS; i++) {
            fprintf(fichier, "%d %d %d\n", blocs[i][0], blocs[i][1], blocs_deplaces[i]);
        }
        fclose(fichier);

    }
    }
void charger_etat_blocs(int blocs[NOMBRE_BLOCS][2], int blocs_deplaces[NOMBRE_BLOCS]) {
    FILE *fichier = fopen("sauvegarde_blocs.txt", "r");
    if (fichier != NULL) {
        for (int i = 0; i < NOMBRE_BLOCS; i++) {
            fscanf(fichier, "%d %d %d", &blocs[i][0], &blocs[i][1], &blocs_deplaces[i]);
        }
        fclose(fichier);

    }
}
void charger_jeu() {
    FILE *fichier = fopen("sauvegarde.txt", "r");
    if (fichier != NULL) {
        fscanf(fichier, "%d %d", &x_personnage, &y_personnage);
        fscanf(fichier, "%d %d\n", x_boule, y_boule);
        fscanf(fichier, "%d %d\n", x_oiseau1, y_oiseau1);
        fscanf(fichier, "%d %d\n", x_oiseau2, y_oiseau2);
        fscanf(fichier, "%d %d\n", x_oiseau3, y_oiseau3);
        fscanf(fichier, "%d %d\n", x_oiseau4, y_oiseau4);

        fclose(fichier);

    }
}


void case1(){
    for (int i = 0; i < NOMBRE_BLOCS; i++) {
        blocs_deplaces_info[i].x = blocs[i][0];
        blocs_deplaces_info[i].y = blocs[i][1];
        blocs_deplaces_info[i].deplace = 0;
    }


    do {

        printf("rentrez le code secret pour acceder a la partie 1");
        scanf("%d", &code_secret);
    } while (code_secret != 123);


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
            tempsAvantLaPause = clock();
            sleep(2);// pause de deux secondes pour feciliter l'utilisateur
            debut += clock() - tempsAvantLaPause;
        }
        if (x_personnage == x_oiseau2 && y_personnage == y_oiseau2) {
            y_oiseau2--;//l oiseau disparait dans le mur du haut, il aurait pu disparaitre dans le mur sur le cote en remplacant par x_oiseau2++
            oiseau_caught++;
            printf("Bravo! vous avez attrape %d oiseau(x)\n", oiseau_caught);
            tempsAvantLaPause = clock();
            sleep(2);
            debut += clock() - tempsAvantLaPause;
        }
        if (x_personnage == x_oiseau3 && y_personnage == y_oiseau3) {
            y_oiseau3++;//l'oiseau disparait dans le mur du bas
            oiseau_caught++;
            printf("Bravo! vous avez attrape %d oiseau(x)\n", oiseau_caught);
            tempsAvantLaPause = clock();
            sleep(2);
            debut += clock() - tempsAvantLaPause;
        }
        if (x_personnage == x_oiseau4 && y_personnage == y_oiseau4) {
            y_oiseau4++;// l'oiseau disparait dans la ligne du bas
            oiseau_caught++;
            printf("Bravo! vous avez attrape %d oiseau(x)\n", oiseau_caught);
            tempsAvantLaPause = clock();
            sleep(2);
            debut += clock() - tempsAvantLaPause;
        }
        if (oiseau_caught == 4) {
            printf("Bravo! vous avez gagne\n");// si l'utilisateur attrape 4 oiseaux alors il a gagne sinon el jeu continue
             printf("Votre score est de %d snoopy\n",tempsRestant*100);
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
                        if(x_personnage==7 && y_personnage == 5 ||x_personnage==8 && y_personnage == 6 || x_personnage==8 && y_personnage == 4 || x_personnage==9 && y_personnage == 5) {
                    if (viesnoopy < 3) {
                        printf(" vous avez declenche un bloc bonus, vous gagne une vie sauf si vous en avez deja 3");
                        tempsAvantLaPause = clock();
                        sleep(2);
                        debut += clock() - tempsAvantLaPause;
                        viesnoopy = viesnoopy + 1;
                    } else
                        (printf(" vous avez declenche un bloc bonus, vous gagne une vie sauf si vous en avez deja 3"));
                    tempsAvantLaPause = clock();
                    sleep(2);
                    debut += clock() - tempsAvantLaPause;
                }


                        
                        for (int i = 0; i < NOMBRE_BLOCS; i++) {
                            if (((x_personnage + 1 == blocs[i][0] && y_personnage == blocs[i][1]) ||
                                 (x_personnage - 1 == blocs[i][0] && y_personnage == blocs[i][1]) ||
                                 (x_personnage == blocs[i][0] && y_personnage + 1 == blocs[i][1]) ||
                                 (x_personnage == blocs[i][0] && y_personnage - 1 == blocs[i][1])) &&
                                blocs_deplaces[i] == 1) {
                                break; // Sortir du case 'p' si un bloc "M" est à côté du personnage
                            }
                        }
                        memset(blocs_deplaces, 0, sizeof(blocs_deplaces));
                        pousser_bloc();
                        break;
                    case 'l':
                        tempsAvantLaPause = clock();
                        getch();

                        debut += clock() - tempsAvantLaPause;
                        break;
                    case 'c': // casser bloc
                        casserblocs();
                        break;
                }
            }
        }
        printf("Temps restant : %d secondes\n", tempsRestant);
        // pause pour ralentir ou accelerer le mouvement entre chaque position de la balle
        usleep(100000); // pause de 0,1 seconde
        if(x_personnage == x_boule && y_personnage == y_boule || tempsRestant < 0){
            viesnoopy = viesnoopy-1;
            printf("vous avez perdue une vie\n");
            sleep(2);
        }
    } while (viesnoopy!=0);
    printf("GAME OVER!\n");
    printf("appuyer sur 1 pour revenir au menu");
    scanf("%d", &touchepourquit);
    reinitialiser_jeu();


// continuer le jeu jusqu'a ce que le personnage rencontre la balle ou que le temps soit ecoule
    //sleep(2000);// afficher game over pendant 2 secondes





}



int main() {
    sauvegarder_positions_initiales();
    do {

        menujeu();
        do {
            switch (choix_menu) {
                case 1:
                    case1();
                    break;


                case 2:
                    afficherregle();
                    printf("appuyer sur 1 pour revenir au menu");
                    scanf("%d", &touchepourquit);
                    break;

            }
        } while (touchepourquit != 1);
    } while (touchquitconsole!=1);
}






























































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

                       if (x_personnage==9 && y_personnage == 2 ||x_personnage==9 && y_personnage == 4 || x_personnage==8 && y_personnage == 3 || x_personnage==10 && y_personnage == 3) {
                           printf("game over");
                           sleep(2);
                           case1();


                           //pousser le bloc d'une case en fonction de la ou ce trouve Snoopy
                       }else if (x_personnage + 1 == blocs[i][0] && y_personnage == blocs[i][1]) {
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
           clock_t tempsAvantLaPause;

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
                   printf("                                                   | 3) chzrger une partie           | \n");
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








           int touchepourquit;
           int touchquitconsole; // utiliser pour pouvoir retourner en arrière sans quitter la console hehe
           void case1(){
               do {

                   printf("rentrez le code secret pour acceder a la partie 1");
                   scanf("%d", &code_secret);
               } while (code_secret != 123);


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
                       tempsAvantLaPause = clock();
                       sleep(2);// pause de deux secondes pour feciliter l'utilisateur
                       debut += clock() - tempsAvantLaPause;
                   }
                   if (x_personnage == x_oiseau2 && y_personnage == y_oiseau2) {
                       y_oiseau2--;//l oiseau disparait dans le mur du haut, il aurait pu disparaitre dans le mur sur le cote en remplacant par x_oiseau2++
                       oiseau_caught++;
                       printf("Bravo! vous avez attrape %d oiseau(x)\n", oiseau_caught);
                       tempsAvantLaPause = clock();
                       sleep(2);
                       debut += clock() - tempsAvantLaPause;
                   }
                   if (x_personnage == x_oiseau3 && y_personnage == y_oiseau3) {
                       y_oiseau3++;//l'oiseau disparait dans le mur du bas
                       oiseau_caught++;
                       printf("Bravo! vous avez attrape %d oiseau(x)\n", oiseau_caught);
                       tempsAvantLaPause = clock();
                       sleep(2);
                       debut += clock() - tempsAvantLaPause;
                   }
                   if (x_personnage == x_oiseau4 && y_personnage == y_oiseau4) {
                       y_oiseau4++;// l'oiseau disparait dans la ligne du bas
                       oiseau_caught++;
                       printf("Bravo! vous avez attrape %d oiseau(x)\n", oiseau_caught);
                       tempsAvantLaPause = clock();
                       sleep(2);
                       debut += clock() - tempsAvantLaPause;
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
                               case 'l':
                                   tempsAvantLaPause = clock();
                                   getch();

                                   debut += clock() - tempsAvantLaPause;
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




           }



           int main() {
               do {

                   menujeu();
                   do {
                       switch (choix_menu) {
                           case 1:
                               case1();
                               break;


                           case 2:
                               afficherregle();
                               printf("appuyer sur 1 pour quitter");
                               scanf("%d", &touchepourquit);
                               break;

                       }
                   } while (touchepourquit != 1);
               } while (touchquitconsole!=1);
           }
