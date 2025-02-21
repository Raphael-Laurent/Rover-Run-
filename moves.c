//
// Created by flasque on 19/10/2024.
//

#include "moves.h"


/* prototypes of local functions */
/* local functions are used only in this file, as helper functions */

/**
 * @brief Function to rotate the robot according to a move and its actual orientation
 * @param ori : the actual orientation of the robot
 * @param move : the move to do
 * @return the new orientation of the robot
 */
t_orientation rotate(t_orientation, t_move);

/**
 * @brief function to translate the robot according to a move and its actual position
 * @param loc : the actual localisation of the robot
 * @param move : the move to do
 * @return the new localisation of the robot
 */
t_localisation translate(t_localisation, t_move);

/* definition of local functions */

t_orientation rotate(t_orientation ori, t_move move) {
    int rst;
    switch (move) {
        case T_LEFT:
            rst = 3;
            break;
        case T_RIGHT:
            rst = 1;
            break;
        case U_TURN:
            rst = 2;
            break;
        default:
            rst = 0; // rst restait non initialis� en default dans le code de base, 0 choisi  arbitrairement sinon �a plante pour moi // Yiannis
            break;
    }
    return (ori + rst) % 4;
}

t_localisation translate(t_localisation loc, t_move move) {
    /** rules for coordinates:
     *  - x grows to the right with step of +1
     *  - y grows to the bottom with step of +1
     *  - the origin (x=0, y=0) is at the top left corner
     */
    t_position res = loc.pos;
    switch (move) {
        case F_10:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 1;
                    break;
                case EAST:
                    res.x = loc.pos.x + 1;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 1;
                    break;
                case WEST:
                    res.x = loc.pos.x - 1;
                    break;
                default:
                    break;
            }
            break;
        case F_20:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 2;
                    break;
                case EAST:
                    res.x = loc.pos.x + 2;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 2;
                    break;
                case WEST:
                    res.x = loc.pos.x - 2;
                    break;
                default:
                    break;
            }
            break;
        case F_30:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 3;
                    break;
                case EAST:
                    res.x = loc.pos.x + 3;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 3;
                    break;
                case WEST:
                    res.x = loc.pos.x - 3;
                    break;
                default:
                    break;
            }
            break;
        case B_10:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y + 1;
                    break;
                case EAST:
                    res.x = loc.pos.x - 1;
                    break;
                case SOUTH:
                    res.y = loc.pos.y - 1;
                    break;
                case WEST:
                    res.x = loc.pos.x + 1;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return loc_init(res.x, res.y, loc.ori);

}

/* definitions of exported functions */

char *getMoveAsString(t_move move) {
    return _moves[move];
}

t_localisation move(t_localisation loc, t_move move) {
    loc.ori = rotate(loc.ori, move);
    loc = translate(loc, move);
    return loc;
}

void updateLocalisation(t_localisation *p_loc, t_move m) {
    *p_loc = move(*p_loc, m);
    return;
}

void randomMoves(int probs[], t_move array[]) {
    const int numVal = 9;
    int randVal;
    int totalCoef =
            probs[F_10] + probs[F_20] + probs[F_30] + probs[B_10] + probs[T_LEFT] + probs[T_RIGHT] + probs[U_TURN] - 1;
    int noResult;
    int interval;

    srand(time(NULL));
    for (int i = 0; i < numVal; i++) {
        randVal = (rand() % (totalCoef)) + 1;
        noResult = 1;
        interval = 0;
        for (t_move e = 0; e < NONE && noResult; e++) {
            interval += probs[e];
            if (randVal <= interval) {
                array[i] = e;
                probs[e]--;
                totalCoef--;
                noResult = 0;
            }
        }
        if (noResult) {
            array[i] = NONE;
        }
    }
}

t_move updateERGMovement(t_move move) {
    switch (move) {
        case F_10:
            return ZERO;
        case F_20:
            return F_10;
        case F_30:
            return F_20;
        case B_10:
            return ZERO;
        default:
            return move;
    }
}