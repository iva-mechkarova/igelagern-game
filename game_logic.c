/* File:   game_logic.c
 * Author: Morgan & Iva
 * This file holds all functions required to play the game - function
 * to place tokens at the beginning of the game, function to play the game and
 * function to print the board after each turn/move
 */
/*****************************************************/
#include "game_init.h" //Library which holds function prototypes for initilization & structs & enums for game
#include "game_logic.h" //Library which holds function prototypes to play the game
#include <stdio.h> //Standard input/output library in C
#include <time.h> //Needed for srand(time(NULL)) to work
#include <stdlib.h> //Standard C library which includes function such as memory allocation & rand() 
/*****************************************************/
//Function prototype for printing a line 
void printLine(); 

//Function prototype to prompt user to select a row and obtain value for row
int askRow(player player, int canCancel);

//Function prototype to prompt user to select a column and obtain value for column
int askColumn(player player);

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
void checkNumTokensLastCol(square board[NUM_ROWS][NUM_COLUMNS], int roll, int numPlayers, player players[]);

struct token *top[NUM_ROWS][NUM_COLUMNS]; //Declare pointer to top of each stack
struct token *curr[NUM_ROWS][NUM_COLUMNS]; //Declare pointer for current element in each stack 
/*****************************************************/
/*
 * Returns the first letter associated with the color of the token
 * 
 * Input: t - pointer to a token
 * Output: initial of the color of the token
 */
