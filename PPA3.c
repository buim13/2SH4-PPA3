#include <stdio.h>
#include "MacUILib.h"
#include <time.h>
#include "myStringLib.h"   // This is your first custom C library

// [TODO] Import the required library for rand() and srand()
// [TODO] Import the required library for accessing the current time - for seeding random number generation





// PREPROCESSOR DIRECTIVE CONSTANTS
// ================================
// For program-wide constants, define them here using #define.  Add as seen needed.
#define ROW 10
#define COL 20
// [COPY AND PASTE FROM PPA2] Copy your additional preprocessor constants from PPA2 and paste them below
char content[ROW][COL] = {
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'}
    };

char input;

struct objPos{
    int x; // x-coordinate of an object
    int y; // y-coordinate of an object
    char symbol; // ASCII symbol of the object to be drawn on the screen
};
struct objPos player;
struct objPos list[5];

enum FSMMode {
    START,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
enum FSMMode myFSMMode;
// [TODO] Then, define more constants here as seen needed.
int toggle = 0;
int win=0;



// GLOBAL VARIABLES
// ================================

int exitFlag; // Program Exiting Flag

// [COPY AND PASTE FROM PPA2] Copy your additional global from PPA2 and paste them below

// [TODO] Declare More Global Variables as seen needed.
const char goalStr[] = "McMaster-ECE";
// [TODO] Declare Global Pointers as seen needed / instructed in the manual.
char * mysteryPtr;
char ** listMalloc;
int moveCount  = 0;






// FUNCTION PROTOTYPES
// ================================
// Declare function prototypes here, so that we can organize the function implementation after the main function for code readability.

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

// [TODO] In PPA3, you will need to implement this function to generate random items on the game board
//        to set the stage for the Scavenger Hunter game.
// list[]       The pointer to the Item Bin
// listSize     The size of the Item Bin (5 by default)
// playerPos    The pointer to the Player Object, read only.
// xRange       The maximum range for x-coordinate generation (probably the x-dimension of the gameboard?)
// yRange       The maximum range for y-coordinate generation (probably the y-dimension of the gameboard?)
// str          The pointer to the start of the Goal String (to choose the random characters from)
void GenerateItems(struct objPos list[], const int listSize, const struct objPos *playerPos, const int xRange, const int yRange, const char* str);




// MAIN PROGRAM
// ===============================
int main(void)
{

    Initialize();

    while(!exitFlag)  
    {
        GetInput();

        RunLogic();

        DrawScreen();

        LoopDelay();
    }

    CleanUp();

}




// INITIALIZATION ROUTINE
// ===============================
void Initialize(void)
{
    MacUILib_init();

    MacUILib_clearScreen();

    // [COPY AND PASTE FROM PPA2] Copy your initialization routine from PPA2 and paste them below

    
    // [TODO] Initialize any global variables as required.
    exitFlag = 0;  // 0 - do not exit, non-zero - exit the program
    
    player.x = 5;
    player.y = 10;
    player.symbol = '@';
    
    content[player.x][player.y] = player.symbol;
    // [TODO] Allocated heap memory for on-demand variables as required.  Initialize them as required.
    mysteryPtr = (char*)malloc((my_strlen(goalStr)+1) * sizeof(char));
    int i,j;
    for (i=0; i<my_strlen(goalStr); i++)
        mysteryPtr[i] = '?';
    mysteryPtr[i] = '\0';    
    // [TODO] Seed the random integer generation function with current time.
    srand(time(NULL));
    // [TODO] Generate the initial random items on the game board at the start of the game.
    GenerateItems(list, 5, &player, 10, 20, goalStr);
    
}




// INPUT COLLECTION ROUTINE
// ===============================
void GetInput(void)
{

    // Asynchronous Input - non blocking character read-in
    
    // [COPY AND PASTE FROM PPA2] Copy your input collection routine from PPA2 and paste them below
    if (MacUILib_hasChar()){
        input = MacUILib_getChar();
    }
    // [TODO] Though optional for PPA3, you may insert any additional logic for input processing.

   
}




// MAIN LOGIC ROUTINE
// ===============================
void RunLogic(void)
{
    // [COPY AND PASTE FROM PPA2] Copy your main logic routine from PPA2 and paste them below
    int i,j;
    if(input != 0)  // if not null character
    {
        switch(input)
        {                      
            case ' ':  // exit
                exitFlag = 1;
                break;

            // Add more key processing here
            case 'w':
                if (myFSMMode != DOWN){
                    myFSMMode = UP;
                }
                break;
            // Add more key processing here
            case 'a':
                if (myFSMMode != RIGHT){
                    myFSMMode = LEFT;
                }
                break;
            // Add more key processing here   
            case 's':
                if (myFSMMode!=UP){
                    myFSMMode = DOWN;
                }
                break;
                
            case 'd':
                if (myFSMMode!=LEFT){
                    myFSMMode = RIGHT;
                }
                break;
            case '.':
            toggle =!toggle;
                for(j=0; j<5; j++){
                content[list[j].x][list[j].y] = ' ';
                }
                GenerateItems(list, 5, &player, 10, 20, goalStr);

                input=0;
                break; 
            default:
                break;
        }
    }

    switch(myFSMMode){
        case LEFT:
            content[player.x][player.y] =' ';
            if (player.y<2){
                player.y=COL-2;
            }
            player.y--;
            moveCount++;
            content[player.x][player.y]=player.symbol;
            break;
        case RIGHT:
            content[player.x][player.y] =' ';
            if (player.y>17){
                player.y=1;
            }
            player.y++;
            moveCount++;
            content[player.x][player.y]=player.symbol;
            break;
        case UP:
            content[player.x][player.y] =' ';
            if (player.x<0){
                player.x=ROW;
            }
            player.x--;
            moveCount++;
            content[player.x][player.y]=player.symbol;
            break;
        case DOWN:
            content[player.x][player.y] =' ';
            player.x++;
            if (player.x>ROW){
                player.x=0;
            }
            content[player.x][player.y]=player.symbol;
            moveCount++;
            break;
        default:
            break;
    }
    // [TODO]   Implement the Object Collision logic here
    //
    //      Simple Collision Algorithm
    //      1. Go through all items on board and check their (x,y) against the player object x and y.
    //      2. If a match is found, use the ASCII symbol of the collided character, and 
    //         find all the occurrences of this ASCII symbol in the Goal String
    //      3. For every occurrence, reveal its ASCII character at the corresponding location in the
    //         Collected String
    //      4. Then, determine whether the game winning condition is met.
    
    for (i=0; i<5; i++){
        if (player.x == list[i].x && player.y == list[i].y){
            for(j=0; j<5; j++){
                content[list[j].x][list[j].y] = ' ';
            }
            for (j=0; j<13; j++){
                if (goalStr[j]==list[i].symbol){
                    mysteryPtr[j] = list[i].symbol;
                } 
            }
            GenerateItems(list, 5, &player, 10, 20, goalStr);
            break;
        }
    }

    // [TODO]   Implement Game Winning Check logic here
    //
    //      Game Winning Check Algorithm
    //      1. Check if the contents of the Collected String exactly matches that of the Goal String.
    //         YOU MUST USE YOUR OWN my_strcmp() function from Lab 3.
    //      2. If matched, end the game.
    //      3. Otherwise, discard the current items on the game board, and 
    //         generate a new set of random items on the board.  Game continues.
    if (my_strcmp(goalStr, mysteryPtr)==1){
        win=1;
        exitFlag = 1;
    }
    
}



// DRAW ROUTINE
// ===============================
void DrawScreen(void)
{
       
    // [COPY AND PASTE FROM PPA2] Copy your draw logic routine from PPA2 and paste them below
    int i, j;
    MacUILib_clearScreen();
    MacUILib_printf("####################\n");
    for(i = 0; i < ROW; i++){
        for(j = 0; j < COL; j++){
            MacUILib_printf("%c", content[i][j]);
        }
        MacUILib_printf("\n");
    }
    MacUILib_printf("####################\n");

    // // [TODO]   Insert somewhere in the draw routine to draw the randomly generated items on the board.

    // // [TODO]   Display the "Mystery String" contents at the bottom of the game board
    // //          To help players keep track of their game progress.
    
    // // // [TODO]   Insert somewhere in the draw routine to draw the randomly generated items on the board.

    // // // [TODO]   Display the "Mystery String" contents at the bottom of the game board
    // // //          To help players keep track of their game progress.
    MacUILib_printf("HOW TO PLAY:\nCollect letters to solve the Mystery String.\nPress '.' to change the game mode.\n");
    MacUILib_printf("--------------------\n");
    MacUILib_printf("Mystery String: %s\n", mysteryPtr);
    MacUILib_printf("Move Count: %d\n", moveCount);
    if (toggle==0){
        MacUILib_printf("Mode: Normal\n");
    } else MacUILib_printf("Mode: Advanced\n");
    MacUILib_printf("Items list:\n");
    for (i=0; i<5; i++){
        MacUILib_printf("%c = [%d, %d]\n", list[i].symbol, list[i].x, list[i].y);
    }
}



// DELAY ROUTINE
// ===============================
void LoopDelay(void)
{
    MacUILib_Delay(100000); // 0.1s delay
}





// TEAR-DOWN ROUTINE
// ===============================
void CleanUp(void)
{
    // [TODO]   To prevent memory leak, free() any allocated heap memory here
    //          Based on the PPA3 requirements, you need to at least deallocate one heap variable here.

    // Insert any additional end-game actions here.
    
    if (win==1)
        MacUILib_printf("\nYou Win!\n");
    
    free(mysteryPtr);
    mysteryPtr = NULL;
    
    int i;
    for (i=0; i<5; i++){
        if (listMalloc[i]!=NULL) {
            free(listMalloc[i]);
    }}
    free(listMalloc);
    listMalloc = NULL;
    
    MacUILib_uninit();

}




// The Item Generation Routine
////////////////////////////////////
void GenerateItems(struct objPos list[], const int listSize, const struct objPos *playerPos, const int xRange, const int yRange, const char* str)
{
    // This is possibly one of the most conceptually challenging function in all PPAs
    // Once you've mastered this one, you are ready to take on the 2SH4 course project!

    // Random Non-Repeating Item Generation Algorithm
    ////////////////////////////////////////////////////

    // Use random number generator function, rand(), to generate a random x-y coordinate and a random choice of character from the Goal String as the ASCII character symbol.
    //      The x and y coordinate range should fall within the xRange and yRange limits, which should be the x- and y-dimension of the board size.
    // This will then be a candidate of the randomly generated Item to be placed on the game board.

    // In order to make sure this candidate is validated, it needs to meet both criteria below:
    //  1. Its coordinate and symbol has not been previously generated (no repeating item)
    //  2. Its coordinate does not overlap the Player's position
    // Thus, for every generated item candidate, check whether its x-y coordinate and symbol has previously generated.  
    //  Also, check if it overlaps the player position
    //      If yes, discard this candidate and regenerate a new one
    //      If no, this candidate is validated.  Add it to the input list[]

    // There are many efficient ways to do this question
    //  We will take a deep dive into some methods in 2SI.

    int i,j, count=0;
    
    listMalloc = (char**)malloc(5*sizeof(char*));
    for (i=0; i<5; i++, count++){
        
        listMalloc[i] = (char*)malloc(3 * sizeof(char));
        
        for (j=0; j<3; j++){
            
            if (j==0){ // X-Coordinate
                do{
                    listMalloc[i][j] = rand() % xRange;
                } while (listMalloc[i][j]==0 || listMalloc[i][j]==10);
                list[i].x = listMalloc[i][j];
            
            } else if (j==1) { // Y-Coordinate
                listMalloc[i][j] = rand()% yRange;
                list[i].y = listMalloc[i][j];
            
            }else { // Symbol
                
                if (toggle==0){
                    do{
                        listMalloc[i][j] = str[rand() % 12];
                    } while (listMalloc[i][j]=='\n' || listMalloc[i][j]==' ');
                    list[i].symbol = listMalloc[i][j];
                
                } else{
                    
                    if (count<=2){
                        do{
                        listMalloc[i][j] = str[rand() % 12];
                        } while (listMalloc[i][j]=='\n' || listMalloc[i][j]==' ');
                        list[i].symbol = listMalloc[i][j];
                    } else{
                        listMalloc[i][j] = '!' + (rand() % 93);
                        list[i].symbol = listMalloc[i][j];
                    }
                }
            }
        }
        
        if (content[list[i].x][list[i].y] ==' '){
            content[list[i].x][list[i].y] = list[i].symbol;
        } else{
            i--;
        }
    }
}
