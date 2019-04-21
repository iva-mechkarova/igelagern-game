/*
 * File: game_init.h
 * Authors: Morgan & Iva
 * 
 * This file holds all function prototypes to initialize the board, the players 
 * and each player's colour before the game starts. It also declares enums and 
 * structs which will be used throughout the program. 
 */

//Number of rows of the board
#ifndef GAME_INIT_H
#define GAME_INIT_H

#define NUM_ROWS 6
//Number of columns of the board
#define NUM_COLUMNS 9

#define COLOR_TRUE /*Change to "COLOR_FALSE" if errors showing colours*/

//Types of squares
//In an obstacle square the token cannot be moved until all other tokens are at least in the same column as the obstacle square
enum stype{ 
    NORMAL, OBSTACLE 
}; 

//Colors of tokens
enum color{
    RED, BLU, GREEN, YELLOW, PINK, CYAN, NONE
};

//Defines a token
//Each token is associated with a color 
typedef struct token{
   enum color col; //Declare variable of type enum color to store token's color
   struct token *next; //Declare variable of type struct token to point to next element in stack 
}token; //When setting variable type to struct token you may just type "token"

//Defines a square of the board
typedef struct square{  
     enum stype type; //A square can be a NORMAL or an OBSTACLE square
     token * stack; //the stack of tokens that can be placed on the board square    
     int numTokens; //Variable to store number of tokens on each square 
}square; //When setting variable type to "struct square" you may just type "square"



//Defines a player 
typedef struct player{
    char playername[20]; //Declare char array to store player's name 
    char *playerColour; //String to store player's color 
    enum color col; //Each player will be associated with a color
    int numTokensLastCol; //Keeps track of how many tokens player has in the last column   
}player; //When setting variable type to "struct player" you may just type "player"


/*
 * This function creates the board for the first time
 * 
 * Input: board - a 6x9 array of squares
 *
 */
void initialize_board(square board[NUM_ROWS][NUM_COLUMNS]);

/*
 * This function creates players for the first time
 * 
 * Input: the array of players to be initialized
 * 
 * Output: The number of players of the game
 *
 */
int initialize_players(player players[]);

/*
 * This function initializes each player's color
 * 
 * Input: the array of players & the number of players 
 *
 */
void initialize_colour(player players[],int numPlayers);

#endif	// GAME_INIT_H

