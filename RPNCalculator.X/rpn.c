#include "stack.h"
#include "rpn.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
int isNum(char* token);
#define ZERO 0

int RPN_Evaluate(char * rpn_string, double * result) {
    //get the inputstring and break it up
    char* token = strtok(rpn_string, " ");
    struct Stack stack = {};
    double token1;
    //values to be popped from the stack
    double popped1, popped2;
    double num2 = 1;
    //initialize the stack
    StackInit(&stack);
    //check if the token or input is null or the end of the string
    while (token != NULL) {
        //check if the token is not a number
        if (!isNum(token)) {
            //if the string length is more than one it is not a valid token
            if (strlen(token) != 1) {
                return RPN_ERROR_INVALID_TOKEN;
            }
            //using string comparison to make sure that * + / - are the only valid operators used
            if (strcmp(token, "*") == 0 || strcmp(token, "+") == 0 || strcmp(token, "-") == 0 || strcmp(token, "/") == 0) {
                //selecting +
                if (strcmp(token, "+") == 0) {
                    if (SUCCESS == StackPop(&stack, &popped1)) {
                    } else {
                        //checking to see if the first nuber is popped
                        return RPN_ERROR_TOO_FEW_ITEMS_REMAIN;
                    }
                    if (SUCCESS == StackPop(&stack, &popped2)) {
                    } else {
                        //checking to see if the second number is popped
                        return RPN_ERROR_STACK_UNDERFLOW;
                    }
                    //giving value to the reuslt 
                    *result = popped1 + popped2;
                    if (StackGetSize(&stack) < STACK_SIZE) {
                        //pushing the result onto the stack
                        StackPush(&stack, *result);
                    } else {
                        return RPN_ERROR_STACK_OVERFLOW;
                    }
                }
                //string comparison to check if the operator is a -
                if (strcmp(token, "-") == 0) {
                    if (SUCCESS == StackPop(&stack, &popped1)) {
                    } else {
                        return RPN_ERROR_TOO_FEW_ITEMS_REMAIN;
                    }
                    if (SUCCESS == StackPop(&stack, &popped2)) {
                    } else {
                        return RPN_ERROR_STACK_UNDERFLOW;
                    }
                    //subracting the second number minus the first
                    *result = popped2 - popped1;
                    if (StackGetSize(&stack) < STACK_SIZE) {
                        StackPush(&stack, *result);
                    } else {
                        return RPN_ERROR_STACK_OVERFLOW;
                    }
                }
                // string comparison to check if operator is a *
                if (strcmp(token, "*") == 0) {
                    if (SUCCESS == StackPop(&stack, &popped1)) {
                    } else {
                        return RPN_ERROR_TOO_FEW_ITEMS_REMAIN;
                    }
                    if (SUCCESS == StackPop(&stack, &popped2)) {
                    } else {
                        return RPN_ERROR_STACK_UNDERFLOW;
                    }
                    *result = popped1 * popped2;
                    if (StackGetSize(&stack) < STACK_SIZE) {
                        StackPush(&stack, *result);
                    } else {
                        return RPN_ERROR_STACK_OVERFLOW;
                    }
                }
                //string comparison to check if operator is a /
                if (strcmp(token, "/") == 0) {
                    if (SUCCESS == StackPop(&stack, &popped1)) {
                    } else {
                        return RPN_ERROR_TOO_FEW_ITEMS_REMAIN;
                    }
                    if (SUCCESS == StackPop(&stack, &popped2)) {
                    } else {
                        return RPN_ERROR_STACK_UNDERFLOW;
                    }
                    //if the first number popped from the stack is a zero that means an error for zero division
                    if (popped1 == ZERO) {
                        return RPN_ERROR_DIVIDE_BY_ZERO;
                    }
                    *result = popped2 / popped1;
                    if (StackGetSize(&stack) < STACK_SIZE) {
                        StackPush(&stack, *result);
                    } else {
                        return RPN_ERROR_STACK_OVERFLOW;
                    }

                }

            } else {
                return RPN_ERROR_INVALID_TOKEN;
            }

        } else {
            if (StackIsFull(&stack)) {
                return RPN_ERROR_STACK_OVERFLOW;
            }
            //push the token into the stack
            token1 = atof(token);
            StackPush(&stack, token1);
        }
        //get the next token here 
        token = strtok(NULL, " ");
    }
    //if the stack size at the end of operations is more than 1 there is an error
    //if the stack size is less than one at the end of operations ther is an error as well
    if (StackGetSize(&stack) > num2) {
        return RPN_ERROR_TOO_MANY_ITEMS_REMAIN;
    } else if (StackGetSize(&stack) < num2) {
        return RPN_ERROR_TOO_FEW_ITEMS_REMAIN;
    }
    StackPop(&stack, result);
    return RPN_NO_ERROR;
}
// helper function to check if the toekn is a number, if it has decimal points, is a negative and is in the correct range
int isNum(char *token) {
    int x = 0, y = 0;
    int z = 0;
    //hex values for negative symbols and decimal points as well as the limits from 0 to 9
    char negative = 0x2D, Decimal = 0x2E, FirstLimit = 0x30, LastLimit = 0x39;
    for (x = 0; x < strlen(token); x++) {
        if (!(token[x] >= FirstLimit && token[x] <= LastLimit)) {
            if (token[x] == negative && (x == ZERO)) {
                continue;
            }
            if (token[x] == Decimal && (y == ZERO)) {
                y++;
                continue;
            }
            return FALSE;
        } else {
            z++;
        }

    }
    if (z >= 1) {
        return TRUE;
    }
    return FALSE;
}
//function to process backspaces
//checks to see where the character is inside of the rpn sentence 
int ProcessBackspaces(char *rpn_sentence) {
    // inner iterator
    int x1;
    //deleted
    int out1 = 1;
    int out2 = 2;
    //flag
    int place = 0;
    //iterator
    int y = 0;
    int length = strlen(rpn_sentence);
    while (y < length) {
        if (rpn_sentence[y] == '\b') {
            if (y != ZERO) {
                for (x1 = 0; x1 + place < length; x1++) {
                    if (x1 == y - out1) {
                        place = out2;
                    }
                    rpn_sentence[x1] = rpn_sentence[x1 + place];
                }
                place = 0;
                length = length - out2;
                y--;
                rpn_sentence[x1] = '\0';
            } else {
                for (x1 = 1; x1 < length; x1++) {
                    rpn_sentence[x1 - out1] = rpn_sentence[x1];
                }
                rpn_sentence[x1 - out1] = '\0';
                length--;
            }
        } else {
            y++;
        }
    }
    return strlen(rpn_sentence);

}