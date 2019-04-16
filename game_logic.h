
/*
 * Prints the board
 * 
 * Input: the board to be printed. 
 */
void print_board(square board[NUM_ROWS][NUM_COLUMNS]);


/*
 * Place tokens in the first column of the board
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players  
 */
void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers);



/* 
 *  * Manages the logic of the game
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players 
 */
void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers);

void playerMovement(square board[NUM_ROWS][NUM_COLUMNS],int row,int column,int upDown,int forward);

void moveForward(square board[NUM_ROWS][NUM_COLUMNS], player currentPlayer,int column,int roll);

int rollDice();

struct token * push(player value, struct token *top);

struct token * pop(struct token *top);

int moveAndObsCheck(square board[NUM_ROWS][NUM_COLUMNS], int row);

int checkBoard(square board[NUM_ROWS][NUM_COLUMNS],int column);








