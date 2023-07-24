// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"


// User libraries
#include "stack.h"

int main() {
    BOARD_Init();

    printf("\n###### Beginning ahern336 stack test harness: ####\n\n");

    //What follows is starter code.  You will need to modify it!

    printf("Does StackInit() set the currentItemIndex appropriately?\n");
    struct Stack stack = {};
    StackInit(&stack);
    if (stack.currentItemIndex == -1) {
        printf("passed\n");
    } else {
        printf("failed\n");
    }
    printf("\nDoes StackInit() initialize the stack?\n");
    if (stack.initialized == TRUE) {
        printf("passed\n");
    } else {
        printf("failed test 2\n");
    }
    double x = 9.0;
    StackPush(&stack, x);
    double y = 8.0;
    StackPush(&stack, y);
    double z = 12.0;
    StackPush(&stack, z);
    double a = 15.0;
    StackPush(&stack, a);
    double value = 0;
    double q = 18.0;
    StackPush(&stack, q);
    double *p = &value;
    while (!StackIsEmpty(&stack)) {
        double q = 18.0;
        StackPop(&stack, p);
        printf("\nDoes StackPush() push all the numbers/ Does StackPop() get the last one in?\n");
        if (value == q) {
            printf("passed\n");
        } else {
            printf("StackPush and Pop failed\n");
        }
        break;
    }
    double size = StackGetSize(&stack);
    double size_expected = 4.0;
    printf("\nDoes StackSize() get the correct amount of items?\n");
    if (size == size_expected) {
        printf("passed\n");
    } else {
        printf("No StackSize failed\n");
    }
    struct Stack stack1 = {};
    int output = StackIsEmpty(&stack1);
    printf("\nDoes StackIsEmpty() return false for uninitialized stacks?\n");
    if (output == 0) {
        printf("passed\n");
    } else {
        printf("No it does not\n");
    }
    struct Stack stack2 = {};
    StackInit(&stack2);
    StackPush(&stack2, x);
    StackPush(&stack2, y);
    StackPush(&stack2, z);
    StackPush(&stack2, a);
    StackPush(&stack2, q);

    int full = StackIsFull(&stack2);
    printf("\nDoes StackisFull() return false stacks that are not full?\n");
    if (full == 0) {
        printf("passed\n");
    } else {
        printf("No StackIsFull() does not\n");
    }
    double size_test = StackGetSize(&stack2);
    double size_output = 5.0;
    printf("\nDoes StackGetSize() check for all active numbers?\n");
    if (size_test == size_output) {
        printf("passed\n");
    } else {
        printf("No StackSize Does not\n");
    }
    struct Stack stack3 = {};
    StackInit(&stack3);
    printf("\nDoes StackisEmpty check if an initialized stack is empty?\n");
    int test2 = StackIsEmpty(&stack3);
    if (test2 == 1) {
        printf("passed\n");
    } else {
        printf("No it does not\n");
    }
    struct Stack stack4 = {};
    int full_uninitialized = StackIsFull(&stack4);
    printf("\nDoes StackIsfull() return false for uninitialized stacks\n");
    if (full_uninitialized == 0) {
        printf("passed\n");
    } else {
        printf("No StackisFull() does not\n");
    }
    struct Stack stack5 = {};
    StackInit(&stack5);
    StackPush(&stack5, 10.0);
    printf("\nDoes StackPush push only one number at a time?/Does StackPop pop the only number in the stack?\n");
    double value1 = 0;
    double *point = &value1;
    double test_output = 10.0;
    StackPop(&stack5, point);
    if (value1 == test_output) {
        printf("passed\n");
    } else {
        printf("No StackPush() and Stack() do not\n");
    }


    BOARD_End();
    while (1);
    return 0;
}


