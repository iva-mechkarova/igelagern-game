/*
 * File: game_logic.h
 * Authors: Morgan & Iva
 * 
 * This file holds all function prototypes required to play the game - function
 * to place tokens at the beginning of the game, function to play the game and
 * function to print the board after each turn/move.
 * 
 */

#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

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

#endif	// GAME_LOGIC_H

