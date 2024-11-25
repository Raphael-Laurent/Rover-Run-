#include <stdio.h>
#include "map.h"
#include "n_tree.h"
#include "moves.h"
#include "stdlib.h"
#include "time.h"
#include "initialize.h"

void printTab(const int *tableau, int size);

int main() {
    t_map map = getRandomMap();

    printMapAndCost(&map);
    // -----TEST------------------------------------------------------------------
    t_move tableau[9];
    int proba[7];
    moveProbaInit(proba);

    /*
    printTab(proba, 7); //Afficher les probabilités pour le debug
    randomMoves(proba, tableau);
    printRndMvs(tableau); //Afficher les moves pour le debug
    printTab(proba, 7); //Afficher les probabilités pour le debug
    */
    t_tree mytree = getTree(&map);

    // Affichage de l'arbre
    printf("\nArbre n-aire:\n");
    printNTree(mytree);

    //Afficher le minimum de parcours
    //t_node *min = minLocalisation(mytree.root, min, map);
    //printf("%d\n",min->value);

    //utilisation du chronomètre
    clock_t start = chronometerInit();
    /*
     * exemple

    for (int i = 0; i < 0xFFff; i++) {
        for (int j = 0; j < 0xFFff; j++) {
            for (int k = 0; k < 0xffff; k++) {
                printf("%6.3lf secondes\r", ((double)(clock() - start)) / ((double)CLOCKS_PER_SEC));
            }
        }
    }
    //
    double deltaT = chronometerEnd(start);
    */
    return 0;
}

void printTab(const int *tableau, int size) {
    for (int i = 0; i < size-1; i++) {
        printf("%d ", tableau[i]);
    }
    printf("%d \n", tableau[size-1]);
}

