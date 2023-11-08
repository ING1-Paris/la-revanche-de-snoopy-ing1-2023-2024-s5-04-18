#include <stdio.h>

int main() {
    int tableau[10][20];
    printf("|*|*|*|*|*|*|*|*|*|*|*|*|\n");
    for (int i = 1; i < 10; ++i) {// on mets 12 pour avoir 10 lignes vide plus deux lignes pleines qui correspondent au bors
        printf("|*|");
        for (int j = 1; j < 20; ++j) {
            printf(" ");
        }
        printf("|*|\n");
    }
    printf("|*|*|*|*|*|*|*|*|*|*|*|*|");
    return 0;
}
