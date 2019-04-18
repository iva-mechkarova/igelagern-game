/*
 * File: game_init.c
 * Authors: Morgan & Iva
 * 
 * This file holds all functions necessary to initialize the board, the players 
 * and each player's colour before the game starts 
 * 
 */


#include "game_init.h" //Library which holds function prototypes for initilization & structs & enums for game
#include <stdio.h> //Standard input/output library in C
#include <string.h> //Standard library in C for string functions (needed for strtok)


/*
 * This function creates the board for the first time
 * 
 * Input: board - a 6x9 array of squares
 */
void initialize_board(square board[NUM_ROWS][NUM_COLUMNS]){
   //Loops through each row
    for (int i =0; i< NUM_ROWS; i++){
        //For each row it loops through each column
        for(int j =0; j < NUM_COLUMNS; j++){
            //Creates an obstacle square at positions (0,3), (1,6), (2,4), (3,5), (4,2) and (5,7)
            if((i == 0 && j==3) || (i == 1 && j == 6) || (i ==2 && j ==4) 
                    || (i == 3 && j ==5) || (i==4 && j==2) || (i==5 && j==7)){
                board[i][j].type = OBSTACLE; //Sets type at these positions to obstacle
            } else{
                //Creates a normal square otherwise
                board[i][j].type = NORMAL;
            }
            board[i][j].stack = NULL; //Initializes stack on each square to NULL
        }
    }
}

/*****************************************************/ 
/*
 * This function creates players for the first time
 * 
 * Input: the array of players to be initialized
 * Output: The number of players of the game
 */
int initialize_players(player players[]){
    int i=0; //Counter initialized to 0
    
    //Loop a maximum of 6 times (0-5) as max players is 6
    while(i<6){
        printf("Name for player %d :",i+1); //Prompt user for input of playername
        fgets(players[i].playername,32,stdin); //Obtain playername from user 
        strtok(players[i].playername, "\n"); //Splits string into tokens - If carriage return is entered it is not the name of a user
        if(players[i].playername[0] == '\n') //Checks if carriage return symbol is entered
            break; //If it is, do not ask for more playernames i.e. break from the loop
        i++; //Increment counter 
        
    }
    return i; //Return number of players provided as input 
}

/*****************************************************/ 
/*
 * This function initializes each player's colour 
 * 
 * Input: the array of players and the number of players
 */
void initialize_colour(player players[],int numPlayers){   
    int i=0; //Initialize counter to 0, 
    int option; //Declare variables to store option(colour) 
    printf("----------------------Colours----------------------\n");
        //Prints all colours in colour hence "\033" and their corresponding number 
#ifdef COLOR_TRUE
        printf("\033[1;31m[1]RED \033[1;34m[2]BLUE \033[1;32m[3]GREEN \033[1;33m[4]YELLOW \033[1;35m[5]PINK \033[1;36m[6]CYAN\033[0m\n"); 
#endif
#ifdef COLOR_FALSE
        printf("[1]RED [2]BLUE [3]GREEN [4]YELLOW [5]PINK [6]CYAN\n"); 
#endif
        printf("---------------------------------------------------\n");
    
    //Loop through each player to initialize their colour 
    while(i<numPlayers)
    {
        printf("%s Select a colour:",players[i].playername); //Prompt user for input of colour 
        scanf("%d",&option); //Obtain value int value from user which corresponds to a colour e.g 1=RED, 2=BLU 
        
        //Check which colour the player has selected and execute the corresponding case 
        /*Set player's col to corresponding colour in enum color and player's playerColour (string) 
        to the colour which will also be written in that colour due to \033*/
        switch(option){
#ifdef COLOR_TRUE
            //If 1 is chosen then set player's col to RED 
            //Player's playerColour (string) will be written in RED as "1;31m" is ANSI code for BOLD RED
            case 1: players[i].col=RED;players[i].playerColour="\033[1;31mRED\033[0m"; 
                    break;
            //If 2 is chosen then set player's col to BLU 
            //Player's playerColour (string) will be written in BLU as "1;34m" is ANSI code for BOLD BLUE
            case 2: players[i].col=BLU;players[i].playerColour="\033[1;34mBLU\033[0m";
                    break;
            //If 1 is chosen then set player's col to GREEN 
            //Player's playerColour (string) will be written in GREEN as "1;32m" is ANSI code for BOLD GREEN
            case 3: players[i].col=GREEN;players[i].playerColour="\033[1;32mGREEN\033[0m";
                    break;
            //If 1 is chosen then set player's col to YELLOW 
            //Player's playerColour (string) will be written in YELLOW as "1;33m" is ANSI code for BOLD YELLOW
            case 4: players[i].col=YELLOW;players[i].playerColour="\033[1;33mYELLOW\033[0m";
                    break;
            //If 1 is chosen then set player's col to PINK 
            //Player's playerColour (string) will be written in PINK as "1;35m" is ANSI code for BOLD MAGENTA (pink)
            case 5: players[i].col=PINK;players[i].playerColour="\033[1;35mPINK\033[0m";
                    break;
            //If 1 is chosen then set player's col to CYAN 
            //Player's playerColour (string) will be written in CYAN as "1;31m" is ANSI code for BOLD CYAN
            case 6: players[i].col=CYAN;players[i].playerColour="\033[1;36mCyan\033[0m";
            default: break;
#endif
#ifdef COLOR_FALSE
            case 1: players[i].col=RED;players[i].playerColour="RED"; 
                    break;
            case 2: players[i].col=BLU;players[i].playerColour="BLU";
                    break;
            case 3: players[i].col=GREEN;players[i].playerColour="GREEN";
                    break;
            case 4: players[i].col=YELLOW;players[i].playerColour="YELLOW";
                    break;
            case 5: players[i].col=PINK;players[i].playerColour="PINK";
                    break;
            case 6: players[i].col=CYAN;players[i].playerColour="CYAN";
            default: break;
#endif
        }
        int loop=0; //Initialize variable "loop" to 0
        //Loop to check if selected colour has already been chosen by another player
        for(int x=0; x<i; x++)
            {
                //Check if any of the previous players have already selected this colour 
                if (players[i].col==players[x].col) 
                {
                    printf("Error: Colour already seleceted!\n"); //Inform user this colour has been selected
                    loop=1; //Don't proceed to next if statement as i shouldn't be incremented 
                }
        }
        if(loop==0)
            i++; //Increment i 
    }
}