// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"



// User libraries
#include "rpn.h"

// **** Set macros and preprocessor directives ****
// The lab calls for 60 characters of user input
#define MAX_INPUT_LENGTH 60
#define STRING_TO_BIG 7

int main() {
    BOARD_Init();

    //What follows is starter code.  You will need to modify it!

    char rpn_sentence[MAX_INPUT_LENGTH + 2];
    double result;
    int valueReturned = 0;
    // char printString[MAX_INPUT_LENGTH];

    printf("Welcome to ahern336 RPN calculator.  Compiled on %s %s", __DATE__, __TIME__);
    while (1) {

        valueReturned = 0;

        printf("Enter floats and + - / * in RPN format:\n");

        fgets(rpn_sentence, sizeof (rpn_sentence), stdin);
        int x;
        //Clearing out all the newline characters in the sentece.
        for (x = 0; x < strlen(rpn_sentence); x++) {
            if (rpn_sentence[x] == '\n') {
                rpn_sentence[x] = '\0';
            }
        }
        //Since I cleared out all the spaces for the length of the sentence (which should be less thatn MAX_INPUT_LENGTH)
        // If the last character of the string is not null that means that the string is longer than is shouls be 
        // An error should be raised
        if (strlen(rpn_sentence) > MAX_INPUT_LENGTH && rpn_sentence[MAX_INPUT_LENGTH] != '\0') {
            // changing the last character (60) to a null.
            rpn_sentence[MAX_INPUT_LENGTH] = '\0';
            valueReturned = STRING_TO_BIG;
            for (x = 0; x < strlen(rpn_sentence); x++) {
                rpn_sentence[x] = '\0';
            }
            //dont want to remove the \n at the end of the string if there is one
            while (getchar() != '\n')
                ;
        }
        if (valueReturned != STRING_TO_BIG) {
            // if no errors are raised we keep on executing the rpn funciton
            // and the backspace function
            ProcessBackspaces(rpn_sentence);
            valueReturned = RPN_Evaluate(rpn_sentence, &result);
        }


        if (valueReturned == 1) {
            printf("Stack is full ERROR!\n");
        } else if (valueReturned == 2) {
            printf("Not enough numbers to work with ERROR!\n");
        } else if (valueReturned == 3) {
            printf("There is an invalid char in the string ERROR!\n");
        } else if (valueReturned == 4) {
            printf("Divde by Zero ERROR!\n");
        } else if (valueReturned == 5) {
            printf("Stack is Empty ERROR!\n");
        } else if (valueReturned == 6) {
            printf("Stack has too many items ERROR!\n");
        } else if (valueReturned == 7) {
            printf("To many characters in input string!\n");
        } else {
            printf("result = %f\n", result);
        }

    }

    while (1);
}
