/* 
 * File:   game_logic.c
 * Author: Morgan & Iva
 *
 * This file holds all functions required to play the game - function
 * to place tokens at the beginning of the game, function to play the game and
 * function to print the board after each turn/move
 * 
 */


#include "game_init.h" //Library which holds function prototypes for initilization & structs & enums for game
#include "game_logic.h" //Library which holds function prototypes to play the game
#include <stdio.h> //Standard input/output library in C
#include <time.h> //Needed for srand(time(NULL)) to work
#include <stdlib.h> //Standard C library which includes function such as memory allocation & rand() 

//Function prototype for printing a line 
void printLine(); 

int askRow();

int askColumn();

//Function prototype for moving token up/down or forward 
void playerMovement(square board[NUM_ROWS][NUM_COLUMNS],int row,int column,int upDown,int forward);

//Function prototype for rolling the dice 
int rollDice();

//Function prototype for adding tokens to a stack on a square
struct token * push(player value, struct token *top);

//Function prototype for removing tokens from a stack on a square
struct token * pop(struct token *top);

/*Function prototype for checking if there is a token in the row to be moved. 
It also checks if a token in an obstacle square can move.*/
int moveAndObsCheck(square board[NUM_ROWS][NUM_COLUMNS], int row);

/*Function prototype to check all squares in columns before token in obstacle square
in order to see if it can move*/
int checkBoard(square board[NUM_ROWS][NUM_COLUMNS],int column);

//Function prototype to increment how many tokens a player has in the last column 
void checkNumTokensLastCol(square board[NUM_ROWS][NUM_COLUMNS], int column, int roll, int numPlayers, player players[]);

struct token *top[NUM_ROWS][NUM_COLUMNS]; //Declare pointer to top of each stack
struct token *curr[NUM_ROWS][NUM_COLUMNS]; //Declare pointer for current element in each stack 

/*
 * Returns the first letter associated with the color of the token
 * 
 * Input: t - pointer to a token
 * Output: initial of the color of the token
 */
char print_token(token *t,char **colC,square type){
    /*When a token is on an obstacle square print color in white to indicate that the
    square is an obstacle*/
#ifdef COLOR_TRUE
    if(type.type==OBSTACLE){
#endif
        if((*t).col== PINK) *colC="P";
        if((*t).col== RED) *colC="R";
        if((*t).col== BLU) *colC="B";
        if((*t).col== GREEN) *colC="G";
        if((*t).col== CYAN) *colC="C";
        if((*t).col== YELLOW) *colC="Y";    
#ifdef COLOR_TRUE
    }
    else{
        /*If a token is on a normal square print the first letter of the color in
         the corresponding color, hence "\033" and the ANSI code of each color*/
        if((*t).col== PINK) *colC="\033[1;35mP\033[0m";
        if((*t).col== RED) *colC="\033[1;31mR\033[0m";
        if((*t).col== BLU) *colC="\033[1;34mB\033[0m";
        if((*t).col== GREEN) *colC="\033[1;32mG\033[0m";
        if((*t).col== CYAN) *colC="\033[1;36mC\033[0m";
        if((*t).col== YELLOW) *colC="\033[1;33mY\033[0m";
    }
#endif
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
                print_token(board[i][j].stack,&c,board[i][j]);
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

/*
 * Prints a horizontal line 
 */
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
    int minNumOfTokens = 0; //Initialize min number of tokens to 0
    int selectedSquare = 0; //Initialize selectedSquare to 0
    int i=0; //Initialize conter to 0
    //Loop to initialize all squares on board
    while(i<NUM_ROWS){ 
        int j=0; //Initialize counter for columns to 0
        while(j<NUM_COLUMNS){
            board[i][j].numTokens=0; //Initialize numTokens of each square to 0
            top[i][j]=NULL; //Initialize top of each square to NULL
            curr[i][j]=NULL; //Initialize curr of each square to NULL
            j++; //Increment counter for columns
        }
        i++; //Increment counter for rows
    }
    
    //Loop to allow each player to place their 4 tokens on the first column
    for (int i=0; i<4; i++)
    {
        for(int j=0; j<numPlayers; j++)
        {
            int loop=1; //This variable will be used to determine when to exit the while loop
            while(loop==1){
                printf("%s (%s) Place token on row[0-5]:", players[j].playername,players[j].playerColour); //Prompt user to select a square to place their token on
                scanf("%d", &selectedSquare); //Obtain value from user
                //Check if the selected square is valid i.e between 0 and 5 
                if(selectedSquare>=0&&selectedSquare<=5)
                {
                    //Check that the player has selected a square which contains min tokens and also does not contain their token on top already 
                    if ((board[selectedSquare][0].numTokens==minNumOfTokens && minNumOfTokens==0 ) || (board[selectedSquare][0].numTokens==minNumOfTokens && board[selectedSquare][0].stack->col!=players[j].col))
                    {
                        board[selectedSquare][0].stack = (token*)malloc(sizeof(token)); //Allocate memory to the stack on the selected square 
                        board[selectedSquare][0].stack->col = players[j].col; //Set the stack color to the player's color 
                        top[selectedSquare][0]=push(players[j],top[selectedSquare][0]); //Call function to add token to the stack
                        board[selectedSquare][0].numTokens++; //Increment number of tokens on the selected square 
                        loop=0; //Will now exit while loop
                    }
                    else{printf("ERROR: This square does not contain minimum number of tokens (%d tokens) OR your token is on top\n", minNumOfTokens);} 
                }
                else{printf("Invalid Row, Try again!\n");}    
            }
            if (((numPlayers*i)+j+1)%NUM_ROWS==0) 
                minNumOfTokens++; //Increment min number of tokens 
            print_board(board); //Print the board each time a token is placed 
        }
    }
}


