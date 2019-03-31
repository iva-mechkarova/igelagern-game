/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "game_init.h"
#include "game_logic.h"
#include <stdio.h>
#include <string.h>


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
        printf("Player For Position %d :",i);
        fgets(players[i].playername,10,stdin);
        if(players[i].playername[0] == '\n')
            break;
        i++;
    }
    return i;
}

int initialize_colour(player players[],int numPlayers){   
    int i=0,option,loop;
    printf("----------------------Colours----------------------\n");
    printf("[1]RED [2]BLUE [3]GREEN [4]YELLOW [5]PINK [6]ORANGE\n");
    printf("---------------------------------------------------\n");
    
    while(i<numPlayers)
    {
        printf("Select colour for %s",players[i].playername);
        scanf("%d",&option);
        
        switch(option){
            case 1: players[i].playersToken.col=RED;
                    break;
            case 2: players[i].playersToken.col=BLU;
                    break;
            case 3: players[i].playersToken.col=GREEN;
                    break;
            case 4: players[i].playersToken.col=YELLOW;
                    break;
            case 5: players[i].playersToken.col=PINK;
                    break;
            case 6: players[i].playersToken.col=ORANGE;
            default: break;
        }
        
        loop=0;
        for(int x=0; x<i; x++)
            {
                if (players[i].playersToken.col==players[x].playersToken.col) 
                {
                    printf("Error colour already seleceted!\n");
                    loop=1;
                }
        }
        if(loop==0)
            i++;
    }
}