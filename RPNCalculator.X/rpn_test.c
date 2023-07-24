// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"



// User libraries
#include "rpn.h"

int main() {
    BOARD_Init();
    int error;

    printf("\n###### Beginning ahern336's rpn test harness: ####\n\n");

    //What follows is starter code.  You will need to modify it!

    char test0[] = "1 1 +";
    double result0;
    double expected0 = 2;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test0);
    error = RPN_Evaluate(test0, &result0);
    if (error) {
        printf("    Failed, RPN_Evaluate produced an error for addition\n");
    } else if (result0 != expected0) {
        printf("    Failed, expected = %f , output = %f\n", expected0, result0);
    } else {
        printf("    Success!\n");
    }
    char test1[] = "1 22.555 -";
    double result1;
    double output1 = -21.555;
    printf("Testing RPN_Evaluate with \"%s\"...\n ", test1);
    error = RPN_Evaluate(test1, &result1);
    if (error) {
        printf("    Failed, RPN_Evaluate produced an error for subtraction\n");
    } else if (result1 != output1) {
        printf("    Failed, expected %f , output =  %f\n", output1, result1);
    } else {
        printf("    Success!\n");
    }
    char test2[] = "5 2.1 * 2 *";
    double result2;
    double output2 = 21;
    printf("Testing RPN_Evaluate with \"%s\"...\n", test2);
    error = RPN_Evaluate(test2, &result2);
    if (error) {
        printf("    Failed, RPN_Evaluate produced an error for multiplication\n");
    } else if (result2 != output2) {
        printf("    Failed, expected = %f , ouptput = %f\n", output2, result2);
    } else {
        printf("    Success!\n");
    }
    char test3[] = "7 4 /";
    double result3;
    double output3 = 1.75;
    printf("Testing RPN_Evaluate with \"%s\"... \n", test3);
    error = RPN_Evaluate(test3, &result3);
    if (error) {
        printf("    Failed, RPN_Evaluate produced an error for division\n");
        printf("Error here %d\n", error);
    } else if (result3 != output3) {
        printf("    Failed, expected = %f , output = %f\n", output3, result3);
    } else {
        printf("    Success!\n");
    }
    char test4[] = "2 -1 + 5 * 4 / 1 + 4 2 + +";
    double result4 = 0.0;
    double output4 = 8.25;
    printf("Testing RPN_Evaluate with \"%s\"... \n", test4);
    error = RPN_Evaluate(test4, &result4);
    if (error) {
        printf("    Failed, RPN_Evaluate produced an error\n");
    } else if (result4 != output4) {
        printf("    Failed, expected = %f , output = %f\n", output4, result4);
    } else {
        printf("    Success!\n");
    }
    double empty1;
    char test5[] = "-. 2 3 + ";
    printf("Testing RPN_Evaluate with \"%s\"... \n", test5);
    error = RPN_Evaluate(test5, &empty1);
    if (error == RPN_ERROR_INVALID_TOKEN) {
        printf("    Success, raised the correct error for Invalid Token\n");
    } else {
        printf("    Failure, error raised: %d\n", error);
    }
    double empty2;
    char test6[] = " 2 -0.0000 / ";
    printf("Testing RPN_Evaluate with \"%s\"... \n", test6);
    error = RPN_Evaluate(test6, &empty2);
    if (error == RPN_ERROR_DIVIDE_BY_ZERO) {
        printf("    Success, raised the correct error for Dividing by Zero\n");
    } else {
        printf("    Failure, error raised: %d\n", error);
    }
    double empty3;
    char test7[] = " 3 5 * + ";
    printf("Testing RPN_Evaluate with \"%s\"... \n", test7);
    error = RPN_Evaluate(test7, &empty3);
    if (error == RPN_ERROR_STACK_UNDERFLOW) {
        printf("    Success, raised the correct error for Stack Underflow\n");
    } else {
        printf("    Failure, error raised: %d\n", error);
    }
    double empty4;
    char test8[] = " 5 5 + 5";
    printf("Testing RPN_Evaluate with \"%s\"... \n", test8);
    error = RPN_Evaluate(test8, &empty4);
    if (error == RPN_ERROR_TOO_MANY_ITEMS_REMAIN) {
        printf("    Success, raised the correct error for too many Stack Items Remaining\n");
    } else {
        printf("    Failure, error raised: %d\n", error);
    }
    double empty5;
    char test9[] = "1 2 3 4 5 6 7 8 9 1 1 3 4 6 8 3 1 9 4 5 6";
    printf("Testing RPN_Evaluate with \"%s\"... \n", test9);
    error = RPN_Evaluate(test9, &empty5);
    if (error == RPN_ERROR_STACK_OVERFLOW) {
        printf("    Success, raised the correct error for Stack Overflow\n");
    } else {
        printf("    Failure, error raised: %d\n", error);
    }
    double empty6;
    char test10[] = "";
    printf("Testing RPN_Evaluate with \"%s\"... \n", test10);
    error = RPN_Evaluate(test10, &empty6);
    if (error == RPN_ERROR_TOO_FEW_ITEMS_REMAIN) {
        printf("    Success, raised the correct error for too few Stack Items Remaining\n");
    } else {
        printf("    Failure, error raised: %d\n", error);
    }
    printf("Testing ProcessBackspaces:\n");
    char test_pb1[] = "123\b3\b\b\b\b\b\b\b33314";
    ProcessBackspaces(test_pb1);
    printf("result    : %s\n", test_pb1);
    printf("should be : 33314\n");
    BOARD_End();
    while (1);
}


