/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "game_init.h"
#include "game_logic.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void printLine();

/*
 * Returns the first letter associated with the color of the token
 * 
 * Input: t - pointer to a token
 * Output: initial of the color of the token
 */
char print_token(token *t){
    if((*t).col== PINK) return 'P';
    if((*t).col== RED) return 'R';
    if((*t).col== BLU) return 'B';
    if((*t).col== GREEN) return 'G';
    if((*t).col== ORANGE) return 'O';
    if((*t).col== YELLOW) return 'Y';
    return '\0';
}

/*
 * Prints the board
 * 
 * Input: the board to be printed. 
 */
void print_board(square board[NUM_ROWS][NUM_COLUMNS]){
    printf("                THE BOARD\n");
    for(int i =0; i < NUM_ROWS; i++){
       
        //prints an horizontal line
        printLine();
        //prints the row number
        printf(" %d ", i);
        char c = '\0' ;
        //if the square (i,j) is occupied,
        //c is assigned the initial of the color of the token that occupies the square
        for (int j = 0; j < NUM_COLUMNS; j++){
            if(board[i][j].stack != NULL){
                c = print_token(board[i][j].stack);
            }
            //if the square (i,j) is empty
            else{
                //c is assigned 'X' if the square represents an obstacle
                if(board[i][j].type == OBSTACLE)
                    c = 'X';
                //c is assigned an empty space otherwise
                else c = ' ';
            }
            printf("| %c ", c);
        }
        printf ("|\n");
    }
    printLine();
    //prints the number of the columns at the end of the board
    printf("     0   1   2   3   4   5   6   7   8\n");
}

void printLine(){
  printf("   -------------------------------------\n");  
}

/*
 * Place tokens in the first column of the board
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players  
 */
void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers){
    // TO BE IMPLEMENTED
    int minNumOfTokens = 0;
    int selectedSquare = 0;
    int i=0;
    while(i<6){ 
    board[i][0].numTokens =0;
    board[i][0].stack = (token*)malloc(sizeof(token));
    board[i][0].stack->col = NONE;
    i++;
    }
    
    for (int i=0; i<4; i++)
    {
        for(int j=0; j<numPlayers; j++)
        {
            printf("Player %d please select a square\n", j);
            scanf("%d", &selectedSquare);
            
            
            if(board[selectedSquare][0].numTokens==minNumOfTokens && board[selectedSquare][0].stack->col!=players[j].col)
            {
                board[selectedSquare][0].stack = (token*)malloc(sizeof(token));
                board[selectedSquare][0].stack->col = players[j].col;
                board[selectedSquare][0].numTokens++;
                
            }
            else
            {
                while (board[selectedSquare][0].numTokens!=minNumOfTokens || board[selectedSquare][0].stack->col==players[j].col)
                {
                    printf("Error: Selected square doesn't contain min number of token OR contains your token\n");
                    printf("Please select a valid square:\n");
                    scanf("%d", &selectedSquare);
                }
                board[selectedSquare][0].stack = (token*)malloc(sizeof(token));
                board[selectedSquare][0].stack->col = players[j].col;
                board[selectedSquare][0].numTokens++;
            }       
            
            if (((numPlayers*i)+j+1)%NUM_ROWS==0)
                minNumOfTokens++;
            
            print_board(board);
        }
    }

}


/*
 * Place tokens in the first column of the board
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players  
 */

void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers){ 
    int a,b,choice,upDown;
    //for(int i=0; i<numPlayers; i++){

        //TO BE IMPLEMENTED
        printf("Would you like to move a token up/down?\n");
        printf("Enter 1 for yes OR 0 for no:\n");
        scanf("%d",&choice);
        
        while(choice!=0 && choice!=1)
        {
            printf("ERROR: Invalid choice!\n");
            printf("Enter 1 for yes OR 0 for no:\n");
            scanf("%d",&choice);
        }
        
        if(choice==1)
        {
            printf("Please choose row of token you'd like to move:\n");
            scanf("%d",&a);
            while(a<0 || a>5)
            {
                printf("ERROR: Invalid row!\n");
                printf("Please choose row of token you'd like to move:\n");
                scanf("%d",&a);
            }
            
            printf("Please choose column of token you'd like to move:\n");
            scanf("%d",&b);
            while(b<0 || b>8)
            {
                printf("ERROR: Invalid column!\n");
                printf("Please choose column of token you'd like to move:\n");
                scanf("%d",&b);
            }
            
            if(a!=0 && a!=5)
            {              
                printf("Would you like to move this token up or down?\n");
                printf("Enter 1 for up OR 0 for down:\n");
                scanf("%d", &upDown);
                while(upDown!=0 && upDown!=1)
                {
                    printf("ERROR: Invalid choice!\n");
                    printf("Enter 1 for up OR 0 for down:\n");
                    scanf("%d",&upDown);
                }
            }
         
            if(upDown==1 || a==5)
            {
                playerMovement(board,players[0],a,b,-1);
            }
            else if(upDown==0 || a==0)
            {
                playerMovement(board,players[0],a,b,1);
            }
                     
            print_board(board);          
        }
        

        /*int roll = rollDice();
        
        printf("Column");
        scanf("%d",&b);
        board[roll][b+1].stack = (token*)malloc(sizeof(token));
        board[roll][b+1].stack->col =players[i].col;
        
        board[roll][b].stack = (token*)malloc(sizeof(token));
        board[roll][b].stack->col =NONE;
        
        print_board(board);*/
        
    
        
      
        /*if(i==(numPlayers-1))
        {
            i=0;
        }
        
        if(players[i].numTokensLastCol==3)
        {
            break;
        }   */
    //}
 
    
}

int rollDice()
{
    srand(time(NULL));
    int roll = rand() % 6;
    printf("You rolled a %d\n",roll);
    return roll;
    
}

void playerMovement(square board[NUM_ROWS][NUM_COLUMNS], player currentPlayer,int row,int column,int upDown)
{
    board[row][column].stack = (token*)malloc(sizeof(token));
    board[row][column].stack->col =NONE;
    board[row+upDown][column].stack = (token*)malloc(sizeof(token));
    board[row+upDown][column].stack->col =currentPlayer.col; 
}