/*
 * Play the game - ask each player if they wish to move one of their tokens up or
 * down and then allow them to roll and move a token forward
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players  
 */
void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers){ 
    int row,column,choice=3; //Variables to store selected row, column and if player wishes to move up/down
    int loop=1; //Will be used to determined when to exit the loop
    int i=0; //Initialize counter which keeps track of who's move it is to 0 to allow first player to go first
    
    //Loop to initialize numTokensLastCol to 0 for each player 
    for(int j=0; j<numPlayers; j++)
    {
        players[j].numTokensLastCol=0; //Initialize numTokensLastCol to 0
    }
    
    //Begin the game 
    while(loop==1){
        //If i exceeds numPlayers-1 set it back to 0 as it is the first player's turn again
        if(i>numPlayers-1)
            i=0;
        printf("%s (%s) move a token up/down? [1]Yes [0]No:", players[i].playername,players[i].playerColour); //Prompt user to input if they wish to move up/down
        scanf("%d",&choice); //Obtain value from user 
        
        //If user inputs an invalid choice keep looping until they select a valid one
        while(choice!=0 && choice!=1)
        {
            printf("Invalid choice! Try again:"); //Prompt user to input a valid choice
            scanf("%d",&choice); //Obtain value from user 
        }
        
        //If user chooses to move a token up/down 
        if(choice==1)
        {
            int loopA=1; //Determines when to exit loop 
            while (loopA==1)
            {
                row=askRow();
                if(row==9){
                    break;
                }
                column=askColumn();
                if(board[row][column].numTokens>0 && board[row][column].stack->col==players[i].col) //Checks that selected square contains their token 
                {
                    if(board[row][column].type==OBSTACLE && checkBoard(board,column)!=2) //Checks if the selected token is stuck in obstacle square 
                        printf("Stuck in Obstacle, Try again!\n");
                    else
                        loopA=0; //Exit loop
                }
                else
                    printf("You don't have a token here, Try again!\n"); //If selected square doesn't contain player's token loop again 
            }
            
/******************************************************************************/  
            
            int upDown=3; //Initialize upDown to 3 a
            //Allow player to select if they wish to move the token up or down if the token is in rows 1-4 i.e. is able to move both up or down 
            if(row>0 && row<5)
            {
                int loopC=1; //Determines when to exit loop 
                while(loopC==1)
                {
                    printf("%s (%s)move token up or down? [1]Up [0]Down:", players[i].playername,players[i].playerColour); //Prompt user to select if they wish to move token up or down
                    scanf("%d", &upDown); //Obtain value from user 
                    if (upDown==0 || upDown==1) //If choice is valid i.e. either 0 or 1 exit loop 
                        loopC=0;
                    else 
                        printf("Invalid choice, Try again!\n"); //If choice is invalid loop again 
                }
            }
            if(upDown==1 || row==5)
                playerMovement(board,row,column,-1,0); //Move token up
            if(upDown==0 || row==0)
                playerMovement(board,row,column,1,0); //Move token down
            print_board(board); //Print the board after token has been moved up or down  
        }
 
/******************************************************************************/  
        
        int roll = rollDice(); //Call function to roll dice 
        
        printf("%s (%s) you rolled a %d\n",players[i].playername,players[i].playerColour, roll); //Inform player what they have rolled 
        
/******************************************************************************/
        
        int checkType=moveAndObsCheck(board,roll); /*check possible move 1- normal has been checked 2- obstacle has been checked and normal can be moved*/
        /*this value is needed as it is possible there is a token that can and a token that cant be moved in the same row*/
        if (checkType==1 || checkType==2) /*only enters loop if there is a possible move*/
        {
            int loopD=1; //Determines when to exit loop 
            while(loopD==1)
            {
                column=askColumn();
                if(board[roll][column].numTokens>0) //Checks that selected square contains at least 1 token 
                    {
                        if((board[roll][column].type==OBSTACLE && checkType==1) && (checkBoard(board,column)!=2))/*Checks if token is on a obstacle square and hasn't been checked if it can move and if it can be moved*/
                            printf("Stuck in Obstacle, Try again!\n");
                        else
                            loopD=0; /*possible move can exit loop*/
                    }
                    else
                        printf("No token on this square, Try again!\n"); //If there is no token on selected square loop again 
                
            }
            if(column==7) //If a token is moved from column 7 to column 8 then numTokensLastCol must be incremented for whichever player owns the token 
                checkNumTokensLastCol(board,column,roll,numPlayers,players); //Checks who's token has been moved to column 8 and increments how many tokens this player has in last column
            playerMovement(board,roll,column,0,1); //Move selected token one square forward
            print_board(board); //Print the board after a token has been moved
        }
        else
            printf("No token on row %d to move\n",roll); //If the number rolled corresponds to a row with no tokens the player cannot move any token 
           
/******************************************************************************/ 
        
        //Loop to check if any player has won the game at the end of each player's move 
        for(int k=0; k<numPlayers; k++)
        {
            if(players[k].numTokensLastCol==3) //If a player has 3 tokens in the last column they've won 
            {
                printf("WINNER: %s (%s)\n", players[k].playername ,players[k].playerColour); //The winner's name and corresponding color is printed
                loop=0; //Breaks from the loop and the game ends 
            }          
        }
        
        i++; //Increment counter which keeps track of which player's go it is
    }  
}

