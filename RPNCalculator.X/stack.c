#include "stack.h"
#include "BOARD.h"
#include <stdbool.h>
#include <stdio.h>

void StackInit(struct Stack *stack) {
    stack ->currentItemIndex = -1;
    stack->initialized = TRUE;
}

int StackIsFull(const struct Stack *stack) {
    // if the stack is at its max capacity it is full and it also has to be initialized to be checked
    if (stack -> currentItemIndex == STACK_SIZE - 1 && stack -> initialized == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

int StackIsEmpty(const struct Stack *stack) {
    // if the current index is at -1 the stack is empty the stack cant be chekcked also if it isn't initialized
    if (stack -> currentItemIndex == -1 && stack -> initialized == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

int StackPush(struct Stack *stack, double value) {
    //to push onto the stack it has to have a maximum amount of 19 cant push more into it
    if (stack ->currentItemIndex < STACK_SIZE-1) {
        if (stack -> initialized == TRUE) {


            stack -> currentItemIndex += 1;
            stack -> stackItems[stack -> currentItemIndex] = value;
            return SUCCESS;
        } else {
            return STANDARD_ERROR;
        }


    } else {
        return STANDARD_ERROR;
    }


}

int StackPop(struct Stack *stack, double *value) {
    // variable to hold a zero, can't pop from a stack if the current item index is at zero or less
    int min = 0;
    if (stack -> currentItemIndex >= min) {
        if (stack -> initialized == TRUE) {
            *value = stack -> stackItems[stack -> currentItemIndex];
            stack -> currentItemIndex -= 1;

            return SUCCESS;
        } else {
            return STANDARD_ERROR;
        }
    } else {
        return STANDARD_ERROR;
    }

}

int StackGetSize(const struct Stack *stack) {
    //stack has to be initialized to get the stack size
    if (stack -> initialized == TRUE) {
        //adding 1 so that the size could start from 1 not 0 index
        return stack -> currentItemIndex + 1;
    } else {
        return SIZE_ERROR;
    }
}