char print_token(token *t,char **colC,square type){
    /*When a token is on an obstacle square print color in white to indicate that the
    square is an obstacle only if color is ture*/
#ifdef COLOR_TRUE
    if(type.type==OBSTACLE){
#endif
        if((*t).col== PINK) *colC="P";
        if((*t).col== RED) *colC="R";
        if((*t).col== BLU) *colC="B";
        if((*t).col== GREEN) *colC="G";
        if((*t).col== CYAN) *colC="C";
        if((*t).col== YELLOW) *colC="Y";    
#ifdef COLOR_TRUE /*Prints color if true*/
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
/*****************************************************/
/* Prints the board Input: the board to be printed. */
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
/*****************************************************/
/* Prints a horizontal line */
void printLine(){
  printf("   -------------------------------------\n");  
}
/*****************************************************/
/*
 * Place tokens in the first column of the board
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players  
 */
void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers){
    int minNumOfTokens = 0; //Initialize min number of tokens to 0
    int selectedSquare = 0; //Initialize selectedSquare to 0
    int i=0; //Initialize counter to 0
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
/*****************************************************/
    //Loop to allow each player to place their 4 tokens on the first column
    for (int i=0; i<4; i++)
    {
        for(int j=0; j<numPlayers; j++)
        {
            int loop=1; //This variable will be used to determine when to exit the while loop
            while(loop==1){
                int tokenMatch=0; /*if the token match is 1 means only one square to place token and color matching on stack is allowed*/
                selectedSquare=askRow(players[j],0); //Set selected square value to value obtained from user in function askRowPlaceTokens
                    //Check that the player has selected a square which contains min tokens and also does not contain their token on top already 
                if ((board[selectedSquare][0].numTokens==minNumOfTokens && minNumOfTokens==0 ) || (board[selectedSquare][0].numTokens==minNumOfTokens && board[selectedSquare][0].stack->col!=players[j].col))
                {
                    board[selectedSquare][0].stack = (token*)malloc(sizeof(token)); //Allocate memory to the stack on the selected square 
                    board[selectedSquare][0].stack->col = players[j].col; //Set the stack color to the player's color 
                    top[selectedSquare][0]=push(players[j],top[selectedSquare][0]); //Call function to add token to the stack
                    board[selectedSquare][0].numTokens++; //Increment number of tokens on the selected square 
                    loop=0; //Will now exit while loop
                }
                else
                    printf("This square does not contain minimum number of tokens (%d tokens) OR your token is on top\n", minNumOfTokens);
            }
            if (((numPlayers*i)+j+1)%NUM_ROWS==0) 
                minNumOfTokens++; //Increment min number of tokens 
            print_board(board); //Print the board each time a token is placed 
        }
    }
}
/*****************************************************/
/*
 * Play the game - ask each player if they wish to move one of their tokens up or
 * down and then allow them to roll and move a token forward
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
        players[j].numTokensLastCol=0; //Initialize numTokensLastCol to 0
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
                row=askRow(players[i],1); //Set row value to value for row obtained from user 
                if(row==9){
                    break; //If user chooses to cancel i.e. select 9 exit the loop
                }
                column=askColumn(players[i]); //Set column value to value obtained for column from user
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
            int upDown=3; //Initialize upDown to 3 as this is not an option, only 0 (Down) and 1 (Up) are 
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
            if(upDown==1 || row==5) //Move up in row 5 as it is not possible to move down 
                playerMovement(board,row,column,-1,0); //Move token up
            if(upDown==0 || row==0) //Move down in row 0 as it is not possible to move up
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
                column=askColumn(players[i]);
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
                checkNumTokensLastCol(board,roll,numPlayers,players); //Checks who's token has been moved to column 8 and increments how many tokens this player has in last column
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
/*****************************************************/
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

/*
 * Function which is called whenever a token is to be moved in any direction  
 * 
 * Input: The board (2-D array of squares), the row of the token to be moved, the
 * column of the token to be moved, if it is being moved up or down (1 for down,
 * -1 for up and 0 for neither) and if it is being moved forward (1[yes] or 0[no]) 
 * 
 */
void playerMovement(square board[NUM_ROWS][NUM_COLUMNS],int row,int column,int upDown,int forward)
{
    player sCol; //Declare variable of type player to store square's colour 
    
    sCol.col=board[row][column].stack->col; //Set colour of square to colour of current square 
    
    board[row+upDown][column+forward].stack = (token*)malloc(sizeof(token)); //Dynamically allocate memory for stack on new square 
    top[row+upDown][column+forward]=push(sCol,top[row+upDown][column+forward]); //Add token to stack on new square by setting the top to top returned from push function
    board[row+upDown][column+forward].stack->col =sCol.col; //Set colour of new square to the colour of the token that has been moved from square you selected 
    board[row+upDown][column+forward].numTokens++; //Increment number of tokens on new square as there is clearly one more token on it 
    
    board[row][column].stack = (token*)malloc(sizeof(token)); //Dynamically allocate memory to stack of square that token has moved from 
    top[row][column]=pop(top[row][column]); //Remove element from this square's stack by setting top to top returned from pop function 
    board[row][column].stack =top[row][column]; //Set stack of previous square to top of this square 
    board[row][column].numTokens--; //Decrement number of tokens on this square as there has been a token moved from it 
}

/*
 * Function which is called to add elements/tokens to stack
 * 
 * Input: the colour of the token being moved (player value) and a pointer to a variable
 * of type struct token
 * 
 * Output: The new top for the square 
 * 
 */
struct token * push(player value, struct token *top){
    struct token *curr = top; //Declare pointer which is equal to top (when top changed curr changes)
    top = malloc(sizeof(token)); //Dynamically allocate memory to top
    top->col = value.col; //Set value of top to colour of token that has been moved
    top->next = curr; //Set next pointer to curr which is the new token added
    return top; //Return top of stack 
}

/*
 * Function which is called to remove elements/tokens from stack 
 * 
 * Input: A pointer to a variable of type struct token
 * 
 * Output: The new top for the square (token underneath the token which was moved away)
 * 
 */
struct token * pop(struct token *top){
    struct token *curr = top; //Declare pointer which is equal to top (when top changes curr changes)
    //Check that there is a token on the square to be removed i.e. curr/top is not NULL
    if(curr!=NULL){
        top = curr->next; //Set top to next pointer 
        free(curr); //Deallocates memory previously allocated in push function 
    }
    return top; //Return the top of stack 
}

/*
 * This function checks for possible moves and breaks when if finds a move
 * 
 * Input: Board (2-D array of squares) and row (number rolled on dice)
 *
 * Output: If it returns 1 the first possible move is on a normal square and possible tokens on obstacles haven't been checked.
 * When 2 the first move found was on a obstacle square and it can be moved also meaning all tokens on that row can be moved.
 * When 0 no possible moves
 * having the value set to 2 means the program doesn't need to re check tokens on obstacles when the user selects one
 * 
 */
int moveAndObsCheck(square board[NUM_ROWS][NUM_COLUMNS], int row){
    int obsPosition; /*holds the obstacle column*/
    int canMove=0; //Initialize to 0
    
    for(int i=0;i<NUM_COLUMNS-1;i++)/*less than num column-1 as we don't ant to check column 8*/
    {
        if(canMove==1 || canMove==2) /*breaks if there is a possible move*/
            break;
        if(board[row][i].numTokens>0 && board[row][i].type==NORMAL)
        {
            canMove=1; //First possible move is on a normal square 
        }
        else if(board[row][i].numTokens>0 && board[row][i].type==OBSTACLE){
            obsPosition=i; //obsPosition is set to the column that the obstacle is in
            canMove=checkBoard(board,obsPosition); //Calls function to check if token in obstacle square can move yet 
        }
    }
    
    return canMove; /*Function returns a 1 if its possible to move a token on a normal square*/
                    /*Function returns a 2 if its possible to move a token on a obstacle square*/
}

/*****************************************************/
/*
 * This function checks if its possible to move token on obstacle square yet, i.e. it
 * checks if there are any tokens in any of the columns before the obstacle square -
 * token cannot move until all other tokens are at least in the column of the obstacle square  
 * 
 * Input: Board (2-D array of squares) and column of obstacle square
 * 
 * Output: If it returns 0 then the token in the obstacle square cannot move but if 
 * it returns 2 then it can
 * 
 */
int checkBoard(square board[NUM_ROWS][NUM_COLUMNS],int column){
    //Checks if there is a token in any of the squares in columns before obstacle square 
    for(int i=0; i<column;i++){
            for(int j=0; j<=NUM_ROWS;j++){
                if(board[j][i].numTokens>0){
                    return 0; //If there are more than 0 tokens in one of these squares the token on obstacle square cannot move
            }
        }
    }
    return 2; /*Function returns a 2 if its possible to move a token on a obstacle square*/
}

/*****************************************************/
/*
 * This function checks if any of the players' tokens reach the last column and if 
 * they do it increments the variable storing how many tokens they have in last column
 * 
 * Input: Board (2-D array of squares), row of token being moved from column 7 to 8 (number rolled on dice),
 * number of players and array of players
 * 
 */
void checkNumTokensLastCol(square board[NUM_ROWS][NUM_COLUMNS], int roll, int numPlayers, player players[])
{
    //Loop to check which player's token is being moved from column 7 to 8
    for(int i=0; i<numPlayers; i++)
    {
        if(players[i].col==board[roll][7].stack->col) //If player's colour matches colour of stoken on square/top of stack then it is their token being moved
        {
            players[i].numTokensLastCol++; //Increment number of tokens this player has in last column
            break; //Escape loop when a player's colour matches the token's colour as player has been found 
        }
    }
}

/*****************************************************/
/*
 * This function asks the user to select a row 
 * 
 * Input: Array of players, integer where 1 means move can be canceled i.e. when
 * sidestepping and 0 when cannot be canceled i.e. placing tokens
 * 
 * Output: The number of the row selected 
 * 
 */
int askRow(player player,int canCancel)
{
    int row,loop=1; //Declare variable to store row and also another variable to determine when to exit loop
    while(loop==1){
        if(canCancel==1)
            printf("%s (%s) select a row [0-5] or [9]Cancel:", player.playername, player.playerColour); //Prompt user to select row of token they wish to move up/down
        else
            printf("%s (%s) select a row [0-5]:", player.playername, player.playerColour);
        scanf("%d",&row); //Obtain value from user
        if(row>=0&&row<NUM_ROWS || (canCancel==1 && row==9))//Checks that row is valid/in range
            loop=0; //Will exit loop
        else
            printf("Invalid Row, Try again!\n"); //If row is out of range print error message and loop again
    }
    return row; //Return value obtained for row
}

/*****************************************************/
/*
 * This function asks the user to select a column 
 * 
 * Input: Array of players 
 * 
 * Output: The number of the column selected
 */
int askColumn(player player)
{
    int column,loop=1; //Declare variable to store column and also another variable to determine when to exit loop 
    while(loop==1){
        printf("%s (%s) select a Column [0-7]:", player.playername, player.playerColour); //Prompt user to select column of token they wish to move up/down OR forward
        scanf("%d",&column); //Obtain value from user 
        if(column>=0&&column<NUM_COLUMNS-1)//Checks that row is valid/in range 
            loop=0; //Will exit loop
        else
            printf("Invalid Column, Try again!\n"); //If column is out of range print error message and loop again
    }
    return column; //Return value obtained for column
}
/*****************************************************/