/*
 * Function which acts as rolling a dice 
 * 
 * Output: Random integer between 0 and 5
 * 
 */
int rollDice()
{
    srand(time(NULL)); //Initializes the PRNG (Pseudo-Random Number Generator) to ensure rand() numbers are random each time
    int roll = rand() % 6; //Generates random number between 0 and 5
    return roll; //Return random number generated/"rolled"
}

void playerMovement(square board[NUM_ROWS][NUM_COLUMNS],int row,int column,int upDown,int forward)
{
    player sCol;
    
    sCol.col=board[row][column].stack->col;
    
    board[row+upDown][column+forward].stack = (token*)malloc(sizeof(token));
    top[row+upDown][column+forward]=push(sCol,top[row+upDown][column+forward]);
    board[row+upDown][column+forward].stack->col =sCol.col; 
    board[row+upDown][column+forward].numTokens++;
    
    board[row][column].stack = (token*)malloc(sizeof(token));
    top[row][column]=pop(top[row][column]);
    board[row][column].stack =top[row][column];
    board[row][column].numTokens--;
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

/*
 * This function checks for possible moves and breaks when if finds a move
 * if it returns 1 the first possible move is on a normal square and possible tokens on obstacles haven't been checked
 * when 2 the first move found was on a obstacle square and it can be moved also meaning all tokens on that row can be moved.
 * when 0 no possible moves
 * having the value set to 2 means the program doesn't need to re check tokens on obstacles when the user selects one
 */
int moveAndObsCheck(square board[NUM_ROWS][NUM_COLUMNS], int row){
    int obsPosition; /*holds the obstacle column*/
    int canMove=0;
    
    for(int i=0;i<NUM_COLUMNS;i++)/*less than num column as we don't ant to check column 8*/
    {
        if(canMove==1 || canMove==2) /*breaks if there is a possible move*/
            break;
        if(board[row][i].numTokens>0 && board[row][i].type==NORMAL)
        {
            canMove=1;
        }
        else if(board[row][i].numTokens>0 && board[row][i].type==OBSTACLE){
            obsPosition=i;
            canMove=checkBoard(board,obsPosition);
        }
    }
    return canMove; /*Function returns a 1 if its possible to move a token on a normal square*/
                    /*Function returns a 2 if its possible to move a token on a obstacle square*/
}

int checkBoard(square board[NUM_ROWS][NUM_COLUMNS],int column){
    for(int i=0; i<column;i++){
            for(int j=0; j<=NUM_ROWS;j++){
                if(board[j][i].numTokens>0){
                    return 0;
            }
        }
    }
    return 2; /*Function returns a 2 if its possible to move a token on a obstacle square*/
}

void checkNumTokensLastCol(square board[NUM_ROWS][NUM_COLUMNS], int column, int roll, int numPlayers, player players[])
{
    for(int i=0; i<numPlayers; i++)
    {
        if(players[i].col==board[roll][column].stack->col)
        {
            players[i].numTokensLastCol++;
            break;
        }
    }
}

int askRow()
{
    int row,loop=1;
    while(loop==1){
        printf("Select a row [0-5] or [9]Cancel:"); //Prompt user to select row of token they wish to move up/down
    scanf("%d",&row); //Obtain value from user 
    if(row>=0&&row<NUM_ROWS || row==9)//Checks that row is valid/in range 
        loop=0;
    else
        printf("Invalid Row, Try again!\n"); //If row is out of range print error message and loop again
    }
    return row;
}

int askColumn()
{
    int column,loop=1;
    while(loop==1){
        printf("Select a Column [0-7]:"); //Prompt user to select row of token they wish to move up/down
    scanf("%d",&column); //Obtain value from user 
    if(column>=0&&column<NUM_COLUMNS-1)//Checks that row is valid/in range 
        loop=0;
    else
        printf("Invalid Column, Try again!\n"); //If row is out of range print error message and loop again
    }
    return column;
}

