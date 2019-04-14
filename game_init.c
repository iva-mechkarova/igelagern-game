/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "game_init.h"
#include "game_logic.h"
#include <stdio.h>


/*
 * This function creates the board for the first time
 * 
 * Input: board - a 6x9 array of squares
 *
 */


void initialize_board(square board[NUM_ROWS][NUM_COLUMNS]){
   
    for (int i =0; i< NUM_ROWS; i++){
        for(int j =0; j < NUM_COLUMNS; j++){
            //creates an obstacle square at positions (0,3), (1,6), (2,4), (3,5), (4,2) and (5,7)
            if((i == 0 && j==3) || (i == 1 && j == 6) || (i ==2 && j ==4) 
                    || (i == 3 && j ==5) || (i==4 && j==2) || (i==5 && j==7)){
                board[i][j].type = OBSTACLE;
            } else{
                //creates a normal square otherwise
                board[i][j].type = NORMAL;
            }
            board[i][j].stack = NULL;
        }
    }
}
    
    
 /*
 * This function creates players for the first time
 * 
 * Input: the array of players to be initialized
 * Output: The number of players of the game
 */
int initialize_players(player players[]){
    
    //YOU WILL NEED TO IMPLEMENT THIS FUNCTION IN THIS LAB
    int i=0;
    while(i<6){
        printf("Name for player %d :",i+1);
        fgets(players[i].playername,32,stdin);
        strtok(players[i].playername, "\n");
        if(players[i].playername[0] == '\n')
            break;
        i++;
        
    }
    return i;
}

int initialize_colour(player players[],int numPlayers){   
    int i=0,option,loop;
    printf("----------------------Colours----------------------\n");
        printf("\033[1;31m[1]RED \033[1;34m[2]BLUE \033[1;32m[3]GREEN \033[1;33m[4]YELLOW \033[1;35m[5]PINK \033[1;36m[6]CYAN\033[0m\n");
        printf("---------------------------------------------------\n");
    
    while(i<numPlayers)
    {
        printf("%s Select a colour:",players[i].playername);
        scanf("%d",&option);
        
        switch(option){
            case 1: players[i].col=RED;players[i].playerColour="\033[1;31mRED\033[0m";
                    break;
            case 2: players[i].col=BLU;players[i].playerColour="\033[1;34mBLU\033[0m";
                    break;
            case 3: players[i].col=GREEN;players[i].playerColour="\033[1;32mGREEN\033[0m";
                    break;
            case 4: players[i].col=YELLOW;players[i].playerColour="\033[1;33mYELLOW\033[0m";
                    break;
            case 5: players[i].col=PINK;players[i].playerColour="\033[1;35mPINK\033[0m";
                    break;
            case 6: players[i].col=CYAN;players[i].playerColour="\033[1;36mCyan\033[0m";
            default: break;
        }
        
        loop=0;
        for(int x=0; x<i; x++)
            {
                if (players[i].col==players[x].col) 
                {
                    printf("Error: Colour already seleceted!\n");
                    loop=1;
                }
        }
        if(loop==0)
            i++;
    }
}