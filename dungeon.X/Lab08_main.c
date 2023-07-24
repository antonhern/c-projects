// Antonio Hernandez Ruiz

// **** Include libraries here ****
// Standard libraries
#include <string.h>
#include <math.h>
#include <stdio.h>

//CSE013E Support Library
#include "UNIXBOARD.h"
#include "Player.h"
#include "Game.h"


// User libraries


// **** Set any macros or preprocessor directives here ****

// **** Declare any data types here ****

// **** Define any global or external variables here ****
#define DEAD_END 0b0000
#define ONE 1
// **** Declare any function prototypes here ****

int main()
{



    /******************************** Your custom code goes below here ********************************/
    int travel = GameInit();
    

    if(travel == STANDARD_ERROR){
        FATAL_ERROR();
    }

    char room_title[GAME_MAX_ROOM_TITLE_LENGTH + ONE];
    char room_description[GAME_MAX_ROOM_DESC_LENGTH + ONE];

    char input;
    uint8_t exits;

    int check;

    while(1){
        GameGetCurrentRoomTitle(room_title);
        printf("\nRoom Title: %s\n", room_title);

        GameGetCurrentRoomDescription(room_description);
        printf("\nRoom Description: %s\n", room_description);

        exits = GameGetCurrentRoomExits();
        printf("\nPossible Exits: ");
        if( exits & GAME_ROOM_EXIT_NORTH_EXISTS){
            printf("\n\tNORTH Exit Available");
        }
        if(exits & GAME_ROOM_EXIT_EAST_EXISTS){
            printf("\n\tEAST Exit Available");
        }
        if(exits & GAME_ROOM_EXIT_SOUTH_EXISTS){
            printf("\n\tSOUTH Exit Available");
        }
        if(exits & GAME_ROOM_EXIT_WEST_EXISTS){
            printf("\n\tWEST Exit Available");
        }
        if(exits == DEAD_END){
            printf("\n\t Dead End. Press q to quit");
        }
        printf("\n");


            printf("Pick a direction you want to go in!\n\tn = North\n\te = East\n\ts = South\n\tw = West\n\tq = Quit Game\nInput: ");

            input = getchar();

            if(getchar()!= '\n'){
                while(getchar()!= '\n');
                printf("\nWrong Input, Please try again!\n");
                continue;
            }
           if (input == 'n'|| input == 'N'){
                    check = GameGoNorth();
                    if(check == STANDARD_ERROR){
                        printf("\nDirection North is not Available!\n");
                    }else{
                       printf("\nYou have gone North!\n"); 
                    }
           }
            if(input == 'e'|| input == 'E'){
                    check = GameGoEast();
                    if(check == STANDARD_ERROR){
                        printf("\nDirection East is not Available!\n");
                    }else{
                        printf("\nYou have gone East!\n");
                    }
            }
            if(input == 's'|| input == 'S'){
                    check = GameGoSouth();
                    if(check == STANDARD_ERROR){
                        printf("\nDirection South is not Available!\n");
                    }else{
                       printf("\nYou have gone South!\n"); 
                    }
            }
            if(input == 'w'|| input == 'W'){
                    check = GameGoWest();
                    if(check == STANDARD_ERROR){
                        printf("\nDirection West is not Available!\n");
                    }else{
                        printf("\nYou have gone West!\n");
                    }
            }      
            if(input == 'q'|| input == 'Q'){
                    printf("\nYou have quit the Game!\n");
                    exit(SUCCESS);
            }
            if(input == '\n'){
                printf("\nWrong Input, Please try again!\n");
            }
    }

}

    /**************************************************************************************************/


