#include "player.h"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /* 
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */

    this->side = side;
    this->board = new Board();
}

/*
 * Destructor for the player.
 */
Player::~Player() {
    delete this->board;
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /* 
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */ 

    if (this->side == BLACK)
    {
        this->board->doMove(opponentsMove, WHITE);
    }
    else
    {
        this->board->doMove(opponentsMove, BLACK);
    }
    
    int scores[8][8] = {
        { 3, -3,  2,  2,  2,  2, -3,  3},
        {-3, -4, -2, -2, -2, -2, -4, -3},
        { 2, -2,  1,  0,  0,  1, -2,  2},
        { 2, -2,  0,  1,  1,  0, -2,  2},
        { 2, -2,  0,  1,  1,  0, -2,  2},
        { 2, -2,  1,  0,  0,  1, -2,  2},
        {-3, -4, -2, -2, -2, -2, -4, -3},
        { 3, -3,  2,  2,  2,  2, -3,  3},
    };

    int bestScore = -5;
    Move *bestMove = NULL;
    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {
            Move *move = new Move(i, j);

            if (this->board->checkMove(move, this->side))
            {
                if (scores[move->getX()][move->getY()] > bestScore)
                {
                    bestScore = scores[move->getX()][move->getY()];
                    bestMove = move;
                }
            }
        }
    }

    this->board->doMove(bestMove, this->side);
    return bestMove;
}
