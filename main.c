//Totalistic Cellular Automaton

#include <stdio.h>
#include <stdbool.h>

const int WORLD_SIZE = 65;

typedef struct cell_struct{
    int localSum; // total sum of local cells, [left] + [me] + [right]: possible values are 0-6
    int status;   // this cell's current status: 0, 1, or 2
    int count;    // running accumulated count of this cell's active status for all generations
} cell;

//Finds the Binary value of rule, sets that value into valArray, each number 012 is placed in each element of the array.
bool setValArray(int valArray[7], int rule) {
    //Task 1
    bool returnStatement = false;
    int quotient = rule;
    int remainder;
    
    if ((rule >= 0) && (rule <= 2186)){
        for(int i = 0;i < 7;i++) {
            // if(quotient != 0){
                remainder = quotient % 3;
                //printf("%d\n",remainder);
                valArray[i] = remainder; 
                quotient = (quotient/3);
            // }
        }
        returnStatement = true;
    }
    return returnStatement;
}

//------------------------------------------------------------------------------------------------------------------------------------------

//Sets the localSum of each cell using its status, localSum takes into account each indiv cell, the cell to its right and its left.
//The last cell takes into account, itself, the cell to its left and the first cell.
//The first cell takes into account, itself, the cell to its right and the last cell.
void setSums(cell world[WORLD_SIZE]) {
    //TODO: Task 4

    for(int i = 1; i <= WORLD_SIZE-2; i++) {
        int left = world[i-1].status;
        int right = world[i+1].status;
        int current = world[i].status;
        world[i].localSum = left + right + current;
    }

    world[0].localSum = world[0].status + world[1].status + world[WORLD_SIZE-1].status;
    world[WORLD_SIZE-1].localSum = world[0].status + world[WORLD_SIZE-1].status + world[WORLD_SIZE-2].status;

    return;
}

//------------------------------------------------------------------------------------------------------------------------------------------

//Sets the Total Sum of each Generation, which is printed at the end of each generation.
//Total sum is all the statuses of each Generation added together.
//Function also updates cell count and cell status.
int evolveWorld(cell world[WORLD_SIZE], int ruleValArray[7]) {
    //TODO: Task 6
    //int TotalSum = 1;
    int TotalSum = 0;
    
    for(int i = 0; i < WORLD_SIZE; i++) {
        world[i].status = ruleValArray[world[i].localSum];
        world[i].count += world[i].status;
        TotalSum += world[i].status;
    }
    return TotalSum;
}

//-------------------------------------------------------------------------------------------------------------------------------------------

//MAIN START
int main() {
    cell world[WORLD_SIZE];
    printf("Welcome to the Totalistic Cellular Automaton!\n");

    //Task 2
    int rule;
    int valArray[7];
    printf("Enter the rule # (0-2186): \n");
    scanf("%d",&rule);

    //Asks user to enter rule again if requirements are not met
    setValArray(valArray,rule);
    while(setValArray(valArray,rule) != true) {
        printf("Enter the rule # (0-2186): \n");
        scanf("%d",&rule);
        setValArray(valArray,rule);
    }

    printf("\nThe value array for rule #%d is ",rule);
    for (int i = 6; i >= 0; i--){
        printf("%d",valArray[i]);
    }

    printf("\n\n");
    //--------------------------------------------------------------------------------------------------------
    
    printf("The evolution of all possible states are as follows:\n");
    //Task 3
    char status[7]; //array that prints valArray flipped
    for(int i = 0;i < 7;i++) {
        if(valArray[i] == 0) {
            status[i] = ' ';
        }
        else if(valArray[i] == 1) {
            status[i] = '-';
        }
        else {
            status[i] = '+';
        }
    }
    
    printf("Local Sum:   6       5       4       3       2       1       0      \n");
    printf("States:    |+++|   |++-|   |++ |   |+- |   |-- |   |-  |   |   |    \n");
    printf("                   |+-+|   |+ +|   |+ -|   |- -|   | - |            \n");
    printf("                   |-++|   | ++|   |-+ |   | --|   |  -|            \n");
    printf("                           |+--|   | +-|   |+  |                    \n");
    printf("                           |-+-|   |- +|   | + |                    \n");
    printf("                           |--+|   | -+|   |  +|                    \n");
    printf("                                   |---|                            \n");
    printf("New Status: |%c|     |%c|     |%c|     |%c|     |%c|     |%c|     |%c|     \n\n",status[6],status[5],status[4],status[3],status[2],status[1],status[0]);
    //---------------------------------------------------------------------------------------------------------------------------------------------------------------
    //Task 5a
    int Generation = 0;

    //Asks user to eneter Generation again if requirements are not met
    while (Generation < 1 || Generation > 49) {
        printf("Enter the number of generations (1-49): \n");
        scanf("%d",&Generation);
    }
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------
    printf("Enter the value (1 or 2) for the initial active cell: \n");
    //Task 5b
    int middleStatus;
    scanf("%d",&middleStatus);

    //Asks user to eneter initial active cell again if requirements are not met
    while ((middleStatus != 1) && (middleStatus != 2)) {
        printf("Enter the value (1 or 2) for the initial active cell: \n");
        scanf("%d",&middleStatus);
    }
    printf("\n");
    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------
    printf("Initializing world & evolving...\n");
    //Task 5c
    //initializes status,count and localSum
    for(int i = 0; i < WORLD_SIZE; i++){
        world[i].status = 0;
        world[i].count = 0;
        world[i].localSum = 0;
        //sets initial active cell status and sets initial active cell count
        if(i == WORLD_SIZE/2){
            world[i].status = middleStatus;
            world[i].count += middleStatus;

        }
    }

    //Generation 0
    for(int j = 0; j < WORLD_SIZE; j++) { 
        if(world[j].status == 0){
            printf(" ");
        }
        else if(world[j].status == 1){
            printf("-");
        }
        else if(world[j].status == 2) {
            printf("+");
        }
    }
    printf(" %d ",middleStatus);

    printf("\n");
    setSums(world); //Updates world
    //---------------------------------------------------------------------------------------------------------

    //Generation 1 and onward
    //Task 7
    for(int i = 1; i < Generation; i++) {
        int TotalSum = evolveWorld(world,valArray);
        for(int i = 0; i < WORLD_SIZE;i++){
            if(world[i].status == 0) {
                printf(" ");
            }
            else if (world[i].status == 1) {
                printf("-");
            }
            else {
                printf("+");
            }
        }
        printf(" %d ", TotalSum);
        printf("\n");
        setSums(world);
    }  

    //Line before Count
    for(int i = 0; i < WORLD_SIZE; i++) {
        printf("_");
    }
    printf("\n");
    //-----------------------------------------------------------------------------------------------------
    //Task 8:

    //Prints tens value of count for each cell
    for(int i = 0; i < 65;i++){
        if(world[i].count >= 10) {
            printf("%d",world[i].count/10);
        }
        else {
            printf(" ");
        }
    }
    printf("\n");

    //Prints ones value of count for each cell
    for(int i = 0; i < 65; i++){
        if(world[i].count != 0){
            printf("%d",world[i].count%10);
        }
        else {
            printf(" ");
        }
    }

    printf("\n");
    return 0;
}
