// Antonio Hernandez Ruiz
#include "UNIXBOARD.h"

#include "Player.h"
#include "Game.h"
// Standard libraries
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
// room struct
struct Room{
    char title[GAME_MAX_ROOM_TITLE_LENGTH + 1];
    char description[GAME_MAX_ROOM_DESC_LENGTH + 1];
    int North;
    int South;
    int East;
    int West;
};
#define CHARS 25
// defining the variable for the room struct.
static struct Room room;
// string to hold what is read from file
static char string[CHARS];
// definition for helper function I made
uint8_t file(int roomNum);

// all of the direction functions use the helper that I made to open and read the files
// If it is a success and the direction is not equal to 0x00 then success is returned 
// meaning that you can travel in that direction as a player
int GameGoNorth(void) {
    if (room.North != 0x00 && file(room.North) == SUCCESS) {
        return SUCCESS;
    }
    return STANDARD_ERROR;
}

int GameGoEast(void) {
    if (room.East != 0x00 && file(room.East) == SUCCESS) {
        return SUCCESS;
    }
    return STANDARD_ERROR;
}

int GameGoSouth(void) {
    if (room.South != 0x00 && file(room.South) == SUCCESS) {
        return SUCCESS;
    }
    return STANDARD_ERROR;
}

int GameGoWest(void) {
    if (room.West != 0x00 && file(room.West) == SUCCESS) {
        return SUCCESS;
    }
    return STANDARD_ERROR;
}
// sets up the start of the game. 
// puts the player in the throne room to start
// checks to see if you can open the file(done in the helper)
// if so then success is returned
int GameInit(void) {
    uint8_t passed = file(STARTING_ROOM);
    if (passed == SUCCESS) {
        return SUCCESS;
    } else {
        return STANDARD_ERROR;
    }
}

// copying the room.tile to the pointer that is inserted
// then just returning the length of that
int GameGetCurrentRoomTitle(char *title) {
    strcpy(title, room.title);
    return strlen(title + 1);
}
// copying the room.description to the pointer that is inserted
// then just returning the length of the string
int GameGetCurrentRoomDescription(char *desc) {
    strcpy(desc, room.description);
    return strlen(desc + 1);
}

// getting the current exits by oring a variable of zero with the 
// binary value of the room exits and returning that at the end
// using a bit mask to do it
uint8_t GameGetCurrentRoomExits(void) {
    uint8_t exits = 0b0000;
    if (room.North) {
        exits |= GAME_ROOM_EXIT_NORTH_EXISTS;
    } 
    if (room.East) {
        exits |= GAME_ROOM_EXIT_EAST_EXISTS;
    } 
    if (room.South) {
        exits |= GAME_ROOM_EXIT_SOUTH_EXISTS;
    } 
    if (room.West) {
        exits |= GAME_ROOM_EXIT_WEST_EXISTS;
    }
    return exits;
}

// helper function that reads
// and processess all the files for the roooms
uint8_t file(int roomNum) {
    // cpying what room is gonna be opened to the string variable
    sprintf(string, "RoomFiles/room%d.txt", roomNum);
    
    // pointers and variables 
    FILE *fp;
    int len;
    int check = 1;
    // open the file
    fp = fopen(string, "r");
    if (fp == NULL) {
        FATAL_ERROR();
    }
    // set the file pointer 3 values in to skip the RPG portion of the file
    fseek(fp, 3, SEEK_SET);
    // getting the len of the title and then putting that in the variable/member for room title
    len = fgetc(fp);
    fread(room.title, len, 1, fp);
    // add the null terminator to the end of the title
    room.title[len] = '\0';
    if (strlen(room.title) != len) {
        return STANDARD_ERROR;
    }
    
    // redefining len and getting the next character which is jut any item the player picks up
    // then getting the numer of items required
    // checking to see if the item is in the inventory if it is set the flag to zero
    len = fgetc(fp);
    while (len) {
        uint8_t item = fgetc(fp);
        if (FindInInventory(item) == STANDARD_ERROR) {
            check = 0;
            break;
        }
        len--;
    }
    
    // getting the next character which is the description
    // doing the same thing to it as the title
    // reading the chracters and then ending the string with a null
    len = fgetc(fp);
    fread(room.description, len, 1, fp);
    room.description[len] = '\0';
    if (strlen(room.description) != len) {
        return STANDARD_ERROR;
    }
    
    
    // getting the next character which is the amount of collectables in the room
    // once you find the amount there are iterate trough them and add them to the
    // inventory if they aren't in it
    len = fgetc(fp);
    while (len) {
        uint8_t collectables = fgetc(fp);
        if (FindInInventory(collectables) == STANDARD_ERROR) {
            int i = AddToInventory(collectables);
            if (i == STANDARD_ERROR) {
                return STANDARD_ERROR;
            }
        }
        len--;
    }
    
    // getting the next characters which are the exits and then
    // making them equal to the members they correspond to
    room.North = fgetc(fp);
    room.East = fgetc(fp);
    room.South = fgetc(fp);
    room.West = fgetc(fp);
    
   // if the flag is zero that means that we need to check to see if we have the item
    // for that rooom
    // getting the next char and checking just in case if the item is in out inventory
    if (check == 0) {
        len = fgetc(fp);
        while (len) {
            uint8_t item = fgetc(fp);
            if (FindInInventory(item) == STANDARD_ERROR) {
                return STANDARD_ERROR;
            }
            len--;
        }
        
        // doing the same thing over again
        len = fgetc(fp);
        
        // getting the new description since we already have the item
        fread(room.description, len, 1, fp);
        room.description[len] = '\0';

         // checking to see for any other items just in case
        len = fgetc(fp);
        while (len) {
            uint8_t collectables2 = fgetc(fp);
            if (FindInInventory(collectables2) == STANDARD_ERROR) {
                int r = AddToInventory(collectables2);
                if (r == STANDARD_ERROR) {
                    return STANDARD_ERROR;
                }
            }
            len--;
        }
        // getting the exits at the end and adding them to the members
        room.North = fgetc(fp);
        room.East = fgetc(fp);
        room.South = fgetc(fp);
        room.West = fgetc(fp);
    }
    // closing the file
    fclose(fp);
    
    return SUCCESS;
    
}
