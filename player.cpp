#include "player.h"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    this->side = side; // Make the side available to the player
    this->board = new Board(); // Make an empty board to keep track of moves
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

    // If the player is black
    if (this->side == BLACK)
    {
        // Record the opponent's move as white
        this->board->doMove(opponentsMove, WHITE);
    }
    else
    {
        // Else record the opponent's move as black
        this->board->doMove(opponentsMove, BLACK);
    }
    
    // Scores for each position in the game board
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

    // Initialize the best score and best move
    int bestScore = -5;
    Move *bestMove = NULL;

    // Loop through every move in the game board
    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {
            // Store the potentional move
            Move *move = new Move(i, j);

            // Check if the move is valid
            if (this->board->checkMove(move, this->side))
            {
                // If the score of the potentional move is better than the 
                // best score
                if (scores[move->getX()][move->getY()] > bestScore)
                {
                    // Set the new best score and best move
                    bestScore = scores[move->getX()][move->getY()];
                    bestMove = move;
                }
            }
        }
    }

    // Record the move and return it
    this->board->doMove(bestMove, this->side);
    return bestMove;
}
