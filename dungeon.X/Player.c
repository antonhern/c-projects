// Antonio Hernandez Ruiz

#include "Player.h"
#include "UNIXBOARD.h"
#include <stdint.h>

static int inventory[INVENTORY_SIZE];

static int place = 0;

#define ZERO 0
int AddToInventory(uint8_t item){
    // cheching to see if the place is less than or inside of the inventory size
    // if it is add the item
    if(place < INVENTORY_SIZE){
        inventory[place] = item;
        return SUCCESS;
    }
    return STANDARD_ERROR;
}

int FindInInventory(uint8_t item){
    // temporary variable to hold the amount of values in the inventory
    // don't want to modify the variable place
    // checking the list/array backwards
    int temp;
    for(temp = place; temp >= ZERO; temp--){
        if(inventory[temp] == item){
            return SUCCESS;
        }
    }
    return STANDARD_ERROR;
}