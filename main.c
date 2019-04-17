/* 
 * File:   main.c
 * Author: Morgan & Iva
 *
 * Calls all functions necessary to initialize the game, play the game and 
 * identify a winner
 * 
 */

#include "game_init.h" //Library which holds function prototypes for initilization & structs & enums for game
#include "game_logic.h" //Library which holds function prototypes to play the game
#include <stdio.h> //Standard input/output library in C


/*
 * Begin function main execution
 */
int main(int argc, char** argv) {
    
    
    //The board is defined as a 2-Dimensional array of squares
    square board[NUM_ROWS][NUM_COLUMNS];
    
    //An array containing the players (MAX 6 players)
    player players[6];
    
    //The number of players
    int numPlayers =0;
    
    //Creates the squares of the board
    initialize_board(board);
    
    //Creates the players
    numPlayers = initialize_players(players);
    
    //Initialize color
    initialize_colour(players,numPlayers);
    
    //Prints the board
    print_board(board);
    
    //Asks each player to place their tokens on first column of the board
    place_tokens(board, players, numPlayers);

    //Manages the turns of the game and identifies a winner
    play_game(board, players, numPlayers);
       
    return 0;

} //End function main

