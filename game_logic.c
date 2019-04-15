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

struct token *top[NUM_ROWS][NUM_COLUMNS];
struct token *curr[NUM_ROWS][NUM_COLUMNS];

/*
 * Returns the first letter associated with the color of the token
 * 
 * Input: t - pointer to a token
 * Output: initial of the color of the token
 */
/*
 * Prints the board
 * 
 * Input: the board to be printed. 
 */
char print_token(token *t,char **colC){
    int x=0;
    if((*t).col== PINK) *colC="\033[1;35mP\033[0m";x=1;
    if((*t).col== RED) *colC="\033[1;31mR\033[0m";x=1;
    if((*t).col== BLU) *colC="\033[1;34mB\033[0m";x=1;
    if((*t).col== GREEN) *colC="\033[1;32mG\033[0m";x=1;
    if((*t).col== CYAN) *colC="\033[1;36mC\033[0m";x=1;
    if((*t).col== YELLOW) *colC="\033[1;35mY\033[0m";x=1;
    if (x=0)
        *colC="\0";


}

/*
 * Prints the board
 * 
 * Input: the board to be printed. 
 */
void print_board(square board[NUM_ROWS][NUM_COLUMNS]){
    printf("\n\n                THE BOARD\n");
    for(int i =0; i < NUM_ROWS; i++){
       
        //prints an horizontal line
        printLine();
        //prints the row number
        printf(" %d ", i);
        char *c = "\0" ;
        //if the square (i,j) is occupied,
        //c is assigned the initial of the color of the token that occupies the square
        for (int j = 0; j < NUM_COLUMNS; j++){
            if(board[i][j].stack != NULL){
                print_token(board[i][j].stack,&c);
            }
            //if the square (i,j) is empty
            else{
                //c is assigned 'X' if the square represents an obstacle
                if(board[i][j].type == OBSTACLE)
                    c = "X";
                //c is assigned an empty space otherwise
                else c = " ";
            }
            printf("| %s ",c);
        }
        printf ("|\n");
    }
    printLine();
    //prints the number of the columns at the end of the board
    printf("     0   1   2   3   4   5   6   7   8\n\n\n");
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
        board[i][0].numTokens=0;
        int j=0;
        while(j<8){
            top[i][j]=NULL;
            curr[i][j]=NULL;
            j++;
        }
        i++;
    }
    
    for (int i=0; i<4; i++)
    {
        for(int j=0; j<numPlayers; j++)
        {
            int loop=1;
            while(loop==1){
                printf("%s (%s) Place token on row[0-5]:", players[j].playername,players[j].playerColour);
                scanf("%d", &selectedSquare);
                if(selectedSquare>=0&&selectedSquare<=5)
                {
                    if ((board[selectedSquare][0].numTokens==minNumOfTokens && minNumOfTokens==0 ) || (board[selectedSquare][0].numTokens==minNumOfTokens && board[selectedSquare][0].stack->col!=players[j].col))
                    {
                        board[selectedSquare][0].stack = (token*)malloc(sizeof(token));
                        board[selectedSquare][0].stack->col = players[j].col;
                        top[selectedSquare][0]=push(players[j],top[selectedSquare][0]);
                        board[selectedSquare][0].numTokens++;
                        loop=0; 
                    }
                    else{printf("ERROR: This square does not contain minimum number of tokens (%d tokens) OR your token is on top\n", minNumOfTokens);}
                }
                else{printf("Invalid Row, Try again!\n");}    
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
    int row,column,choice=3, winner=0;
    int loop=1;
    while(loop==1){
        int i=0;

        //TO BE IMPLEMENTED#
        printf("%s move a token up/down? [1]Yes [0]No:", players[i].playername);
        scanf("%d",&choice);
        
        while(choice!=0 && choice!=1)
        {
            printf("Invalid choice! Try again:");
            scanf("%d",&choice);
        }
        
        if(choice==1)
        {
            int loopA=1;
            while (loopA==1)
            {
                printf("Row [0-5]:");
                scanf("%d",&row);
                if(row>=0&&row<=5)
                {
                    int loopB=1;
                    while (loopB==1)
                    {
                        printf("Column [0-8]:"); 
                        scanf("%d",&column);
                        if(column>=0&&column<=8)
                        {
                            loopB=0;
                            if(board[row][column].numTokens>0 && top[row][column]->col==players[i].col)
                            {
                                loopA=0;
                            }
                            else{printf("You don't have a token here, Try again!\n");}
                               
                        }
                        else{printf("Invalid Column, Try again!\n");}
                    }
                }
                else{printf("Invalid Row, Try again!\n");} 
            }
            int upDown=3;
            if(row>0 && row<5)
            {
                int loopC=1;
                while(loopC==1)
                {
                    printf("%s move token up or down? [1]Up [0]Down:", players[i].playername);
                    scanf("%d", &upDown);
                    if (upDown==0 || upDown==1)
                    {
                        loopC=0;
                    }
                    else 
                    {
                        printf("Invalid choice, Try again!\n");
                    }
                    
                }
            }
            if(upDown==1 || row==5)
                playerMovement(board,row,column,-1,0);
            if(upDown==0 || row==0)
                playerMovement(board,row,column,1,0);
            print_board(board); 
        }
        
        
        int roll = rollDice();
        
        printf("%s you rolled a %d\n",players[i].playername, roll);
        
        int loopD = 1;
        
        while(loopD==1)
        {
            printf("%s select a column[0-8]:", players[i].playername);
            scanf("%d",&column);
            if(column>=0 && column<=8)
            {
                if(board[roll][column].numTokens>0)
                {
                    moveForward(board, players[i],column,roll);
                    print_board(board);
                    loopD=0;
                }
                else 
                {
                    printf("ERROR: No token on this square, Try again!\n");
                }  
            }
            else
            {
                printf("ERROR: Invalid column, Try again!\n");
            }
        }
        
        if(players[i].numTokensLastCol==3)
        {
            printf("WINNER: %s\n", players[i].playername);
            loop=0;
        }
        
        /*i++;
        
        if(i==numPlayers && loop==1)
        {
            i=0;
        }*/
    }  
}

int rollDice()
{
    srand(time(NULL));
    int roll = rand() % 6;
    return roll;
    
}

void playerMovement(square board[NUM_ROWS][NUM_COLUMNS],int row,int column,int upDown,int forward)
{
    player sCol;
    
    sCol.col=board[row][column].stack->col;
    
    board[row+upDown][column+forward].stack = (token*)malloc(sizeof(token));
    top[row+upDown][column+forward]=push(sCol,top[row+upDown][column]);
    board[row+upDown][column+forward].stack->col =sCol.col; 
    board[row+upDown][column+forward].numTokens++;
    
    board[row][column].stack = (token*)malloc(sizeof(token));
    top[row][column]=pop(top[row][column]);
    board[row][column].stack =top[row][column];
    board[row][column].numTokens--;
}


void moveForward(square board[NUM_ROWS][NUM_COLUMNS], player currentPlayer, int column, int roll)
{
    board[roll][column].stack = (token*)malloc(sizeof(token));
    top[roll][column]=pop(top[roll][column]);
    board[roll][column].stack =top[roll][column];
    board[roll][column].numTokens--;
    board[roll][column+1].stack = (token*)malloc(sizeof(token));
    top[roll][column+1]=push(currentPlayer,top[roll][column+1]);
    board[roll][column+1].stack->col =currentPlayer.col; 
    
}

struct token * push(player value, struct token *top){
    struct token *curr = top;
    top = malloc(sizeof(token));
    top->col = value.col;
    top->next = curr;
    return top;
}

struct token * pop(struct token *top){
    struct token *curr = top;
    if(curr!=NULL){
        top = curr->next;
        free(curr);
    }
    return top;
}

