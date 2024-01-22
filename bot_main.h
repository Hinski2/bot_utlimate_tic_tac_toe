// bot_main.h
#ifndef BOT_MAIN_H
#define BOT_MAIN_H

extern int DIFF, WINS, SELECT;
extern double SQRT;

typedef enum
{
    IN_PROGRESS, /**< Game in progress - 0 */
    X_WON,       /**< X won - 1 */
    O_WON,       /**< O won  - 2 */
    DRAW,        /**< Draw  - 3 */
    NOT_STARTED, /**< Game waiting for the start  - 4 */
} GameStatus;

/*!
 * \brief Enumerates the turns of players.
 *
 * This enumeration represents which player is about to place next move and
 * is used as indicators in the Board values
 */
typedef enum
{
    O,     /**< O - 0 */
    X,     /**< X - 1 */
    EMPTY, /**< Empty space - 2 */
} Player;

/*!
 * \brief Represents a single tictactoe board.
 *
 * This structure defines tictactoe board. It keeps game status and board as 3x3 matrix,
 * with X and O as player moves.
 */
typedef struct
{
    GameStatus status;  /**< Status of the game on the board */
    int moves_count;    /**< Number of moves played on the board */
    Player value[3][3]; /**< Matrix representing the board */
} Board;

/*!
 * \brief Represents any board of the size NxN.
 *
 * This structure defines tictactoe board. It keeps NxN game status and boards,
 * allowing to play on the boards of any (correct) size.
 */
typedef struct
{
    Board **board;     /**< Pointer to the pointer of board - linear representation of NxN board */
    int board_size;    /**< boards are board_size x board_size */
    int moves_count;   /**< Numbers of the moves played in the game */
    GameStatus status; /**< Status of the game */
    Player turn;       /**< X or O indicating which player is about to move next */
} Game;


#endif
