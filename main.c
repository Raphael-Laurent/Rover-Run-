#include <stdio.h>
#include "map.h"
#include "n_tree.h"

int main() {
    t_map map;

    // The following preprocessor directive checks if the code is being compiled on a Windows system.
    // If either _WIN32 or _WIN64 is defined, it means we are on a Windows platform.
    // On Windows, file paths use backslashes (\), hence we use the appropriate file path for Windows.
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\example1.map");
#else
    map = createMapFromFile("../maps/example1.map");
#endif

    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    displayMap(map);


    printf("%d",map.costs[4][2]);
    t_localisation ruver;
    ruver = loc_init(1,4, EAST); //on initialise la position du rover
    printLocalisation(ruver, map);
    ruver = move(ruver, F_10);
    printLocalisation(ruver, map);
    ruver = loc_init(1,4,NORTH);
    printLocalisation(ruver, map);



    // -----TEST------------------------------------------------------------------
    //map.costs = les coûts

    t_localisation rover;
    rover = loc_init(1, 4, NORTH); //on initialise la position du rover
    t_move avails[9] = {F_10, F_20, F_10, T_RIGHT, U_TURN};
    t_node *root = createNode(map.costs[rover.pos.x][rover.pos.y], 5, avails, 0, rover);
    t_tree mytree = createNTree(root, 3, rover, map);

        // Affichage de l'arbre
    printf("Arbre n-aire:\n");
    printNTree(mytree);


}
